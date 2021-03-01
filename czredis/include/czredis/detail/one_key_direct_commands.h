#pragma once

#include "call_finally.h"
#include "client.h"

namespace czredis
{
namespace detail
{

class one_key_direct_commands : public i_one_key_direct_commands
{
    virtual client& use_client(cref_string key) = 0;

public:

//geo

    czint geoadd(cref_string key,
        double longitude, double latitude, cref_string member) override final
    {
        auto& c = use_client(key);
        c.geoadd(key, longitude, latitude, member);
        return c.get_reply_as<czint>();
    }

    czint geoadd(cref_string key,
        tmap<czstring, geo_coordinate> members_coordinates) override final
    {
        auto& c = use_client(key);
        c.geoadd(key, members_coordinates);
        return c.get_reply_as<czint>();
    }

    reply geodist(cref_string key,
        cref_string member1, cref_string member2, geo_unit unit) override final
    {
        auto& c = use_client(key);
        c.geodist(key, member1, member2, unit);
        return c.get_reply_as<reply>();
    }

    reply_array geohash(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.geohash(key, members);
        return c.get_reply_as<reply_array>();
    }

    reply_array geopos(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.geopos(key, members);
        return c.get_reply_as<reply_array>();
    }

    reply_array georadius(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        auto& c = use_client(key);
        c.georadius(key, longitude, latitude, radius,
            unit, param, georadius_store_param());
        return c.get_reply_as<reply_array>();
    }

    reply_array georadius_RO(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        auto& c = use_client(key);
        c.georadius_RO(key, longitude, latitude, radius,
            unit, param);
        return c.get_reply_as<reply_array>();
    }

    reply_array georadiusbymember(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        auto& c = use_client(key);
        c.georadiusbymember(key, member, radius, unit,
            param, georadius_store_param());
        return c.get_reply_as<reply_array>();
    }

    reply_array georadiusbymember_RO(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        auto& c = use_client(key);
        c.georadiusbymember_RO(key, member, radius,
            unit, param);
        return c.get_reply_as<reply_array>();
    }

//hashes

    czint hdel(cref_string key,
        cref_string_array fields) override final
    {
        auto& c = use_client(key);
        c.hdel(key, fields);
        return c.get_reply_as<czint>();
    }

    czint hexists(cref_string key,
        cref_string field) override final
    {
        auto& c = use_client(key);
        c.hexists(key, field);
        return c.get_reply_as<czint>();
    }

    reply hget(cref_string key,
        cref_string field) override final
    {
        auto& c = use_client(key);
        c.hget(key, field);
        return c.get_reply_as<reply>();
    }

    reply_array hgetall(cref_string key) override final
    {
        auto& c = use_client(key);
        c.hgetall(key);
        return c.get_reply_as<reply_array>();
    }

    czint hincrby(cref_string key,
        cref_string field, czint increment) override final
    {
        auto& c = use_client(key);
        c.hincrby(key, field, increment);
        return c.get_reply_as<czint>();
    }

    double hincrbyfloat(cref_string key,
        cref_string field, double increment) override final
    {
        auto& c = use_client(key);
        c.hincrbyfloat(key, field, increment);
        return c.get_reply_as<double>();
    }

    string_array hkeys(cref_string key) override final
    {
        auto& c = use_client(key);
        c.hkeys(key);
        return c.get_reply_as<string_array>();
    }

    czint hlen(cref_string key) override final
    {
        auto& c = use_client(key);
        c.hlen(key);
        return c.get_reply_as<czint>();
    }

    reply_array hmget(cref_string key,
        cref_string_array fields) override final
    {
        auto& c = use_client(key);
        c.hmget(key, fields);
        return c.get_reply_as<reply_array>();
    }

    czstring hmset(cref_string key,
        cref_string_array fields_values) override final
    {
        auto& c = use_client(key);
        c.hmset(key, fields_values);
        return c.get_reply_as<czstring>();
    }

    scan_result hscan(cref_string key,
        cref_string cursor,
        const scan_param& param = scan_param()) override final
    {
        auto& c = use_client(key);
        c.hscan(key, cursor, param);
        return c.get_reply_as<scan_result>();
    }

