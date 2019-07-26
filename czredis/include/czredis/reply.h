#pragma once

namespace czredis
{

class reply
{
public:
    using reply_array = std::vector<reply>;

    reply() noexcept :
        type_(reply_type::kNull)
    {
    }

    reply(rds_string&& s, bool err = false) :
        type_(err ? reply_type::kError : reply_type::kString),
        str_(std::move(s))
    {
    }

    reply(rds_integer i) noexcept :
        type_(reply_type::kInteger),
        int_(i)
    {
    }

    reply(reply_array&& arr) :
        type_(reply_type::kArray),
        arr_(std::move(arr))
    {
    }

    reply(const reply& r) :
        type_(r.type_),
        str_(r.str_),
        int_(r.int_),
        arr_(r.arr_)
    {
    }

    reply(reply&& r) noexcept :
        type_(r.type_),
        str_(std::move(r.str_)),
        int_(r.int_),
        arr_(std::move(r.arr_))
    {
    }

    ~reply() {};

    reply& operator=(const reply& r)
    {
        type_ = r.type_;
        switch (r.type_)
        {
        case reply_type::kString:
        case reply_type::kError:
            str_ = r.str_;
            break;
        case reply_type::kInteger:
            int_ = r.int_;
            break;
        case reply_type::kArray:
            arr_ = r.arr_;
            break;
        }
        return *this;
    }

    reply& operator=(reply&& r) noexcept
    {
        type_ = r.type_;
        str_ = std::move(r.str_);
        int_ = r.int_;
        arr_ = std::move(r.arr_);
    }

    rds_string& as_string()
    {
        if (type_ == reply_type::kString)
            return str_;
        else
            throw redis_data_error("reply type is not string");
    }

    rds_integer as_integer()
    {
        if (type_ == reply_type::kInteger)
            return int_;
        else
            throw redis_data_error("reply type is not integer");
    }

    reply_array& as_array()
    {
        if (type_ == reply_type::kArray)
            return arr_;
        else
            throw redis_data_error("reply type is not array");
    }

    rds_string& as_error()
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

    bool is_string() const noexcept
    {
        return type_ == reply_type::kString;
    }

    bool is_integer() const noexcept
    {
        return type_ == reply_type::kInteger;
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

    bool is_ok()
    {
        return is_string() && str_ == "OK";
    }

    bool is_pong()
    {
        return is_string() && str_ == "PONG";
    }

private:
    reply_type  type_;
    rds_string  str_;
    rds_integer int_;
    reply_array arr_;
};

} // namespace czredis


