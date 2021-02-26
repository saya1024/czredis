#pragma once

namespace czredis
{
namespace detail
{

struct i_hashes
{
    virtual void hdel(cref_string key, cref_string_array fields) = 0;
    virtual void hexists(cref_string key, cref_string field) = 0;
    virtual void hget(cref_string key, cref_string field) = 0;
    virtual void hgetall(cref_string key) = 0;
    virtual void hincrby(cref_string key, cref_string field, czint increment) = 0;
    virtual void hincrbyfloat(cref_string key, cref_string field, double increment) = 0;
    virtual void hkeys(cref_string key) = 0;
    virtual void hlen(cref_string key) = 0;
    virtual void hmget(cref_string key, cref_string_array fields) = 0;
    virtual void hmset(cref_string key, cref_string_array fields_values) = 0;
    virtual void hscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual void hset(cref_string key, cref_string field, cref_string value) = 0;
    virtual void hsetnx(cref_string key, cref_string field, cref_string value) = 0;
    virtual void hstrlen(cref_string key, cref_string field) = 0;
    virtual void hvals(cref_string key) = 0;
};

struct i_one_key_direct_hashes
{
    virtual czint hdel(cref_string key, cref_string_array fields) = 0;
    virtual czint hexists(cref_string key, cref_string field) = 0;
    virtual reply hget(cref_string key, cref_string field) = 0;
    virtual reply_array hgetall(cref_string key) = 0;
    virtual czint hincrby(cref_string key, cref_string field, czint increment) = 0;
    virtual double hincrbyfloat(cref_string key, cref_string field, double increment) = 0;
    virtual string_array hkeys(cref_string key) = 0;
    virtual czint hlen(cref_string key) = 0;
    virtual reply_array hmget(cref_string key, cref_string_array fields) = 0;
    virtual czstring hmset(cref_string key, cref_string_array fields_values) = 0;
    virtual scan_result hscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual czint hset(cref_string key, cref_string field, cref_string value) = 0;
    virtual czint hsetnx(cref_string key, cref_string field, cref_string value) = 0;
    virtual czint hstrlen(cref_string key, cref_string field) = 0;
    virtual string_array hvals(cref_string key) = 0;
};

struct i_direct_hashes
{};

struct i_one_key_delay_hashes
{
    virtual delay<czint> hdel(cref_string key, cref_string_array fields) = 0;
    virtual delay<czint> hexists(cref_string key, cref_string field) = 0;
    virtual delay<reply> hget(cref_string key, cref_string field) = 0;
    virtual delay<reply_array> hgetall(cref_string key) = 0;
    virtual delay<czint> hincrby(cref_string key, cref_string field, czint increment) = 0;
    virtual delay<double> hincrbyfloat(cref_string key, cref_string field, double increment) = 0;
    virtual delay<string_array> hkeys(cref_string key) = 0;
    virtual delay<czint> hlen(cref_string key) = 0;
    virtual delay<reply_array> hmget(cref_string key, cref_string_array fields) = 0;
    virtual delay<czstring> hmset(cref_string key, cref_string_array fields_values) = 0;
    virtual delay<scan_result> hscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual delay<czint> hset(cref_string key, cref_string field, cref_string value) = 0;
    virtual delay<czint> hsetnx(cref_string key, cref_string field, cref_string value) = 0;
    virtual delay<czint> hstrlen(cref_string key, cref_string field) = 0;
    virtual delay<string_array> hvals(cref_string key) = 0;
};

struct i_delay_hashes
{};

} // namespace detail
} // namespace czredis