    czint hset(cref_string key,
        cref_string field, cref_string value) override final
    {
        auto& c = use_client(key);
        c.hset(key, field, value);
        return c.get_reply_as<czint>();
    }

    czint hsetnx(cref_string key,
        cref_string field, cref_string value) override final
    {
        auto& c = use_client(key);
        c.hsetnx(key, field, value);
        return c.get_reply_as<czint>();
    }

    czint hstrlen(cref_string key,
        cref_string field) override final
    {
        auto& c = use_client(key);
        c.hstrlen(key, field);
        return c.get_reply_as<czint>();
    }

    string_array hvals(cref_string key) override final
    {
        auto& c = use_client(key);
        c.hvals(key);
        return c.get_reply_as<string_array>();
    }

//hyper_log_log

    czint pfadd(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.pfadd(key, elements);
        return c.get_reply_as<czint>();
    }

    czint pfcount(cref_string key) override final
    {
        auto& c = use_client(key);
        c.pfcount(key);
        return c.get_reply_as<czint>();
    }

//keys

    czint del(cref_string key) override final
    {
        auto& c = use_client(key);
        c.del(key);
        return c.get_reply_as<czint>();
    }

    reply dump(cref_string key) override final
    {
        auto& c = use_client(key);
        c.dump(key);
        return c.get_reply_as<reply>();
    }

    czint exists(cref_string key) override final
    {
        auto& c = use_client(key);
        c.exists(key);
        return c.get_reply_as<czint>();
    }

    czint expire(cref_string key,
        czint seconds) override final
    {
        auto& c = use_client(key);
        c.expire(key, seconds);
        return c.get_reply_as<czint>();
    }

    czint expireat(cref_string key,
        czint timestamp) override final
    {
        auto& c = use_client(key);
        c.expireat(key, timestamp);
        return c.get_reply_as<czint>();
    }

    czstring migrate(cref_string host, cref_string port,
        cref_string key, unsigned destination_db, czint timeout,
        const migrate_param& param = migrate_param()) override final
    {
        auto& c = use_client(key);
        c.migrate(host, port, key, destination_db, timeout, param);
        return c.get_reply_as<czstring>();
    }

    czint move(cref_string key,
        unsigned db) override final
    {
        auto& c = use_client(key);
        c.move(key, db);
        return c.get_reply_as<czint>();
    }

    reply object_refcount(cref_string key) override final
    {
        auto& c = use_client(key);
        c.object_refcount(key);
        return c.get_reply_as<reply>();
    }

    reply object_encoding(cref_string key) override final
    {
        auto& c = use_client(key);
        c.object_encoding(key);
        return c.get_reply_as<reply>();
    }

    reply object_idletime(cref_string key) override final
    {
        auto& c = use_client(key);
        c.object_idletime(key);
        return c.get_reply_as<reply>();
    }

    reply object_freq(cref_string key) override final
    {
        auto& c = use_client(key);
        c.object_freq(key);
        return c.get_reply_as<reply>();
    }

    czint persist(cref_string key) override final
    {
        auto& c = use_client(key);
        c.persist(key);
        return c.get_reply_as<czint>();
    }

    czint pexpire(cref_string key,
        czint milliseconds) override final
    {
        auto& c = use_client(key);
        c.pexpire(key, milliseconds);
        return c.get_reply_as<czint>();
    }

    czint pexpireat(cref_string key,
        czint milliseconds_timestamp) override final
    {
        auto& c = use_client(key);
        c.pexpireat(key, milliseconds_timestamp);
        return c.get_reply_as<czint>();
    }

    czint pttl(cref_string key) override final
    {
        auto& c = use_client(key);
        c.pttl(key);
        return c.get_reply_as<czint>();
    }

    czstring restore(cref_string key,
        czint ttl, cref_string serialized_value,
        const restore_param& param = restore_param()) override final
    {
        auto& c = use_client(key);
        c.restore(key, ttl, serialized_value, param);
        return c.get_reply_as<czstring>();
    }

    string_array sort(cref_string key,
        const sort_param& param = sort_param()) override final
    {
        auto& c = use_client(key);
        c.sort(key, param);
        return c.get_reply_as<string_array>();
    }

