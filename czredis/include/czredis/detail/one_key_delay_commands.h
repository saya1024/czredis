#pragma once

#include "client.h"
#include "delay_queue.h"

namespace czredis
{
namespace detail
{

class one_key_delay_commands : public i_one_key_delay_commands
{
    virtual client& use_client(cref_string key) = 0;

public:

//geo

    delay<czint> geoadd(cref_string key,
        double longitude, double latitude, cref_string member) override final
    {
        auto& c = use_client(key);
        c.geoadd(key, longitude, latitude, member);
        return c.make_delay<czint>();
    }

    delay<czint> geoadd(cref_string key,
        hmap<czstring, geo_coordinate> members_coordinates) override final
    {
        auto& c = use_client(key);
        c.geoadd(key, members_coordinates);
        return c.make_delay<czint>();
    }

    delay<reply> geodist(cref_string key,
        cref_string member1, cref_string member2, geo_unit unit) override final
    {
        auto& c = use_client(key);
        c.geodist(key, member1, member2, unit);
        return c.make_delay<reply>();
    }

    delay<reply_array> geohash(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.geohash(key, members);
        return c.make_delay<reply_array>();
    }

    delay<reply_array> geopos(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.geopos(key, members);
        return c.make_delay<reply_array>();
    }

    delay<reply_array> georadius(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        auto& c = use_client(key);
        c.georadius(key, longitude, latitude, radius,
            unit, param, georadius_store_param());
        return c.make_delay<reply_array>();
    }

    delay<reply_array> georadius_RO(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        auto& c = use_client(key);
        c.georadius_RO(key, longitude, latitude, radius, unit, param);
        return c.make_delay<reply_array>();
    }

    delay<reply_array> georadiusbymember(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        auto& c = use_client(key);
        c.georadiusbymember(key, member, radius,
            unit, param, georadius_store_param());
        return c.make_delay<reply_array>();
    }

    delay<reply_array> georadiusbymember_RO(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        auto& c = use_client(key);
        c.georadiusbymember_RO(key, member, radius, unit, param);
        return c.make_delay<reply_array>();
    }

// hashes

    delay<czint> hdel(cref_string key,
        cref_string_array fields) override final
    {
        auto& c = use_client(key);
        c.hdel(key, fields);
        return c.make_delay<czint>();
    }

    delay<czint> hexists(cref_string key,
        cref_string field) override final
    {
        auto& c = use_client(key);
        c.hexists(key, field);
        return c.make_delay<czint>();
    }

    delay<reply> hget(cref_string key,
        cref_string field) override final
    {
        auto& c = use_client(key);
        c.hget(key, field);
        return c.make_delay<reply>();
    }

    delay<reply_array> hgetall(cref_string key) override final
    {
        auto& c = use_client(key);
        c.hgetall(key);
        return c.make_delay<reply_array>();
    }

    delay<czint> hincrby(cref_string key,
        cref_string field, czint increment) override final
    {
        auto& c = use_client(key);
        c.hincrby(key, field, increment);
        return c.make_delay<czint>();
    }

    delay<double> hincrbyfloat(cref_string key,
        cref_string field, double increment) override final
    {
        auto& c = use_client(key);
        c.hincrbyfloat(key, field, increment);
        return c.make_delay<double>();
    }

    delay<string_array> hkeys(cref_string key) override final
    {
        auto& c = use_client(key);
        c.hkeys(key);
        return c.make_delay<string_array>();
    }

    delay<czint> hlen(cref_string key) override final
    {
        auto& c = use_client(key);
        c.hlen(key);
        return c.make_delay<czint>();
    }

    delay<reply_array> hmget(cref_string key,
        cref_string_array fields) override final
    {
        auto& c = use_client(key);
        c.hmget(key, fields);
        return c.make_delay<reply_array>();
    }

    delay<czstring> hmset(cref_string key,
        cref_string_array fields_values) override final
    {
        auto& c = use_client(key);
        c.hmset(key, fields_values);
        return c.make_delay<czstring>();
    }

    delay<scan_result> hscan(cref_string key,
        cref_string cursor, const scan_param& param = scan_param()) override final
    {
        auto& c = use_client(key);
        c.hscan(key, cursor, param);
        return c.make_delay<scan_result>();
    }

