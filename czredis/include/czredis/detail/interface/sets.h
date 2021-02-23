#pragma once

namespace czredis
{
namespace detail
{

struct i_sets
{
    virtual void sadd(cref_string key, cref_string_array members) = 0;
    virtual void scard(cref_string key) = 0;
    virtual void sdiff(cref_string_array keys) = 0;
    virtual void sdiffstore(cref_string destination, cref_string_array keys) = 0;
    virtual void sinter(cref_string_array keys) = 0;
    virtual void sinterstore(cref_string destination, cref_string_array keys) = 0;
    virtual void sismember(cref_string key, cref_string member) = 0;
    virtual void smembers(cref_string key) = 0;
    virtual void smove(cref_string source, cref_string destination, cref_string member) = 0;
    virtual void spop(cref_string key) = 0;
    virtual void spop(cref_string key, czint count) = 0;
    virtual void srandmember(cref_string key) = 0;
    virtual void srandmember(cref_string key, czint count) = 0;
    virtual void srem(cref_string key, cref_string_array members) = 0;
    virtual void sscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual void sunion(cref_string_array keys) = 0;
    virtual void sunionstore(cref_string destination, cref_string_array keys) = 0;
};

struct i_one_key_direct_sets
{
    virtual czint sadd(cref_string key, cref_string_array members) = 0;
    virtual czint scard(cref_string key) = 0;
    virtual czint sismember(cref_string key, cref_string member) = 0;
    virtual string_array smembers(cref_string key) = 0;
    virtual reply spop(cref_string key) = 0;
    virtual reply spop(cref_string key, czint count) = 0;
    virtual reply srandmember(cref_string key) = 0;
    virtual string_array srandmember(cref_string key, czint count) = 0;
    virtual czint srem(cref_string key, cref_string_array members) = 0;
    virtual scan_result sscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
};

struct i_direct_sets
{
    virtual string_array sdiff(cref_string_array keys) = 0;
    virtual czint sdiffstore(cref_string destination, cref_string_array keys) = 0;
    virtual string_array sinter(cref_string_array keys) = 0;
    virtual czint sinterstore(cref_string destination, cref_string_array keys) = 0;
    virtual czint smove(cref_string source, cref_string destination, cref_string member) = 0;
    virtual string_array sunion(cref_string_array keys) = 0;
    virtual czint sunionstore(cref_string destination, cref_string_array keys) = 0;
};

struct i_one_key_delay_sets
{
    virtual delay<czint> sadd(cref_string key, cref_string_array members) = 0;
    virtual delay<czint> scard(cref_string key) = 0;
    virtual delay<czint> sismember(cref_string key, cref_string member) = 0;
    virtual delay<string_array> smembers(cref_string key) = 0;
    virtual delay<reply> spop(cref_string key) = 0;
    virtual delay<reply> spop(cref_string key, czint count) = 0;
    virtual delay<reply> srandmember(cref_string key) = 0;
    virtual delay<string_array> srandmember(cref_string key, czint count) = 0;
    virtual delay<czint> srem(cref_string key, cref_string_array members) = 0;
    virtual delay<scan_result> sscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
};

struct i_delay_sets
{
    virtual delay<string_array> sdiff(cref_string_array keys) = 0;
    virtual delay<czint> sdiffstore(cref_string destination, cref_string_array keys) = 0;
    virtual delay<string_array> sinter(cref_string_array keys) = 0;
    virtual delay<czint> sinterstore(cref_string destination, cref_string_array keys) = 0;
    virtual delay<czint> smove(cref_string source, cref_string destination, cref_string member) = 0;
    virtual delay<string_array> sunion(cref_string_array keys) = 0;
    virtual delay<czint> sunionstore(cref_string destination, cref_string_array keys) = 0;
};

} // namespace detail
} // namespace czredis