    czint touch(cref_string key) override final
    {
        auto& c = use_client(key);
        c.touch(key);
        return c.get_reply_as<czint>();
    }

    czint ttl(cref_string key) override final
    {
        auto& c = use_client(key);
        c.ttl(key);
        return c.get_reply_as<czint>();
    }

    czstring type(cref_string key) override final
    {
        auto& c = use_client(key);
        c.type(key);
        return c.get_reply_as<czstring>();
    }

    czint unlink(cref_string key) override final
    {
        auto& c = use_client(key);
        c.unlink(key);
        return c.get_reply_as<czint>();
    }

//lists

    reply blpop(cref_string key, czint timeout) override final
    {
        auto& c = use_client(key);
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.blpop(key, timeout);
        return c.get_reply_as<reply>();
    }

    reply brpop(cref_string key, czint timeout) override final
    {
        auto& c = use_client(key);
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.brpop(key, timeout);
        return c.get_reply_as<reply>();
    }

    reply lindex(cref_string key,
        czint index) override final
    {
        auto& c = use_client(key);
        c.lindex(key, index);
        return c.get_reply_as<reply>();
    }

    czint linsert(cref_string key,
        insert_place place, cref_string pivot, cref_string value) override final
    {
        auto& c = use_client(key);
        c.linsert(key, place, pivot, value);
        return c.get_reply_as<czint>();
    }

    czint llen(cref_string key) override final
    {
        auto& c = use_client(key);
        c.llen(key);
        return c.get_reply_as<czint>();
    }

    reply lpop(cref_string key) override final
    {
        auto& c = use_client(key);
        c.lpop(key);
        return c.get_reply_as<reply>();
    }

    czint lpush(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.lpush(key, elements);
        return c.get_reply_as<czint>();
    }

    czint lpushx(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.lpushx(key, elements);
        return c.get_reply_as<czint>();
    }

    string_array lrange(cref_string key,
        czint start, czint stop) override final
    {
        auto& c = use_client(key);
        c.lrange(key, start, stop);
        return c.get_reply_as<string_array>();
    }

    czint lrem(cref_string key,
        czint count, cref_string element) override final
    {
        auto& c = use_client(key);
        c.lrem(key, count, element);
        return c.get_reply_as<czint>();
    }

    czstring lset(cref_string key,
        czint index, cref_string element) override final
    {
        auto& c = use_client(key);
        c.lset(key, index, element);
        return c.get_reply_as<czstring>();
    }

    czstring ltrim(cref_string key,
        czint start, czint stop) override final
    {
        auto& c = use_client(key);
        c.ltrim(key, start, stop);
        return c.get_reply_as<czstring>();
    }

    reply rpop(cref_string key) override final
    {
        auto& c = use_client(key);
        c.rpop(key);
        return c.get_reply_as<reply>();
    }

    czint rpush(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.rpush(key, elements);
        return c.get_reply_as<czint>();
    }

    czint rpushx(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.rpushx(key, elements);
        return c.get_reply_as<czint>();
    }

//server

    czint memory_usage(cref_string key) override final
    {
        auto& c = use_client(key);
        c.memory_usage(key);
        return c.get_reply_as<czint>();
    }
    czint memory_usage(cref_string key, czint samples) override final
    {
        auto& c = use_client(key);
        c.memory_usage(key, samples);
        return c.get_reply_as<czint>();
    }

//sets

    czint sadd(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.sadd(key, members);
        return c.get_reply_as<czint>();
    }

    czint scard(cref_string key) override final
    {
        auto& c = use_client(key);
        c.scard(key);
        return c.get_reply_as<czint>();
    }

    czint sismember(cref_string key,
        cref_string member) override final
    {
        auto& c = use_client(key);
        c.sismember(key, member);
        return c.get_reply_as<czint>();
    }

    string_array smembers(cref_string key) override final
    {
        auto& c = use_client(key);
        c.smembers(key);
        return c.get_reply_as<string_array>();
    }

    reply spop(cref_string key) override final
    {
        auto& c = use_client(key);
        c.spop(key);
        return c.get_reply_as<reply>();
    }

