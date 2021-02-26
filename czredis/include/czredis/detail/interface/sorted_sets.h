#pragma once

namespace czredis
{
namespace detail
{

struct i_sorted_sets
{
    virtual void bzpopmax(cref_string key, czint timeout) = 0;
    virtual void bzpopmax(cref_string_array keys, czint timeout) = 0;
    virtual void bzpopmin(cref_string key, czint timeout) = 0;
    virtual void bzpopmin(cref_string_array keys, czint timeout) = 0;
    virtual void zadd(cref_string key, const zadd_param& param, cref_string_array scores_members) = 0;
    virtual void zcard(cref_string key) = 0;
    virtual void zcount(cref_string key, cref_string min, cref_string max) = 0;
    virtual void zincrby(cref_string key, cref_string increment, cref_string member) = 0;
    virtual void zinterstore(cref_string destination, cref_string_array keys, const z_param& param) = 0;
    virtual void zlexcount(cref_string key, cref_string min, cref_string max) = 0;
    virtual void zpopmax(cref_string key) = 0;
    virtual void zpopmax(cref_string key, czint count) = 0;
    virtual void zpopmin(cref_string key) = 0;
    virtual void zpopmin(cref_string key, czint count) = 0;
    virtual void zrange(cref_string key, czint start, czint stop, bool withscores) = 0;
    virtual void zrangebylex(cref_string key, cref_string max, cref_string min) = 0;
    virtual void zrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) = 0;
    virtual void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) = 0;
    virtual void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) = 0;
    virtual void zrank(cref_string key, cref_string member) = 0;
    virtual void zrem(cref_string key, cref_string_array members) = 0;
    virtual void zremrangebylex(cref_string key, cref_string min, cref_string max) = 0;
    virtual void zremrangebyrank(cref_string key, czint start, czint stop) = 0;
    virtual void zremrangebyscore(cref_string key, cref_string min, cref_string max) = 0;
    virtual void zrevrange(cref_string key, czint start, czint stop, bool withscores) = 0;
    virtual void zrevrangebylex(cref_string key, cref_string max, cref_string min) = 0;
    virtual void zrevrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) = 0;
    virtual void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) = 0;
    virtual void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) = 0;
    virtual void zrevrank(cref_string key, cref_string member) = 0;
    virtual void zscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual void zscore(cref_string key, cref_string member) = 0;
    virtual void zunionstore(cref_string destination, cref_string_array keys, const z_param& param) = 0;
};

struct i_one_key_direct_sorted_sets
{
    virtual reply bzpopmax(cref_string key, czint timeout) = 0;
    virtual reply bzpopmin(cref_string key, czint timeout) = 0;
    virtual reply zadd(cref_string key, const zadd_param& param, cref_string_array scores_members) = 0;
    virtual czint zcard(cref_string key) = 0;
    virtual czint zcount(cref_string key, cref_string min, cref_string max) = 0;
    virtual czstring zincrby(cref_string key, cref_string increment, cref_string member) = 0;
    virtual czint zlexcount(cref_string key, cref_string min, cref_string max) = 0;
    virtual string_array zpopmax(cref_string key) = 0;
    virtual string_array zpopmax(cref_string key, czint count) = 0;
    virtual string_array zpopmin(cref_string key) = 0;
    virtual string_array zpopmin(cref_string key, czint count) = 0;
    virtual string_array zrange(cref_string key, czint start, czint stop, bool withscores) = 0;
    virtual string_array zrangebylex(cref_string key, cref_string max, cref_string min) = 0;
    virtual string_array zrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) = 0;
    virtual string_array zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) = 0;
    virtual string_array zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) = 0;
    virtual reply zrank(cref_string key, cref_string member) = 0;
    virtual czint zrem(cref_string key, cref_string_array members) = 0;
    virtual czint zremrangebylex(cref_string key, cref_string min, cref_string max) = 0;
    virtual czint zremrangebyrank(cref_string key, czint start, czint stop) = 0;
    virtual czint zremrangebyscore(cref_string key, cref_string min, cref_string max) = 0;
    virtual string_array zrevrange(cref_string key, czint start, czint stop, bool withscores) = 0;
    virtual string_array zrevrangebylex(cref_string key, cref_string max, cref_string min) = 0;
    virtual string_array zrevrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) = 0;
    virtual string_array zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) = 0;
    virtual string_array zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) = 0;
    virtual reply zrevrank(cref_string key, cref_string member) = 0;
    virtual scan_result zscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual reply zscore(cref_string key, cref_string member) = 0;

};

