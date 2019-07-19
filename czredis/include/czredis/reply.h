#pragma once

namespace czredis
{

class reply
{
    using reply_array = std::vector<reply>;

public:
    reply() noexcept :
        type_(reply_type::kNull)
    {
    }

    reply(const rds_string& s) :
        type_(reply_type::kString),
        str_(s)
    {
    }

    reply(rds_string&& s) noexcept :
        type_(reply_type::kString),
        str_(std::move(s))
    {
    }

    reply(rds_integer i) noexcept :
        type_(reply_type::kInteger),
        int_(i)
    {
    }

    reply(const reply_array& arr) :
        type_(reply_type::kArray),
        arr_(arr)
    {
    }

    reply(reply_array&& arr) noexcept :
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
        if (r.type_ == reply_type::kString)
            str_ = r.str_;
        if (r.type_ == reply_type::kInteger)
            int_ = r.int_;
        if (r.type_ == reply_type::kArray)
            arr_ = r.arr_;
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
            throw std::runtime_error("reply type is not string");
    }

    rds_integer as_integer()
    {
        if (type_ == reply_type::kInteger)
            return int_;
        else
            throw std::runtime_error("reply type is not integer");
    }

    reply_array& as_array()
    {
        if (type_ == reply_type::kArray)
            return arr_;
        else
            throw std::runtime_error("reply type is not array");
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

    bool is_null() const noexcept
    {
        return type_ == reply_type::kNull;
    }

    reply_type type() const noexcept
    {
        return type_;
    }

    void set_null() noexcept
    {
        type_ = reply_type::kNull;
    }

    void set_string(const rds_string& s)
    {
        type_ = reply_type::kString;
        str_ = s;
    }

    void set_string(rds_string&& s) noexcept
    {
        type_ = reply_type::kString;
        str_ = std::move(s);
    }

    void set_integer(rds_integer i) noexcept
    {
        type_ = reply_type::kInteger;
        int_ = i;
    }

    void set_array(const reply_array& arr)
    {
        type_ = reply_type::kArray;
        arr_ = arr;
    }

    void set_array(reply_array&& arr) noexcept
    {
        type_ = reply_type::kArray;
        arr_ = std::move(arr);
    }

private:
    reply_type  type_;
    rds_string  str_;
    rds_integer int_;
    reply_array arr_;
};

} // namespace czredis