    delay<czint> hset(cref_string key,
        cref_string field, cref_string value) override final
    {
        auto& c = use_client(key);
        c.hset(key, field, value);
        return c.make_delay<czint>();
    }

    delay<czint> hsetnx(cref_string key,
        cref_string field, cref_string value) override final
    {
        auto& c = use_client(key);
        c.hsetnx(key, field, value);
        return c.make_delay<czint>();
    }

    delay<czint> hstrlen(cref_string key,
        cref_string field) override final
    {
        auto& c = use_client(key);
        c.hstrlen(key, field);
        return c.make_delay<czint>();
    }

    delay<string_array> hvals(cref_string key) override final
    {
        auto& c = use_client(key);
        c.hvals(key);
        return c.make_delay<string_array>();
    }

//hyper_log_log
    delay<czint> pfadd(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.pfadd(key, elements);
        return c.make_delay<czint>();
    }

    delay<czint> pfcount(cref_string key) override final
    {
        auto& c = use_client(key);
        c.pfcount(key);
        return c.make_delay<czint>();
    }

//keys

    delay<czint> del(cref_string key) override final
    {
        auto& c = use_client(key);
        c.del(key);
        return c.make_delay<czint>();
    }

    delay<reply> dump(cref_string key) override final
    {
        auto& c = use_client(key);
        c.dump(key);
        return c.make_delay<reply>();
    }

    delay<czint> exists(cref_string key) override final
    {
        auto& c = use_client(key);
        c.exists(key);
        return c.make_delay<czint>();
    }

    delay<czint> expire(cref_string key, czint seconds) override final
    {
        auto& c = use_client(key);
        c.expire(key, seconds);
        return c.make_delay<czint>();
    }

    delay<czint> expireat(cref_string key, czint timestamp) override final
    {
        auto& c = use_client(key);
        c.expireat(key, timestamp);
        return c.make_delay<czint>();
    }

    delay<czstring> migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout,
        const migrate_param& param = migrate_param()) override final
    {
        auto& c = use_client(key);
        c.migrate(host, port, key, destination_db, timeout, param);
        return c.make_delay<czstring>();
    }

    delay<czint> move(cref_string key,
        unsigned db) override final
    {
        auto& c = use_client(key);
        c.move(key, db);
        return c.make_delay<czint>();
    }

    delay<reply> object_refcount(cref_string key) override final
    {
        auto& c = use_client(key);
        c.object_refcount(key);
        return c.make_delay<reply>();
    }

    delay<reply> object_encoding(cref_string key) override final
    {
        auto& c = use_client(key);
        c.object_encoding(key);
        return c.make_delay<reply>();
    }

    delay<reply> object_idletime(cref_string key) override final
    {
        auto& c = use_client(key);
        c.object_idletime(key);
        return c.make_delay<reply>();
    }

    delay<reply> object_freq(cref_string key) override final
    {
        auto& c = use_client(key);
        c.object_freq(key);
        return c.make_delay<reply>();
    }

    delay<czint> persist(cref_string key) override final
    {
        auto& c = use_client(key);
        c.persist(key);
        return c.make_delay<czint>();
    }

    delay<czint> pexpire(cref_string key,
        czint milliseconds) override final
    {
        auto& c = use_client(key);
        c.pexpire(key, milliseconds);
        return c.make_delay<czint>();
    }

    delay<czint> pexpireat(cref_string key,
        czint milliseconds_timestamp) override final
    {
        auto& c = use_client(key);
        c.pexpireat(key, milliseconds_timestamp);
        return c.make_delay<czint>();
    }

    delay<czint> pttl(cref_string key) override final
    {
        auto& c = use_client(key);
        c.pttl(key);
        return c.make_delay<czint>();
    }

    delay<czstring> restore(cref_string key,
        czint ttl, cref_string serialized_value,
        const restore_param& param = restore_param()) override final
    {
        auto& c = use_client(key);
        c.restore(key, ttl, serialized_value, param);
        return c.make_delay<czstring>();
    }

    delay<string_array> sort(cref_string key,
        const sort_param& param = sort_param()) override final
    {
        auto& c = use_client(key);
        c.sort(key, param);
        return c.make_delay<string_array>();
    }

