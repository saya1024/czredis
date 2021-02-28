#pragma once

#include "move_only.h"
#include "../common.h"

namespace czredis
{
namespace detail
{

class pool_object : private move_only
{
    time_point last_response_time_;

public:
    pool_object() : last_response_time_(steady_clock::now())
    {}

    virtual ~pool_object() noexcept
    {}

    virtual void prepare() = 0;

    virtual bool check_health() = 0;

    void update_response_time() noexcept
    {
        last_response_time_ = steady_clock::now();
    }

    time_point last_response_time() const noexcept
    {
        return last_response_time_;
    }
};

class pool_object_slot : private move_only
{
    using obj_pointer = std::shared_ptr<pool_object>;

    obj_pointer pobj_;
    time_point last_borrow_time_;

public:
    explicit pool_object_slot(obj_pointer ptr) :
        pobj_(ptr),
        last_borrow_time_(steady_clock::now())
    {}

    void set_ptr(obj_pointer&& ptr) noexcept
    {
        pobj_ = std::move(ptr);
    }

    obj_pointer get_ptr() const noexcept
    {
        return pobj_;
    }

    void update_last_borrow_time() noexcept
    {
        last_borrow_time_ = steady_clock::now();
    }

    time_point last_borrow_time() const noexcept
    {
        return last_borrow_time_;
    }

    time_point last_response_time() const noexcept
    {
        return pobj_->last_response_time();
    }

    bool empty() const noexcept
    {
        return pobj_ == nullptr;
    }

    bool borrowed() const noexcept
    {
        return !empty() && pobj_.use_count() > 1;
    }

    bool not_borrowed() const noexcept
    {
        return !empty() && pobj_.use_count() == 1;
    }
};


} // namespace detail
} // namespace czredis