struct i_direct_sorted_sets
{
    virtual reply bzpopmax(cref_string_array keys, czint timeout) = 0;
    virtual reply bzpopmin(cref_string_array keys, czint timeout) = 0;
    virtual czint zinterstore(cref_string destination, cref_string_array keys, const z_param& param) = 0;
    virtual czint zunionstore(cref_string destination, cref_string_array keys, const z_param& param) = 0;
};

struct i_one_key_delay_sorted_sets
{
    virtual delay<reply> bzpopmax(cref_string key, czint timeout) = 0;
    virtual delay<reply> bzpopmin(cref_string key, czint timeout) = 0;
    virtual delay<reply> zadd(cref_string key, const zadd_param& param, cref_string_array scores_members) = 0;
    virtual delay<czint> zcard(cref_string key) = 0;
    virtual delay<czint> zcount(cref_string key, cref_string min, cref_string max) = 0;
    virtual delay<czstring> zincrby(cref_string key, cref_string increment, cref_string member) = 0;
    virtual delay<czint> zlexcount(cref_string key, cref_string min, cref_string max) = 0;
    virtual delay<string_array> zpopmax(cref_string key) = 0;
    virtual delay<string_array> zpopmax(cref_string key, czint count) = 0;
    virtual delay<string_array> zpopmin(cref_string key) = 0;
    virtual delay<string_array> zpopmin(cref_string key, czint count) = 0;
    virtual delay<string_array> zrange(cref_string key, czint start, czint stop, bool withscores) = 0;
    virtual delay<string_array> zrangebylex(cref_string key, cref_string max, cref_string min) = 0;
    virtual delay<string_array> zrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) = 0;
    virtual delay<string_array> zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) = 0;
    virtual delay<string_array> zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) = 0;
    virtual delay<reply> zrank(cref_string key, cref_string member) = 0;
    virtual delay<czint> zrem(cref_string key, cref_string_array members) = 0;
    virtual delay<czint> zremrangebylex(cref_string key, cref_string min, cref_string max) = 0;
    virtual delay<czint> zremrangebyrank(cref_string key, czint start, czint stop) = 0;
    virtual delay<czint> zremrangebyscore(cref_string key, cref_string min, cref_string max) = 0;
    virtual delay<string_array> zrevrange(cref_string key, czint start, czint stop, bool withscores) = 0;
    virtual delay<string_array> zrevrangebylex(cref_string key, cref_string max, cref_string min) = 0;
    virtual delay<string_array> zrevrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) = 0;
    virtual delay<string_array> zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) = 0;
    virtual delay<string_array> zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) = 0;
    virtual delay<reply> zrevrank(cref_string key, cref_string member) = 0;
    virtual delay<scan_result> zscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual delay<reply> zscore(cref_string key, cref_string member) = 0;
};

struct i_delay_sorted_sets
{
    virtual delay<reply> bzpopmax(cref_string_array keys, czint timeout) = 0;
    virtual delay<reply> bzpopmin(cref_string_array keys, czint timeout) = 0;
    virtual delay<czint> zinterstore(cref_string destination, cref_string_array keys, const z_param& param) = 0;
    virtual delay<czint> zunionstore(cref_string destination, cref_string_array keys, const z_param& param) = 0;
};

} // namespace detail
} // namespace czredis

