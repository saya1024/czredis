#pragma once

namespace czredis
{
namespace detail
{

struct i_lists
{
    virtual void blpop(cref_string key, czint timeout) = 0;
    virtual void blpop(cref_string_array keys, czint timeout) = 0;
    virtual void brpop(cref_string key, czint timeout) = 0;
    virtual void brpop(cref_string_array keys, czint timeout) = 0;
    virtual void brpoplpush(cref_string source, cref_string destination, czint timeout) = 0;
    virtual void lindex(cref_string key, czint index) = 0;
    virtual void linsert(cref_string key, insert_place place, cref_string pivot, cref_string value) = 0;
    virtual void llen(cref_string key) = 0;
    virtual void lpop(cref_string key) = 0;
    virtual void lpush(cref_string key, cref_string_array elements) = 0;
    virtual void lpushx(cref_string key, cref_string_array elements) = 0;
    virtual void lrange(cref_string key, czint start, czint stop) = 0;
    virtual void lrem(cref_string key, czint count, cref_string element) = 0;
    virtual void lset(cref_string key, czint index, cref_string element) = 0;
    virtual void ltrim(cref_string key, czint start, czint stop) = 0;
    virtual void rpop(cref_string key) = 0;
    virtual void rpoplpush(cref_string source, cref_string destination) = 0;
    virtual void rpush(cref_string key, cref_string_array elements) = 0;
    virtual void rpushx(cref_string key, cref_string_array elements) = 0;
};

struct i_one_key_direct_lists
{
    virtual reply blpop(cref_string key, czint timeout) = 0;
    virtual reply brpop(cref_string key, czint timeout) = 0;
    virtual reply lindex(cref_string key, czint index) = 0;
    virtual czint linsert(cref_string key, insert_place place, cref_string pivot, cref_string value) = 0;
    virtual czint llen(cref_string key) = 0;
    virtual reply lpop(cref_string key) = 0;
    virtual czint lpush(cref_string key, cref_string_array elements) = 0;
    virtual czint lpushx(cref_string key, cref_string_array elements) = 0;
    virtual string_array lrange(cref_string key, czint start, czint stop) = 0;
    virtual czint lrem(cref_string key, czint count, cref_string element) = 0;
    virtual czstring lset(cref_string key, czint index, cref_string element) = 0;
    virtual czstring ltrim(cref_string key, czint start, czint stop) = 0;
    virtual reply rpop(cref_string key) = 0;
    virtual czint rpush(cref_string key, cref_string_array elements) = 0;
    virtual czint rpushx(cref_string key, cref_string_array elements) = 0;
};

struct i_direct_lists
{
    virtual reply blpop(cref_string_array keys, czint timeout) = 0;
    virtual reply brpop(cref_string_array keys, czint timeout) = 0;
    virtual reply brpoplpush(cref_string source, cref_string destination, czint timeout) = 0;
    virtual reply rpoplpush(cref_string source, cref_string destination) = 0;
};

struct i_one_key_delay_lists
{
    virtual delay<reply> blpop(cref_string key, czint timeout) = 0;
    virtual delay<reply> brpop(cref_string key, czint timeout) = 0;
    virtual delay<reply> lindex(cref_string key, czint index) = 0;
    virtual delay<czint> linsert(cref_string key, insert_place place, cref_string pivot, cref_string value) = 0;
    virtual delay<czint> llen(cref_string key) = 0;
    virtual delay<reply> lpop(cref_string key) = 0;
    virtual delay<czint> lpush(cref_string key, cref_string_array elements) = 0;
    virtual delay<czint> lpushx(cref_string key, cref_string_array elements) = 0;
    virtual delay<string_array> lrange(cref_string key, czint start, czint stop) = 0;
    virtual delay<czint> lrem(cref_string key, czint count, cref_string element) = 0;
    virtual delay<czstring> lset(cref_string key, czint index, cref_string element) = 0;
    virtual delay<czstring> ltrim(cref_string key, czint start, czint stop) = 0;
    virtual delay<reply> rpop(cref_string key) = 0;
    virtual delay<czint> rpush(cref_string key, cref_string_array elements) = 0;
    virtual delay<czint> rpushx(cref_string key, cref_string_array elements) = 0;
};

struct i_delay_lists
{
    virtual delay<reply> blpop(cref_string_array keys, czint timeout) = 0;
    virtual delay<reply> brpop(cref_string_array keys, czint timeout) = 0;
    virtual delay<reply> brpoplpush(cref_string source, cref_string destination, czint timeout) = 0;
    virtual delay<reply> rpoplpush(cref_string source, cref_string destination) = 0;
};

} // namespace detail
} // namespace czredis

