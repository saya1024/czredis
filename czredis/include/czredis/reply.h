#pragma once

#include "error.h"
#include "detail/move_only.h"

namespace czredis
{

class reply
{
    reply_type          type_;
    czint               int_ = 0;
    czstring            str_;
    std::vector<reply>  arr_;

public:
    using reply_array = std::vector<reply>;

    explicit reply() :
        type_(reply_type::kNull)
    {}

    explicit reply(czstring&& s, bool err = false) :
        type_(err ? reply_type::kError : reply_type::kString),
        str_(std::move(s))
    {}

    explicit reply(czint i) :
        type_(reply_type::kInteger),
        int_(i)
    {}

    explicit reply(reply_array&& arr) :
        type_(reply_type::kArray),
        arr_(std::move(arr))
    {}

    czint as_integer() const
    {
        if (type_ == reply_type::kInteger)
            return int_;
        else if (type_ == reply_type::kError)
            throw redis_commmand_error(str_);
        else
            throw redis_data_error("reply type is not integer");
    }

    czstring& as_string()
    {
        if (type_ == reply_type::kString)
            return str_;
        else if (type_ == reply_type::kError)
            throw redis_commmand_error(str_);
        else
            throw redis_data_error("reply type is not string");
    }

    const czstring& as_string() const
    {
        if (type_ == reply_type::kString)
            return str_;
        else if (type_ == reply_type::kError)
            throw redis_commmand_error(str_);
        else
            throw redis_data_error("reply type is not string");
    }

    reply_array& as_array()
    {
        if (type_ == reply_type::kArray)
            return arr_;
        else if (type_ == reply_type::kError)
            throw redis_commmand_error(str_);
        else
            throw redis_data_error("reply type is not array");
    }

    const reply_array& as_array() const
    {
        if (type_ == reply_type::kArray)
            return arr_;
        else if (type_ == reply_type::kError)
            throw redis_commmand_error(str_);
        else
            throw redis_data_error("reply type is not array");
    }

    czstring& as_error()
    {
        if (type_ == reply_type::kError)
            return str_;
        else
            throw redis_data_error("reply type is not error");
    }

    const czstring& as_error() const
    {
        if (type_ == reply_type::kError)
            return str_;
        else
            throw redis_data_error("reply type is not error");
    }

    bool is_null() const noexcept
    {
        return type_ == reply_type::kNull;
    }

    bool is_integer() const noexcept
    {
        return type_ == reply_type::kInteger;
    }

    bool is_string() const noexcept
    {
        return type_ == reply_type::kString;
    }

    bool is_array() const noexcept
    {
        return type_ == reply_type::kArray;
    }

    bool is_error() const noexcept
    {
        return type_ == reply_type::kError;
    }

    reply_type type() const noexcept
    {
        return type_;
    }
};

using reply_array = std::vector<reply>;
using reply_hmap = hmap<czstring, reply>;

} // namespace czredis