    delay<czint> touch(cref_string key) override final
    {
        auto& c = use_client(key);
        c.touch(key);
        return c.make_delay<czint>();
    }

    delay<czint> ttl(cref_string key) override final
    {
        auto& c = use_client(key);
        c.ttl(key);
        return c.make_delay<czint>();
    }

    delay<czstring> type(cref_string key) override final
    {
        auto& c = use_client(key);
        c.type(key);
        return c.make_delay<czstring>();
    }

    delay<czint> unlink(cref_string key) override final
    {
        auto& c = use_client(key);
        c.unlink(key);
        return c.make_delay<czint>();
    }

//lists

    delay<reply> blpop(cref_string key,
        czint timeout) override final
    {
        auto& c = use_client(key);
        c.blpop(key, timeout);
        return c.make_delay<reply>();
    }

    delay<reply> brpop(cref_string key,
        czint timeout) override final
    {
        auto& c = use_client(key);
        c.brpop(key, timeout);
        return c.make_delay<reply>();
    }

    delay<reply> lindex(cref_string key,
        czint index) override final
    {
        auto& c = use_client(key);
        c.lindex(key, index);
        return c.make_delay<reply>();
    }

    delay<czint> linsert(cref_string key,
        insert_place place, cref_string pivot, cref_string value) override final
    {
        auto& c = use_client(key);
        c.linsert(key, place, pivot, value);
        return c.make_delay<czint>();
    }

    delay<czint> llen(cref_string key) override final
    {
        auto& c = use_client(key);
        c.llen(key);
        return c.make_delay<czint>();
    }

    delay<reply> lpop(cref_string key) override final
    {
        auto& c = use_client(key);
        c.lpop(key);
        return c.make_delay<reply>();
    }

    delay<czint> lpush(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.lpush(key, elements);
        return c.make_delay<czint>();
    }

    delay<czint> lpushx(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.lpushx(key, elements);
        return c.make_delay<czint>();
    }

    delay<string_array> lrange(cref_string key,
        czint start, czint stop) override final
    {
        auto& c = use_client(key);
        c.lrange(key, start, stop);
        return c.make_delay<string_array>();
    }

    delay<czint> lrem(cref_string key,
        czint count, cref_string element) override final
    {
        auto& c = use_client(key);
        c.lrem(key, count, element);
        return c.make_delay<czint>();
    }

    delay<czstring> lset(cref_string key,
        czint index, cref_string element) override final
    {
        auto& c = use_client(key);
        c.lset(key, index, element);
        return c.make_delay<czstring>();
    }

    delay<czstring> ltrim(cref_string key,
        czint start, czint stop) override final
    {
        auto& c = use_client(key);
        c.ltrim(key, start, stop);
        return c.make_delay<czstring>();
    }

    delay<reply> rpop(cref_string key) override final
    {
        auto& c = use_client(key);
        c.rpop(key);
        return c.make_delay<reply>();
    }

    delay<czint> rpush(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.rpush(key, elements);
        return c.make_delay<czint>();
    }

    delay<czint> rpushx(cref_string key,
        cref_string_array elements) override final
    {
        auto& c = use_client(key);
        c.rpushx(key, elements);
        return c.make_delay<czint>();
    }

//server

    delay<czint> memory_usage(cref_string key) override final
    {
        auto& c = use_client(key);
        c.memory_usage(key);
        return c.make_delay<czint>();
    }
    delay<czint> memory_usage(cref_string key, czint samples) override final
    {
        auto& c = use_client(key);
        c.memory_usage(key, samples);
        return c.make_delay<czint>();
    }

//sets

    delay<czint> sadd(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.sadd(key, members);
        return c.make_delay<czint>();
    }

    delay<czint> scard(cref_string key) override final
    {
        auto& c = use_client(key);
        c.scard(key);
        return c.make_delay<czint>();
    }

    delay<czint> sismember(cref_string key,
        cref_string member) override final
    {
        auto& c = use_client(key);
        c.sismember(key, member);
        return c.make_delay<czint>();
    }

