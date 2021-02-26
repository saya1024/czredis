#pragma once

#include "pool_config.h"
#include "pool_object.h"

namespace czredis
{

namespace detail
{

template<typename OBJ>
class pool : private asio::noncopyable
{
    using obj_pointer = std::shared_ptr<OBJ>;
    using lock_guard = std::lock_guard<std::mutex>;

    pool_config config_;
    time_point last_check_idle_;
    std::mutex mtx_;
    std::vector<pool_object_slot<OBJ>> pool_;

public:
    pool(const pool_config& config) :
        config_(config),
        last_check_idle_(steady_clock::now())
    {
        for (size_t i = 0; i < config_.init_size(); i++)
        {
            pool_.emplace_back(create_object());
        }
    }

    virtual ~pool() noexcept
    {}

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

    void check_idle_time()
    {
        auto millis = config_.max_idle_time();
        if (millis == 0)
            return;
        if (duration_millis(last_check_idle_) > millis)
        {
            bool removed = false;
            auto length = pool_.size();
            for (size_t i = 0; i < length; i++)
            {
                auto& slot = pool_[i];
                if (!slot.borrowed() && duration_millis(slot.last_borrow_time()) > millis)
                {
                    slot.set_ptr(nullptr);
                    removed = true;
                }
            }
            if (removed)
            {
                decltype(pool_) new_pool;
                for (size_t i = 0; i < length; i++)
                {
                    auto& slot = pool_[i];
                    if (!slot.empty())
                        new_pool.emplace_back(std::move(slot));
                }
                pool_ = std::move(new_pool);
            }
            last_check_idle_ = steady_clock::now();
        }
    }

    obj_pointer get_one()
    {
        lock_guard lock(mtx_);

        check_idle_time();
        auto length = pool_.size();
        for (size_t i = 0; i < length; i++)
        {
            auto& slot = pool_[i];
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
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
                unsigned retries = 0;
                do
                {
                    if (pobj->check_health())
                        break;
                } while (retries++ < config_.health_check_retry());
            }
            else
            {
                pobj->prepare();
            }
        }
        return pobj;
    }
};

} // namespace detail
} // namespace czredis

