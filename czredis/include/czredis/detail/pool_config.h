#pragma once

#include "../common.h"

namespace czredis
{

enum class when_pool_exhausted { kWait, kThrow, kCreate };

namespace detail
{

class pool_config
{
    size_t pool_size_;
    size_t init_size_;
    when_pool_exhausted exhausted_action_;
    unsigned max_wait_time_;
    unsigned max_idle_time_;
    unsigned health_check_retry_;
    unsigned health_check_interval_;
    bool health_check_on_borrow_;

public:
    pool_config() = default;

    size_t pool_size() const noexcept
    {
        return pool_size_;
    }

    void set_pool_size(size_t size) noexcept
    {
        pool_size_ = size;
    }

    size_t init_size() const noexcept
    {
        return init_size_;
    }

    void set_init_size(size_t size) noexcept
    {
        init_size_ = size;
    }

    when_pool_exhausted exhausted_action() const noexcept
    {
        return exhausted_action_;
    }

    void set_exhausted_action(when_pool_exhausted action) noexcept
    {
        exhausted_action_ = action;
    }

    unsigned max_wait_time() const noexcept
    {
        return max_wait_time_;
    }

    void set_max_wait_time(unsigned millis) noexcept
    {
        max_wait_time_ = static_cast<long long>(millis);
    }

    unsigned max_idle_time() const noexcept
    {
        return max_idle_time_;
    }

    void set_max_idle_time(unsigned millis) noexcept
    {
        max_idle_time_ = static_cast<long long>(millis);
    }

    unsigned health_check_retry() const noexcept
    {
        return health_check_retry_;
    }

    void set_health_check_retry(unsigned times) noexcept
    {
        health_check_retry_ = times;
    }

    unsigned health_check_interval() const noexcept
    {
        return health_check_interval_;
    }

    void set_health_check_interval(unsigned millis) noexcept
    {
        health_check_interval_ = millis;
    }

    bool health_check_on_borrow() const noexcept
    {
        return health_check_on_borrow_;
    }

    void set_health_check_on_borrow(bool enabel) noexcept
    {
        health_check_on_borrow_ = enabel;
    }
};

} // namespace detail
} // namespace czredis