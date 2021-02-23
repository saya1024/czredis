#pragma once

namespace czredis
{
namespace detail
{

struct i_keys
{
    virtual void del(cref_string key) = 0;
    virtual void del(cref_string_array keys) = 0;
    virtual void dump(cref_string key) = 0;
    virtual void exists(cref_string key) = 0;
    virtual void expire(cref_string key, czint seconds) = 0;
    virtual void expireat(cref_string key, czint timestamp) = 0;
    virtual void keys(cref_string pattern) = 0;
    virtual void migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout, const migrate_param& param) = 0;
    virtual void migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param, cref_string_array keys) = 0;
    virtual void move(cref_string key, unsigned db) = 0;
    virtual void object_refcount(cref_string key) = 0;
    virtual void object_encoding(cref_string key) = 0;
    virtual void object_idletime(cref_string key) = 0;
    virtual void object_freq(cref_string key) = 0;
    virtual void object_help() = 0;
    virtual void persist(cref_string key) = 0;
    virtual void pexpire(cref_string key, czint milliseconds) = 0;
    virtual void pexpireat(cref_string key, czint milliseconds_timestamp) = 0;
    virtual void pttl(cref_string key) = 0;
    virtual void randomkey() = 0;
    virtual void rename(cref_string key, cref_string new_key) = 0;
    virtual void renamenx(cref_string key, cref_string new_key) = 0;
    virtual void restore(cref_string key, czint ttl, cref_string serialized_value,
        const restore_param& param) = 0;
    virtual void scan(cref_string cursor, const scan_param& param) = 0;
    virtual void scan(cref_string cursor, const scan_param& param, redis_key_type type) = 0;
    virtual void sort(cref_string key, const sort_param& param) = 0;
    virtual void sort(cref_string key, const sort_param& param, cref_string destination) = 0;
    virtual void touch(cref_string key) = 0;
    virtual void touch(cref_string_array keys) = 0;
    virtual void ttl(cref_string key) = 0;
    virtual void type(cref_string key) = 0;
    virtual void unlink(cref_string key) = 0;
    virtual void unlink(cref_string_array keys) = 0;
    virtual void wait(unsigned numreplicas, czint timeout) = 0;
};

struct i_one_key_direct_keys
{
    virtual czint del(cref_string key) = 0;
    virtual reply dump(cref_string key) = 0;
    virtual czint exists(cref_string key) = 0;
    virtual czint expire(cref_string key, czint seconds) = 0;
    virtual czint expireat(cref_string key, czint timestamp) = 0;
    virtual czstring migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout, const migrate_param& param) = 0;
    virtual czint move(cref_string key, unsigned db) = 0;
    virtual reply object_refcount(cref_string key) = 0;
    virtual reply object_encoding(cref_string key) = 0;
    virtual reply object_idletime(cref_string key) = 0;
    virtual reply object_freq(cref_string key) = 0;
    virtual czint persist(cref_string key) = 0;
    virtual czint pexpire(cref_string key, czint milliseconds) = 0;
    virtual czint pexpireat(cref_string key, czint milliseconds_timestamp) = 0;
    virtual czint pttl(cref_string key) = 0;
    virtual czstring restore(cref_string key, czint ttl, cref_string serialized_value,
        const restore_param& param) = 0;
    virtual string_array sort(cref_string key, const sort_param& param) = 0;
    virtual czint touch(cref_string key) = 0;
    virtual czint ttl(cref_string key) = 0;
    virtual czstring type(cref_string key) = 0;
    virtual czint unlink(cref_string key) = 0;
};

struct i_direct_keys
{
    virtual czint del(cref_string_array keys) = 0;
    virtual string_array keys(cref_string pattern) = 0;
    virtual czstring migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param, cref_string_array keys) = 0;
    virtual string_array object_help() = 0;
    virtual reply randomkey() = 0;
    virtual czstring rename(cref_string key, cref_string new_key) = 0;
    virtual czint renamenx(cref_string key, cref_string new_key) = 0;
    virtual scan_result scan(cref_string cursor, const scan_param& param) = 0;
    virtual scan_result scan(cref_string cursor, const scan_param& param, redis_key_type type) = 0;
    virtual czint sort(cref_string key, const sort_param& param, cref_string destination) = 0;
    virtual czint touch(cref_string_array keys) = 0;
    virtual czint unlink(cref_string_array keys) = 0;
    virtual czint wait(unsigned numreplicas, czint timeout) = 0;
};

struct i_one_key_delay_keys
{
    virtual delay<czint> del(cref_string key) = 0;
    virtual delay<reply> dump(cref_string key) = 0;
    virtual delay<czint> exists(cref_string key) = 0;
    virtual delay<czint> expire(cref_string key, czint seconds) = 0;
    virtual delay<czint> expireat(cref_string key, czint timestamp) = 0;
    virtual delay<czstring> migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout, const migrate_param& param) = 0;
    virtual delay<czint> move(cref_string key, unsigned db) = 0;
    virtual delay<reply> object_refcount(cref_string key) = 0;
    virtual delay<reply> object_encoding(cref_string key) = 0;
    virtual delay<reply> object_idletime(cref_string key) = 0;
    virtual delay<reply> object_freq(cref_string key) = 0;
    virtual delay<czint> persist(cref_string key) = 0;
    virtual delay<czint> pexpire(cref_string key, czint milliseconds) = 0;
    virtual delay<czint> pexpireat(cref_string key, czint milliseconds_timestamp) = 0;
    virtual delay<czint> pttl(cref_string key) = 0;
    virtual delay<czstring> restore(cref_string key, czint ttl, cref_string serialized_value,
        const restore_param& param) = 0;
    virtual delay<string_array> sort(cref_string key, const sort_param& param) = 0;
    virtual delay<czint> touch(cref_string key) = 0;
    virtual delay<czint> ttl(cref_string key) = 0;
    virtual delay<czstring> type(cref_string key) = 0;
    virtual delay<czint> unlink(cref_string key) = 0;
};

struct i_delay_keys
{
    virtual delay<czint> del(cref_string_array keys) = 0;
    virtual delay<string_array> keys(cref_string pattern) = 0;
    virtual delay<czstring> migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param, cref_string_array keys) = 0;
    virtual delay<string_array> object_help() = 0;
    virtual delay<reply> randomkey() = 0;
    virtual delay<czstring> rename(cref_string key, cref_string new_key) = 0;
    virtual delay<czint> renamenx(cref_string key, cref_string new_key) = 0;
    virtual delay<scan_result> scan(cref_string cursor, const scan_param& param) = 0;
    virtual delay<scan_result> scan(cref_string cursor, const scan_param& param, redis_key_type type) = 0;
    virtual delay<czint> sort(cref_string key, const sort_param& param, cref_string destination) = 0;
    virtual delay<czint> touch(cref_string_array keys) = 0;
    virtual delay<czint> unlink(cref_string_array keys) = 0;
    virtual delay<czint> wait(unsigned numreplicas, czint timeout) = 0;
};

} // namespace detail
} // namespace czredis

