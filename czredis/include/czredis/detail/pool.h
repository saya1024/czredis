#pragma once

#include "pool_object.h"

namespace czredis
{

enum class when_exhausted_action { kWait, kThrow, kCreate };

namespace detail
{

struct pool_config
{
    size_t pool_size = 8;
    size_t init_size = 8;
    when_exhausted_action when_exhausted = when_exhausted_action::kWait;
    unsigned max_wait_millis = 1000;
    unsigned max_idle_millis = 60 * 1000;
    unsigned health_check_retry_times = 3;
    unsigned health_check_millis = 30 * 1000;
    bool health_check_on_borrow = false;
};

template<typename OBJ>
class pool : private asio::noncopyable
{
    using pointer = std::shared_ptr<OBJ>;
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
        for (size_t i = 0; i < config_.init_size; i++)
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

    virtual pointer create_object() = 0;

    long long duration_millis(time_point time) noexcept
    {
        return std::chrono::duration_cast<
            std::chrono::milliseconds>(steady_clock::now() - time).count();
    }

    void check_idle_time()
    {
        auto millis = static_cast<long long>(config_.max_idle_millis);
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

    pointer get_one()
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
        if (pool_.size() < config_.pool_size ||
            (config_.when_exhausted == when_exhausted_action::kCreate))
        {
            auto pobj = create_object();
            pool_.emplace_back(pobj);
            return pobj;
        }
        if (config_.when_exhausted == when_exhausted_action::kThrow)
        {
            return nullptr;
        }
    }

    pointer borrow_object()
    {
        pointer pobj = nullptr;
        if (config_.when_exhausted == when_exhausted_action::kWait)
        {
            auto wait_start = steady_clock::now();
            auto millis = static_cast<long long>(config_.max_wait_millis);
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
            if (config_.health_check_on_borrow)
            {
                unsigned retry_times = 0;
                do
                {
                    if (pobj->check_health())
                        break;
                    ++retry_times;
                } while (retry_times < config_.health_check_retry_times);
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