    delay<string_array> smembers(cref_string key) override final
    {
        auto& c = use_client(key);
        c.smembers(key);
        return c.make_delay<string_array>();
    }

    delay<reply> spop(cref_string key) override final
    {
        auto& c = use_client(key);
        c.spop(key);
        return c.make_delay<reply>();
    }

    delay<reply> spop(cref_string key,
        czint count) override final
    {
        auto& c = use_client(key);
        c.spop(key, count);
        return c.make_delay<reply>();
    }

    delay<reply> srandmember(cref_string key) override final
    {
        auto& c = use_client(key);
        c.srandmember(key);
        return c.make_delay<reply>();
    }

    delay<string_array> srandmember(cref_string key,
        czint count) override final
    {
        auto& c = use_client(key);
        c.srandmember(key, count);
        return c.make_delay<string_array>();
    }

    delay<czint> srem(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.srem(key, members);
        return c.make_delay<czint>();
    }

    delay<scan_result> sscan(cref_string key,
        cref_string cursor, const scan_param& param = scan_param()) override final
    {
        auto& c = use_client(key);
        c.sscan(key, cursor, param);
        return c.make_delay<scan_result>();
    }

//sorted_sets

    delay<reply> bzpopmax(cref_string key,
        czint timeout) override final
    {
        auto& c = use_client(key);
        c.bzpopmax(key, timeout);
        return c.make_delay<reply>();
    }

    delay<reply> bzpopmin(cref_string key,
        czint timeout) override final
    {
        auto& c = use_client(key);
        c.bzpopmin(key, timeout);
        return c.make_delay<reply>();
    }

    delay<reply> zadd(cref_string key,
        const zadd_param& param,
        cref_string_array scores_members) override final
    {
        auto& c = use_client(key);
        c.zadd(key, param, scores_members);
        return c.make_delay<reply>();
    }

    delay<czint> zcard(cref_string key) override final
    {
        auto& c = use_client(key);
        c.zcard(key);
        return c.make_delay<czint>();
    }

    delay<czint> zcount(cref_string key,
        cref_string min, cref_string max) override final
    {
        auto& c = use_client(key);
        c.zcount(key, min, max);
        return c.make_delay<czint>();
    }

    delay<czstring> zincrby(cref_string key,
        cref_string increment, cref_string member) override final
    {
        auto& c = use_client(key);
        c.zincrby(key, increment, member);
        return c.make_delay<czstring>();
    }

    delay<czint> zlexcount(cref_string key,
        cref_string min, cref_string max) override final
    {
        auto& c = use_client(key);
        c.zlexcount(key, min, max);
        return c.make_delay<czint>();
    }

    delay<string_array> zpopmax(cref_string key) override final
    {
        auto& c = use_client(key);
        c.zpopmax(key);
        return c.make_delay<string_array>();
    }

    delay<string_array> zpopmax(cref_string key,
        czint count) override final
    {
        auto& c = use_client(key);
        c.zpopmax(key, count);
        return c.make_delay<string_array>();
    }

    delay<string_array> zpopmin(cref_string key) override final
    {
        auto& c = use_client(key);
        c.zpopmin(key);
        return c.make_delay<string_array>();
    }