    reply spop(cref_string key,
        czint count) override final
    {
        auto& c = use_client(key);
        c.spop(key, count);
        return c.get_reply_as<reply>();
    }

    reply srandmember(cref_string key) override final
    {
        auto& c = use_client(key);
        c.srandmember(key);
        return c.get_reply_as<reply>();
    }

    string_array srandmember(cref_string key,
        czint count) override final
    {
        auto& c = use_client(key);
        c.srandmember(key, count);
        return c.get_reply_as<string_array>();
    }

    czint srem(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.srem(key, members);
        return c.get_reply_as<czint>();
    }

    scan_result sscan(cref_string key,
        cref_string cursor,
        const scan_param& param = scan_param()) override final
    {
        auto& c = use_client(key);
        c.sscan(key, cursor, param);
        return c.get_reply_as<scan_result>();
    }

//sorted_sets

    reply bzpopmax(cref_string key, czint timeout) override final
    {
        auto& c = use_client(key);
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.bzpopmax(key, timeout);
        return c.get_reply_as<reply>();
    }

    reply bzpopmin(cref_string key, czint timeout) override final
    {
        auto& c = use_client(key);
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.bzpopmin(key, timeout);
        return c.get_reply_as<reply>();
    }

    reply zadd(cref_string key,
        const zadd_param& param,
        cref_string_array scores_members) override final
    {
        auto& c = use_client(key);
        c.zadd(key, param, scores_members);
        return c.get_reply_as<reply>();
    }

    czint zcard(cref_string key) override final
    {
        auto& c = use_client(key);
        c.zcard(key);
        return c.get_reply_as<czint>();
    }

    czint zcount(cref_string key,
        cref_string min, cref_string max) override final
    {
        auto& c = use_client(key);
        c.zcount(key, min, max);
        return c.get_reply_as<czint>();
    }

    czstring zincrby(cref_string key,
        cref_string increment, cref_string member) override final
    {
        auto& c = use_client(key);
        c.zincrby(key, increment, member);
        return c.get_reply_as<czstring>();
    }

    czint zlexcount(cref_string key,
        cref_string min, cref_string max) override final
    {
        auto& c = use_client(key);
        c.zlexcount(key, min, max);
        return c.get_reply_as<czint>();
    }

    string_array zpopmax(cref_string key) override final
    {
        auto& c = use_client(key);
        c.zpopmax(key);
        return c.get_reply_as<string_array>();
    }

    string_array zpopmax(cref_string key,
        czint count) override final
    {
        auto& c = use_client(key);
        c.zpopmax(key, count);
        return c.get_reply_as<string_array>();
    }

    string_array zpopmin(cref_string key) override final
    {
        auto& c = use_client(key);
        c.zpopmin(key);
        return c.get_reply_as<string_array>();
    }

    string_array zpopmin(cref_string key,
        czint count) override final
    {
        auto& c = use_client(key);
        c.zpopmin(key, count);
        return c.get_reply_as<string_array>();
    }

    string_array zrange(cref_string key,
        czint start, czint stop,
        bool withscores = false) override final
    {
        auto& c = use_client(key);
        c.zrange(key, start, stop, withscores);
        return c.get_reply_as<string_array>();
    }

    string_array zrangebylex(cref_string key,
        cref_string max, cref_string min) override final
    {
        auto& c = use_client(key);
        c.zrangebylex(key, max, min);
        return c.get_reply_as<string_array>();
    }

    string_array zrangebylex(cref_string key,
        cref_string max, cref_string min,
        czint offset, czint count) override final
    {
        auto& c = use_client(key);
        c.zrangebylex(key, max, min);
        return c.get_reply_as<string_array>();
    }

    string_array zrangebyscore(cref_string key,
        cref_string min, cref_string max,
        bool withscores = false) override final
    {
        auto& c = use_client(key);
        c.zrangebyscore(key, min, max, withscores);
        return c.get_reply_as<string_array>();
    }

