#pragma once

#include "error.h"

namespace czredis
{
namespace detail
{

template<typename T>
class nullable
{
    bool is_null_;
    T value_;

public:
    explicit nullable() :
        is_null_(true),
        value_{}
    {}

    explicit nullable(const T& value) :
        is_null_(false),
        value_(value)
    {}

    explicit nullable(T&& value) :
        is_null_(false),
        value_(std::move(value))
    {}

    bool is_null()
    {
        return is_null_;
    }

    T& get()
    {
        if (is_null_)
            throw redis_data_error("value is null");
        return value_;
    }

    const T& get() const
    {
        if (is_null_)
            throw redis_data_error("value is null");
        return value_;
    }

    bool try_get(T& value)
    {
        if (is_null_)
            return false;
        value = value_;
        return true;
    }
};

} // namespace detail
} // namespace czredis