    delay<string_array> zpopmin(cref_string key,
        czint count) override final
    {
        auto& c = use_client(key);
        c.zpopmin(key, count);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrange(cref_string key,
        czint start, czint stop,
        bool withscores = false) override final
    {
        auto& c = use_client(key);
        c.zrange(key, start, stop, withscores);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrangebylex(cref_string key,
        cref_string max, cref_string min) override final
    {
        auto& c = use_client(key);
        c.zrangebylex(key, max, min);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrangebylex(cref_string key,
        cref_string max, cref_string min, czint offset, czint count) override final
    {
        auto& c = use_client(key);
        c.zrangebylex(key, max, min);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrangebyscore(cref_string key,
        cref_string min, cref_string max,
        bool withscores = false) override final
    {
        auto& c = use_client(key);
        c.zrangebyscore(key, min, max, withscores);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrangebyscore(cref_string key,
        cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override final
    {
        auto& c = use_client(key);
        c.zrangebyscore(key, min, max, withscores, offset, count);
        return c.make_delay<string_array>();
    }

    delay<reply> zrank(cref_string key,
        cref_string member) override final
    {
        auto& c = use_client(key);
        c.zrank(key, member);
        return c.make_delay<reply>();
    }

    delay<czint> zrem(cref_string key,
        cref_string_array members) override final
    {
        auto& c = use_client(key);
        c.zrem(key, members);
        return c.make_delay<czint>();
    }

    delay<czint> zremrangebylex(cref_string key,
        cref_string min, cref_string max) override final
    {
        auto& c = use_client(key);
        c.zremrangebylex(key, min, max);
        return c.make_delay<czint>();
    }

    delay<czint> zremrangebyrank(cref_string key,
        czint start, czint stop) override final
    {
        auto& c = use_client(key);
        c.zremrangebyrank(key, start, stop);
        return c.make_delay<czint>();
    }

    delay<czint> zremrangebyscore(cref_string key,
        cref_string min, cref_string max) override final
    {
        auto& c = use_client(key);
        c.zremrangebyscore(key, min, max);
        return c.make_delay<czint>();
    }

    delay<string_array> zrevrange(cref_string key,
        czint start, czint stop,
        bool withscores = false) override final
    {
        auto& c = use_client(key);
        c.zrevrange(key, start, stop, withscores);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrevrangebylex(cref_string key,
        cref_string max, cref_string min) override final
    {
        auto& c = use_client(key);
        c.zrevrangebylex(key, max, min);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrevrangebylex(cref_string key,
        cref_string max, cref_string min, czint offset, czint count) override final
    {
        auto& c = use_client(key);
        c.zrevrangebylex(key, max, min, offset, count);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrevrangebyscore(cref_string key,
        cref_string min, cref_string max,
        bool withscores = false) override final
    {
        auto& c = use_client(key);
        c.zrevrangebyscore(key, min, max, withscores);
        return c.make_delay<string_array>();
    }

    delay<string_array> zrevrangebyscore(cref_string key,
        cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override final
    {
        auto& c = use_client(key);
        c.zrevrangebyscore(key, min, max, withscores, offset, count);
        return c.make_delay<string_array>();
    }

    delay<reply> zrevrank(cref_string key,
        cref_string member) override final
    {
        auto& c = use_client(key);
        c.zrevrank(key, member);
        return c.make_delay<reply>();
    }

    delay<scan_result> zscan(cref_string key,
        cref_string cursor, const scan_param& param = scan_param()) override final
    {
        auto& c = use_client(key);
        c.zscan(key, cursor, param);
        return c.make_delay<scan_result>();
    }

    delay<reply> zscore(cref_string key,
        cref_string member) override final
    {
        auto& c = use_client(key);
        c.zscore(key, member);
        return c.make_delay<reply>();
    }

//streams

    delay<czint> xack(cref_string key,
        cref_string group, cref_stream_id_array ids) override final
    {
        auto& c = use_client(key);
        c.xack(key, group, ids);
        return c.make_delay<czint>();
    }

    delay<stream_id> xadd(cref_string key,
        const xadd_param param, cref_string id,
        cref_string_array fields_values) override final
    {
        auto& c = use_client(key);
        c.xadd(key, param, id, fields_values);
        return c.make_delay<stream_id>();
    }

    delay<stream_entries> xclaim(cref_string key,
        cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids,
        const xclaim_param& param = xclaim_param()) override final
    {
        auto& c = use_client(key);
        c.xclaim(key, group, consumer,
            min_idle_time, ids, param);
        return c.make_delay<stream_entries>();
    }

    delay<czint> xdel(cref_string key,
        cref_stream_id_array ids) override final
    {
        auto& c = use_client(key);
        c.xdel(key, ids);
        return c.make_delay<czint>();
    }

    delay<czstring> xgroup_create(cref_string key,
        cref_string groupname, cref_string id,
        bool mkstream = false) override final
    {
        auto& c = use_client(key);
        c.xgroup_create(key, groupname, id, mkstream);
        return c.make_delay<czstring>();
    }

    delay<czint> xgroup_delconsumer(cref_string key,
        cref_string groupname, cref_string consumername) override final
    {
        auto& c = use_client(key);
        c.xgroup_delconsumer(key, groupname, consumername);
        return c.make_delay<czint>();
    }

    delay<czint> xgroup_destroy(cref_string key,
        cref_string groupname) override final
    {
        auto& c = use_client(key);
        c.xgroup_destroy(key, groupname);
        return c.make_delay<czint>();
    }

    delay<czstring> xgroup_setid(cref_string key,
        cref_string groupname, cref_string id) override final
    {
        auto& c = use_client(key);
        c.xgroup_setid(key, groupname, id);
        return c.make_delay<czstring>();
    }

    delay<std::vector<stream_consumer_info>> xinfo_consumers(cref_string key,
        cref_string groupname) override final
    {
        auto& c = use_client(key);
        c.xinfo_consumers(key, groupname);
        return c.make_delay<std::vector<stream_consumer_info>>();
    }

    delay<std::vector<stream_group_info>> xinfo_groups(cref_string key) override final
    {
        auto& c = use_client(key);
        c.xinfo_groups(key);
        return c.make_delay<std::vector<stream_group_info>>();
    }

    delay<stream_info> xinfo_stream(cref_string key) override final
    {
        auto& c = use_client(key);
        c.xinfo_stream(key);
        return c.make_delay<stream_info>();
    }

    delay<czint> xlen(cref_string key) override final
    {
        auto& c = use_client(key);
        c.xlen(key);
        return c.make_delay<czint>();
    }

    delay<xpending_overall_result> xpending(cref_string key,
        cref_string group) override final
    {
        auto& c = use_client(key);
        c.xpending(key, group);
        return c.make_delay<xpending_overall_result>();
    }

    delay<std::vector<xpending_result>> xpending(cref_string key,
        cref_string group, cref_string start, cref_string end, czint count) override final
    {
        auto& c = use_client(key);
        c.xpending(key, group, start, end, count);
        return c.make_delay<std::vector<xpending_result>>();
    }

    delay<std::vector<xpending_result>> xpending(cref_string key,
        cref_string group, cref_string start, cref_string end, czint count,
        cref_string consumer) override final
    {
        auto& c = use_client(key);
        c.xpending(key, group, start, end, count, consumer);
        return c.make_delay<std::vector<xpending_result>>();
    }

    delay<stream_entries> xrange(cref_string key,
        cref_string start, cref_string end) override final
    {
        auto& c = use_client(key);
        c.xrange(key, start, end);
        return c.make_delay<stream_entries>();
    }

    delay<stream_entries> xrange(cref_string key,
        cref_string start, cref_string end, czint count) override final
    {
        auto& c = use_client(key);
        c.xrange(key, start, end, count);
        return c.make_delay<stream_entries>();
    }

    delay<std::pair<czstring, stream_entries>> xread(
        const xread_param& param, cref_string key,
        cref_stream_id id) override final
    {
        auto& c = use_client(key);
        c.xread(param, key, id);
        return c.make_delay<std::pair<czstring, stream_entries>>();
    }

    delay<std::pair<czstring, stream_entries>> xreadgroup(
        cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string key,
        cref_stream_id id) override final
    {
        auto& c = use_client(key);
        c.xreadgroup(group, consumer, param, noack, key, id);
        return c.make_delay<std::pair<czstring, stream_entries>>();
    }

    delay<stream_entries> xrevrange(cref_string key,
        cref_string end, cref_string start) override final
    {
        auto& c = use_client(key);
        c.xrevrange(key, end, start);
        return c.make_delay<stream_entries>();
    }

    delay<stream_entries> xrevrange(cref_string key,
        cref_string end, cref_string start, czint count) override final
    {
        auto& c = use_client(key);
        c.xrevrange(key, end, start, count);
        return c.make_delay<stream_entries>();
    }

    delay<czint> xtrim(cref_string key,
        czint threshold, bool almost_exact = false) override final
    {
        auto& c = use_client(key);
        c.xtrim(key, threshold, almost_exact);
        return c.make_delay<czint>();
    }

//strings

    delay<czint> append(cref_string key,
        cref_string value) override final
    {
        auto& c = use_client(key);
        c.append(key, value);
        return c.make_delay<czint>();
    }

    delay<czint> bitcount(cref_string key) override final
    {
        auto& c = use_client(key);
        c.bitcount(key);
        return c.make_delay<czint>();
    }

    delay<czint> bitcount(cref_string key,
        czint start, czint end) override final
    {
        auto& c = use_client(key);
        c.bitcount(key, start, end);
        return c.make_delay<czint>();
    }

    delay<reply_array> bitfield(cref_string key,
        cref_string_array arguments) override final
    {
        auto& c = use_client(key);
        c.bitfield(key, arguments);
        return c.make_delay<reply_array>();
    }

    delay<reply_array> bitfield_RO(cref_string key,
        cref_string_array arguments) override final
    {
        auto& c = use_client(key);
        c.bitfield_RO(key, arguments);
        return c.make_delay<reply_array>();
    }

    delay<czint> bitpos(cref_string key,
        czbit bit, const bitpos_param& param = bitpos_param()) override final
    {
        auto& c = use_client(key);
        c.bitpos(key, bit, param);
        return c.make_delay<czint>();
    }

    delay<czint> decr(cref_string key) override final
    {
        auto& c = use_client(key);
        c.decr(key);
        return c.make_delay<czint>();
    }

    delay<czint> decrby(cref_string key,
        czint decrement) override final
    {
        auto& c = use_client(key);
        c.decrby(key, decrement);
        return c.make_delay<czint>();
    }

    delay<reply> get(cref_string key) override final
    {
        auto& c = use_client(key);
        c.get(key);
        return c.make_delay<reply>();
    }

    delay<czbit> getbit(cref_string key,
        czint offset) override final
    {
        auto& c = use_client(key);
        c.getbit(key, offset);
        return c.make_delay<czbit>();
    }

    delay<czstring> getrange(cref_string key,
        czint start, czint end) override final
    {
        auto& c = use_client(key);
        c.getrange(key, start, end);
        return c.make_delay<czstring>();
    }

    delay<reply> getset(cref_string key,
        cref_string value) override final
    {
        auto& c = use_client(key);
        c.getset(key, value);
        return c.make_delay<reply>();
    }

    delay<czint> incr(cref_string key) override final
    {
        auto& c = use_client(key);
        c.incr(key);
        return c.make_delay<czint>();
    }

    delay<czint> incrby(cref_string key,
        czint increment) override final
    {
        auto& c = use_client(key);
        c.incrby(key, increment);
        return c.make_delay<czint>();
    }

    delay<double> incrbyfloat(cref_string key,
        double increment) override final
    {
        auto& c = use_client(key);
        c.incrbyfloat(key, increment);
        return c.make_delay<double>();
    }

    delay<czstring> psetex(cref_string key,
        czint milliseconds, cref_string value) override final
    {
        auto& c = use_client(key);
        c.psetex(key, milliseconds, value);
        return c.make_delay<czstring>();
    }

    delay<czstring> set(cref_string key,
        cref_string value) override final
    {
        auto& c = use_client(key);
        c.set(key, value);
        return c.make_delay<czstring>();
    }

    delay<reply> set(cref_string key,
        cref_string value, const set_param& param) override final
    {
        auto& c = use_client(key);
        c.set(key, value, param);
        return c.make_delay<reply>();
    }

    delay<czbit> setbit(cref_string key,
        czint offset, czbit bit) override final
    {
        auto& c = use_client(key);
        c.setbit(key, offset, bit);
        return c.make_delay<czbit>();
    }

    delay<czstring> setex(cref_string key,
        czint seconds, cref_string value) override final
    {
        auto& c = use_client(key);
        c.setex(key, seconds, value);
        return c.make_delay<czstring>();
    }

    delay<czint> setnx(cref_string key,
        cref_string value) override final
    {
        auto& c = use_client(key);
        c.setnx(key, value);
        return c.make_delay<czint>();
    }

    delay<czint> setrange(cref_string key,
        czint offset, cref_string value) override final
    {
        auto& c = use_client(key);
        c.setrange(key, offset, value);
        return c.make_delay<czint>();
    }

    delay<czint> strlen(cref_string key) override final
    {
        auto& c = use_client(key);
        c.strlen(key);
        return c.make_delay<czint>();
    }
};

} // namespace detail
} // namespace czredis