#pragma once

#include "pool_config.h"
#include "pool_object.h"

namespace czredis
{

namespace detail
{

class pool : private asio::noncopyable
{
    using obj_pointer = std::shared_ptr<pool_object>;
    using lock_guard = std::lock_guard<std::mutex>;

    pool_config config_;

    std::mutex mtx_;
    std::vector<pool_object_slot> pool_;
    std::thread loop_;
    std::promise<bool> stop_loop_;

public:
    pool(const pool_config& config) :
        config_(config)
    {
        for (size_t i = 0; i < config_.init_size(); i++)
        {
            pool_.emplace_back(create_object());
        }

        if (config_.health_check_interval() > 0 &&
            config_.max_idle_time() > 0)
        {
            loop_ = std::thread([this] {
                thread_loop();
            });
        }
    }

    virtual ~pool() noexcept
    {
        stop_loop_.set_value(true);
        if (loop_.joinable())
        {
            loop_.join();
        }
    }

    size_t real_size() const noexcept
    {
        return pool_.size();
    }

protected:

    virtual obj_pointer create_object() = 0;

    long long duration_millis(time_point time) noexcept
    {
        return std::chrono::duration_cast<
            std::chrono::milliseconds>(steady_clock::now() - time).count();
    }

    obj_pointer get_one()
    {
        lock_guard lock(mtx_);

        for (auto& slot : pool_)
        {
            if (slot.not_borrowed())
            {
                slot.update_last_borrow_time();
                return slot.get_ptr();
            }
        }
        if (pool_.size() < config_.pool_size() ||
            (config_.exhausted_action() == when_pool_exhausted::kCreate))
        {
            auto pobj = create_object();
            pool_.emplace_back(pobj);
            return pobj;
        }
        if (config_.exhausted_action() == when_pool_exhausted::kThrow)
        {
            return nullptr;
        }
    }

    obj_pointer borrow_object()
    {
        obj_pointer pobj = nullptr;
        if (config_.exhausted_action() == when_pool_exhausted::kWait)
        {
            auto wait_start = steady_clock::now();
            auto millis = config_.max_wait_time();
            do
            {
                pobj = get_one();
                if (pobj != nullptr)
                    break;
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            } while (millis == 0 || duration_millis(wait_start) < millis);
        }
        else
        {
            pobj = get_one();
        }

        if (pobj == nullptr)
        {
            throw redis_pool_exhausted_error();
        }
        else
        {
            if (config_.health_check_on_borrow())
            {
                check_health(pobj);
            }
            else
            {
                pobj->prepare();
            }
        }
        return pobj;
    }

    obj_pointer get_one_for_health_check()
    {
        lock_guard lock(mtx_);

        auto millis = config_.health_check_interval();
        for (auto& slot : pool_)
        {
            if (slot.not_borrowed() &&
                duration_millis(slot.last_response_time()) > millis)
            {
                return slot.get_ptr();
            }
        }
    }

    void check_health(obj_pointer& pobj)
    {
        unsigned retry = 0;
        do
        {
            if (pobj->check_health())
                break;
        } while (retry++ < config_.health_check_retry());
    }

    void check_idle()
    {
        lock_guard lock(mtx_);

        bool removed = false;
        auto millis = config_.max_idle_time();
        for (auto& slot : pool_)
        {
            if (slot.not_borrowed() &&
                duration_millis(slot.last_borrow_time()) > millis)
            {
                slot.set_ptr(nullptr);
                removed = true;
            }
        }
        if (removed)
        {
            decltype(pool_) new_pool;
            for (auto& slot : pool_)
            {
                if (!slot.empty())
                    new_pool.emplace_back(std::move(slot));
            }
            pool_.swap(new_pool);
        }
    }

    void thread_loop()
    {
        auto fstop = stop_loop_.get_future();
        auto last_check_idle = steady_clock::now();
        while (fstop.wait_for(std::chrono::milliseconds(100))
            == std::future_status::timeout)
        {
            if (duration_millis(last_check_idle) > config_.max_idle_time())
            {
                last_check_idle = steady_clock::now();
                check_idle();
            }

            auto pobj = get_one_for_health_check();
            if (pobj != nullptr)
                check_health(pobj);
        }
    }
};

} // namespace detail
} // namespace czredis