    string_array zrangebyscore(cref_string key,
        cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override final
    {
        auto& c = use_client(key);
        c.zrangebyscore(key, min, max, withscores, offset, count);
        return c.get_reply_as<string_array>();
    }

    reply zrank(cref_string key,
        cref_string member) override final
    {
        auto& c = use_client(key);
        c.zrank(key, member);
        return c.get_reply_as<reply>();
    }

    czint zrem(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.zrem(key, members);
        return c.get_reply_as<czint>();
    }

    czint zremrangebylex(cref_string key,
        cref_string min, cref_string max) override final
    {
        auto& c = use_client(key);
        c.zremrangebylex(key, min, max);
        return c.get_reply_as<czint>();
    }

    czint zremrangebyrank(cref_string key,
        czint start, czint stop) override final
    {
        auto& c = use_client(key);
        c.zremrangebyrank(key, start, stop);
        return c.get_reply_as<czint>();
    }

    czint zremrangebyscore(cref_string key,
        cref_string min, cref_string max) override final
    {
        auto& c = use_client(key);
        c.zremrangebyscore(key, min, max);
        return c.get_reply_as<czint>();
    }

    string_array zrevrange(cref_string key,
        czint start, czint stop,
        bool withscores = false) override final
    {
        auto& c = use_client(key);
        c.zrevrange(key, start, stop, withscores);
        return c.get_reply_as<string_array>();
    }

    string_array zrevrangebylex(cref_string key,
        cref_string max, cref_string min) override final
    {
        auto& c = use_client(key);
        c.zrevrangebylex(key, max, min);
        return c.get_reply_as<string_array>();
    }

    string_array zrevrangebylex(cref_string key,
        cref_string max, cref_string min,
        czint offset, czint count) override final
    {
        auto& c = use_client(key);
        c.zrevrangebylex(key, max, min, offset, count);
        return c.get_reply_as<string_array>();
    }

    string_array zrevrangebyscore(cref_string key,
        cref_string min, cref_string max,
        bool withscores) override final
    {
        auto& c = use_client(key);
        c.zrevrangebyscore(key, min, max, withscores);
        return c.get_reply_as<string_array>();
    }

    string_array zrevrangebyscore(cref_string key,
        cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override final
    {
        auto& c = use_client(key);
        c.zrevrangebyscore(key, min, max, withscores, offset, count);
        return c.get_reply_as<string_array>();
    }

    reply zrevrank(cref_string key,
        cref_string member) override final
    {
        auto& c = use_client(key);
        c.zrevrank(key, member);
        return c.get_reply_as<reply>();
    }

    scan_result zscan(cref_string key,
        cref_string cursor,
        const scan_param& param = scan_param()) override final
    {
        auto& c = use_client(key);
        c.zscan(key, cursor, param);
        return c.get_reply_as<scan_result>();
    }

    reply zscore(cref_string key,
        cref_string member) override final
    {
        auto& c = use_client(key);
        c.zscore(key, member);
        return c.get_reply_as<reply>();
    }

//streams

    czint xack(cref_string key,
        cref_string group, cref_stream_id_array ids) override final
    {
        auto& c = use_client(key);
        c.xack(key, group, ids);
        return c.get_reply_as<czint>();
    }

    stream_id xadd(cref_string key,
        const xadd_param param, cref_string id,
        cref_string_array fields_values) override final
    {
        auto& c = use_client(key);
        c.xadd(key, param, id, fields_values);
        return c.get_reply_as<stream_id>();
    }

    stream_entries xclaim(cref_string key,
        cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids,
        const xclaim_param& param = xclaim_param()) override final
    {
        auto& c = use_client(key);
        c.xclaim(key, group, consumer,
            min_idle_time, ids, param);
        return c.get_reply_as<stream_entries>();
    }

    czint xdel(cref_string key,
        cref_stream_id_array ids) override final
    {
        auto& c = use_client(key);
        c.xdel(key, ids);
        return c.get_reply_as<czint>();
    }

    czstring xgroup_create(cref_string key,
        cref_string groupname, cref_string id,
        bool mkstream = false) override final
    {
        auto& c = use_client(key);
        c.xgroup_create(key, groupname, id, mkstream);
        return c.get_reply_as<czstring>();
    }

    czint xgroup_delconsumer(cref_string key,
        cref_string groupname, cref_string consumername) override final
    {
        auto& c = use_client(key);
        c.xgroup_delconsumer(key, groupname, consumername);
        return c.get_reply_as<czint>();
    }

    czint xgroup_destroy(cref_string key,
        cref_string groupname) override final
    {
        auto& c = use_client(key);
        c.xgroup_destroy(key, groupname);
        return c.get_reply_as<czint>();
    }

    czstring xgroup_setid(cref_string key,
        cref_string groupname, cref_string id) override final
    {
        auto& c = use_client(key);
        c.xgroup_setid(key, groupname, id);
        return c.get_reply_as<czstring>();
    }

    std::vector<stream_consumer_info> xinfo_consumers(cref_string key,
        cref_string groupname) override final
    {
        auto& c = use_client(key);
        c.xinfo_consumers(key, groupname);
        return c.get_reply_as<std::vector<stream_consumer_info>>();
    }

    std::vector<stream_group_info> xinfo_groups(cref_string key) override final
    {
        auto& c = use_client(key);
        c.xinfo_groups(key);
        return c.get_reply_as<std::vector<stream_group_info>>();
    }

    stream_info xinfo_stream(cref_string key) override final
    {
        auto& c = use_client(key);
        c.xinfo_stream(key);
        return c.get_reply_as<stream_info>();
    }

    czint xlen(cref_string key) override final
    {
        auto& c = use_client(key);
        c.xlen(key);
        return c.get_reply_as<czint>();
    }

    xpending_overall_result xpending(cref_string key,
        cref_string group) override final
    {
        auto& c = use_client(key);
        c.xpending(key, group);
        return c.get_reply_as<xpending_overall_result>();
    }

    std::vector<xpending_result> xpending(cref_string key,
        cref_string group, cref_string start, cref_string end,
        czint count) override final
    {
        auto& c = use_client(key);
        c.xpending(key, group, start, end, count);
        return c.get_reply_as<std::vector<xpending_result>>();
    }

    std::vector<xpending_result> xpending(cref_string key,
        cref_string group, cref_string start, cref_string end,
        czint count, cref_string consumer) override final
    {
        auto& c = use_client(key);
        c.xpending(key, group, start, end, count, consumer);
        return c.get_reply_as<std::vector<xpending_result>>();
    }

    stream_entries xrange(cref_string key,
        cref_string start, cref_string end) override final
    {
        auto& c = use_client(key);
        c.xrange(key, start, end);
        return c.get_reply_as<stream_entries>();
    }

    stream_entries xrange(cref_string key,
        cref_string start, cref_string end, czint count) override final
    {
        auto& c = use_client(key);
        c.xrange(key, start, end, count);
        return c.get_reply_as<stream_entries>();
    }

    tmap<czstring, stream_entries> xread(const xread_param& param,
        cref_string key, cref_stream_id id) override final
    {
        auto& c = use_client(key);
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        if (param.is_block())
            c.set_read_timeout(0);
        c.xread(param, key, id);
        return c.get_reply_as<tmap<czstring, stream_entries>>();
    }

    tmap<czstring, stream_entries> xreadgroup(cref_string group,
        cref_string consumer, const xread_param& param, bool noack,
        cref_string key, cref_stream_id id) override final
    {
        auto& c = use_client(key);
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        if (param.is_block())
            c.set_read_timeout(0);
        c.xreadgroup(group, consumer, param, noack, key, id);
        return c.get_reply_as<tmap<czstring, stream_entries>>();
    }

    stream_entries xrevrange(cref_string key,
        cref_string end, cref_string start) override final
    {
        auto& c = use_client(key);
        c.xrevrange(key, end, start);
        return c.get_reply_as<stream_entries>();
    }

    stream_entries xrevrange(cref_string key,
        cref_string end, cref_string start, czint count) override final
    {
        auto& c = use_client(key);
        c.xrevrange(key, end, start, count);
        return c.get_reply_as<stream_entries>();
    }

    czint xtrim(cref_string key,
        czint threshold, bool almost_exact = false) override final
    {
        auto& c = use_client(key);
        c.xtrim(key, threshold, almost_exact);
        return c.get_reply_as<czint>();
    }

//string

    czint append(cref_string key,
        cref_string value) override final
    {
        auto& c = use_client(key);
        c.append(key, value);
        return c.get_reply_as<czint>();
    }

    czint bitcount(cref_string key) override final
    {
        auto& c = use_client(key);
        c.bitcount(key);
        return c.get_reply_as<czint>();
    }

    czint bitcount(cref_string key,
        czint start, czint end) override final
    {
        auto& c = use_client(key);
        c.bitcount(key, start, end);
        return c.get_reply_as<czint>();
    }

    reply_array bitfield(cref_string key,
        cref_string_array arguments) override final
    {
        auto& c = use_client(key);
        c.bitfield(key, arguments);
        return c.get_reply_as<reply_array>();
    }

    reply_array bitfield_RO(cref_string key,
        cref_string_array arguments) override final
    {
        auto& c = use_client(key);
        c.bitfield_RO(key, arguments);
        return c.get_reply_as<reply_array>();
    }

    czint bitpos(cref_string key,
        czbit bit,
        const bitpos_param& param = bitpos_param()) override final
    {
        auto& c = use_client(key);
        c.bitpos(key, bit, param);
        return c.get_reply_as<czint>();
    }

    czint decr(cref_string key) override final
    {
        auto& c = use_client(key);
        c.decr(key);
        return c.get_reply_as<czint>();
    }

    czint decrby(cref_string key,
        czint decrement) override final
    {
        auto& c = use_client(key);
        c.decrby(key, decrement);
        return c.get_reply_as<czint>();
    }

    reply get(cref_string key) override final
    {
        auto& c = use_client(key);
        c.get(key);
        return c.get_reply_as<reply>();
    }

    czbit getbit(cref_string key,
        czint offset) override final
    {
        auto& c = use_client(key);
        c.getbit(key, offset);
        return c.get_reply_as<czint>();
    }

    czstring getrange(cref_string key,
        czint start, czint end) override final
    {
        auto& c = use_client(key);
        c.getrange(key, start, end);
        return c.get_reply_as<czstring>();
    }

    reply getset(cref_string key,
        cref_string value) override final
    {
        auto& c = use_client(key);
        c.getset(key, value);
        return c.get_reply_as<reply>();
    }

    czint incr(cref_string key) override final
    {
        auto& c = use_client(key);
        c.incr(key);
        return c.get_reply_as<czint>();
    }

    czint incrby(cref_string key,
        czint increment) override final
    {
        auto& c = use_client(key);
        c.incrby(key, increment);
        return c.get_reply_as<czint>();
    }

    double incrbyfloat(cref_string key,
        double increment) override final
    {
        auto& c = use_client(key);
        c.incrbyfloat(key, increment);
        return c.get_reply_as<double>();
    }

    czstring psetex(cref_string key,
        czint milliseconds, cref_string value) override final
    {
        auto& c = use_client(key);
        c.psetex(key, milliseconds, value);
        return c.get_reply_as<czstring>();
    }

    czstring set(cref_string key,
        cref_string value) override final
    {
        auto& c = use_client(key);
        c.set(key, value);
        return c.get_reply_as<czstring>();
    }

    reply set(cref_string key,
        cref_string value,
        const set_param& param) override final
    {
        auto& c = use_client(key);
        c.set(key, value, param);
        return c.get_reply_as<reply>();
    }

    czbit setbit(cref_string key,
        czint offset, czbit bit) override final
    {
        auto& c = use_client(key);
        c.setbit(key, offset, bit);
        return c.get_reply_as<czint>();
    }

    czstring setex(cref_string key,
        czint seconds, cref_string value) override final
    {
        auto& c = use_client(key);
        c.setex(key, seconds, value);
        return c.get_reply_as<czstring>();
    }

    czint setnx(cref_string key,
        cref_string value) override final
    {
        auto& c = use_client(key);
        c.setnx(key, value);
        return c.get_reply_as<czint>();
    }

    czint setrange(cref_string key,
        czint offset, cref_string value) override final
    {
        auto& c = use_client(key);
        c.setrange(key, offset, value);
        return c.get_reply_as<czint>();
    }

    czint strlen(cref_string key) override final
    {
        auto& c = use_client(key);
        c.strlen(key);
        return c.get_reply_as<czint>();
    }
};

} // namespace detail
} // namespace czredis