#pragma once

#include "client.h"
#include "delay_queue.h"

namespace czredis
{
namespace detail
{

class one_key_delay_commands :
    virtual public delay_queue,
    public i_one_key_delay_commands
{
    virtual client& use_client(cref_string key) = 0;

public:

    delay<reply> send_command(cref_string key, cref_string cmd, cref_string_array args)
    {
        use_client(key).send_command({ cmd }, args);
        return make_delay<reply>();
    }

//geo

    delay<czint> geoadd(cref_string key,
        double longitude, double latitude, cref_string member) override final
    {
        use_client(key).geoadd(key, longitude, latitude, member);
        return make_delay<czint>();
    }

    delay<czint> geoadd(cref_string key,
        hmap<czstring, geo_coordinate> members_coordinates) override final
    {
        use_client(key).geoadd(key, members_coordinates);
        return make_delay<czint>();
    }

    delay<reply> geodist(cref_string key,
        cref_string member1, cref_string member2, geo_unit unit) override final
    {
        use_client(key).geodist(key, member1, member2, unit);
        return make_delay<reply>();
    }

    delay<reply_array> geohash(cref_string key,
        cref_string_array members) override final
    {
        use_client(key).geohash(key, members);
        return make_delay<reply_array>();
    }

    delay<reply_array> geopos(cref_string key,
        cref_string_array members) override final
    {
        use_client(key).geopos(key, members);
        return make_delay<reply_array>();
    }

    delay<reply_array> georadius(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        use_client(key).georadius(key, longitude, latitude, radius,
            unit, param, georadius_store_param());
        return make_delay<reply_array>();
    }

    delay<reply_array> georadius_RO(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        use_client(key).georadius_RO(key, longitude, latitude, radius, unit, param);
        return make_delay<reply_array>();
    }

    delay<reply_array> georadiusbymember(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        use_client(key).georadiusbymember(key, member, radius,
            unit, param, georadius_store_param());
        return make_delay<reply_array>();
    }

    delay<reply_array> georadiusbymember_RO(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override final
    {
        use_client(key).georadiusbymember_RO(key, member, radius, unit, param);
        return make_delay<reply_array>();
    }

// hashes

    delay<czint> hdel(cref_string key,
        cref_string_array fields) override final
    {
        use_client(key).hdel(key, fields);
        return make_delay<czint>();
    }

    delay<czint> hexists(cref_string key,
        cref_string field) override final
    {
        use_client(key).hexists(key, field);
        return make_delay<czint>();
    }

    delay<reply> hget(cref_string key,
        cref_string field) override final
    {
        use_client(key).hget(key, field);
        return make_delay<reply>();
    }

    delay<reply_array> hgetall(cref_string key) override final
    {
        use_client(key).hgetall(key);
        return make_delay<reply_array>();
    }

    delay<czint> hincrby(cref_string key,
        cref_string field, czint increment) override final
    {
        use_client(key).hincrby(key, field, increment);
        return make_delay<czint>();
    }

    delay<double> hincrbyfloat(cref_string key,
        cref_string field, double increment) override final
    {
        use_client(key).hincrbyfloat(key, field, increment);
        return make_delay<double>();
    }

    delay<string_array> hkeys(cref_string key) override final
    {
        use_client(key).hkeys(key);
        return make_delay<string_array>();
    }

    delay<czint> hlen(cref_string key) override final
    {
        use_client(key).hlen(key);
        return make_delay<czint>();
    }

    delay<reply_array> hmget(cref_string key,
        cref_string_array fields) override final
    {
        use_client(key).hmget(key, fields);
        return make_delay<reply_array>();
    }

    delay<czstring> hmset(cref_string key,
        cref_string_hmap fields_values) override final
    {
        use_client(key).hmset(key, fields_values);
        return make_delay<czstring>();
    }

    delay<scan_result> hscan(cref_string key,
        cref_string cursor, const scan_param& param = scan_param()) override final
    {
        use_client(key).hscan(key, cursor, param);
        return make_delay<scan_result>();
    }

    delay<czint> hset(cref_string key,
        cref_string field, cref_string value) override final
    {
        use_client(key).hset(key, field, value);
        return make_delay<czint>();
    }

    delay<czint> hsetnx(cref_string key,
        cref_string field, cref_string value) override final
    {
        use_client(key).hsetnx(key, field, value);
        return make_delay<czint>();
    }

    delay<czint> hstrlen(cref_string key,
        cref_string field) override final
    {
        use_client(key).hstrlen(key, field);
        return make_delay<czint>();
    }

    delay<string_array> hvals(cref_string key) override final
    {
        use_client(key).hvals(key);
        return make_delay<string_array>();
    }

//hyper_log_log
    delay<czint> pfadd(cref_string key,
        cref_string_array elements) override final
    {
        use_client(key).pfadd(key, elements);
        return make_delay<czint>();
    }

    delay<czint> pfcount(cref_string key) override final
    {
        use_client(key).pfcount(key);
        return make_delay<czint>();
    }

//keys

    delay<czint> del(cref_string key) override final
    {
        use_client(key).del(key);
        return make_delay<czint>();
    }

    delay<reply> dump(cref_string key) override final
    {
        use_client(key).dump(key);
        return make_delay<reply>();
    }

    delay<czint> exists(cref_string key) override final
    {
        use_client(key).exists(key);
        return make_delay<czint>();
    }

    delay<czint> expire(cref_string key, czint seconds) override final
    {
        use_client(key).expire(key, seconds);
        return make_delay<czint>();
    }

    delay<czint> expireat(cref_string key, czint timestamp) override final
    {
        use_client(key).expireat(key, timestamp);
        return make_delay<czint>();
    }

    delay<czstring> migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout,
        const migrate_param& param = migrate_param()) override final
    {
        use_client(key).migrate(host, port, key, destination_db, timeout, param);
        return make_delay<czstring>();
    }

    delay<czint> move(cref_string key,
        unsigned db) override final
    {
        use_client(key).move(key, db);
        return make_delay<czint>();
    }

    delay<reply> object_refcount(cref_string key) override final
    {
        use_client(key).object_refcount(key);
        return make_delay<reply>();
    }

    delay<reply> object_encoding(cref_string key) override final
    {
        use_client(key).object_encoding(key);
        return make_delay<reply>();
    }

    delay<reply> object_idletime(cref_string key) override final
    {
        use_client(key).object_idletime(key);
        return make_delay<reply>();
    }

    delay<reply> object_freq(cref_string key) override final
    {
        use_client(key).object_freq(key);
        return make_delay<reply>();
    }

    delay<czint> persist(cref_string key) override final
    {
        use_client(key).persist(key);
        return make_delay<czint>();
    }

    delay<czint> pexpire(cref_string key,
        czint milliseconds) override final
    {
        use_client(key).pexpire(key, milliseconds);
        return make_delay<czint>();
    }

    delay<czint> pexpireat(cref_string key,
        czint milliseconds_timestamp) override final
    {
        use_client(key).pexpireat(key, milliseconds_timestamp);
        return make_delay<czint>();
    }

    delay<czint> pttl(cref_string key) override final
    {
        use_client(key).pttl(key);
        return make_delay<czint>();
    }

    delay<czstring> restore(cref_string key,
        czint ttl, cref_string serialized_value,
        const restore_param& param = restore_param()) override final
    {
        use_client(key).restore(key, ttl, serialized_value, param);
        return make_delay<czstring>();
    }

    delay<string_array> sort(cref_string key,
        const sort_param& param = sort_param()) override final
    {
        use_client(key).sort(key, param);
        return make_delay<string_array>();
    }

    delay<czint> touch(cref_string key) override final
    {
        use_client(key).touch(key);
        return make_delay<czint>();
    }

    delay<czint> ttl(cref_string key) override final
    {
        use_client(key).ttl(key);
        return make_delay<czint>();
    }

    delay<czstring> type(cref_string key) override final
    {
        use_client(key).type(key);
        return make_delay<czstring>();
    }

    delay<czint> unlink(cref_string key) override final
    {
        use_client(key).unlink(key);
        return make_delay<czint>();
    }

//lists

    delay<reply> blpop(cref_string key,
        czint timeout) override final
    {
        use_client(key).blpop(key, timeout);
        return make_delay<reply>();
    }

    delay<reply> brpop(cref_string key,
        czint timeout) override final
    {
        use_client(key).brpop(key, timeout);
        return make_delay<reply>();
    }

    delay<reply> lindex(cref_string key,
        czint index) override final
    {
        use_client(key).lindex(key, index);
        return make_delay<reply>();
    }

    delay<czint> linsert(cref_string key,
        insert_place place, cref_string pivot, cref_string value) override final
    {
        use_client(key).linsert(key, place, pivot, value);
        return make_delay<czint>();
    }

    delay<czint> llen(cref_string key) override final
    {
        use_client(key).llen(key);
        return make_delay<czint>();
    }

    delay<reply> lpop(cref_string key) override final
    {
        use_client(key).lpop(key);
        return make_delay<reply>();
    }

    delay<czint> lpush(cref_string key,
        cref_string_array elements) override final
    {
        use_client(key).lpush(key, elements);
        return make_delay<czint>();
    }

    delay<czint> lpushx(cref_string key,
        cref_string_array elements) override final
    {
        use_client(key).lpushx(key, elements);
        return make_delay<czint>();
    }

    delay<string_array> lrange(cref_string key,
        czint start, czint stop) override final
    {
        use_client(key).lrange(key, start, stop);
        return make_delay<string_array>();
    }

    delay<czint> lrem(cref_string key,
        czint count, cref_string element) override final
    {
        use_client(key).lrem(key, count, element);
        return make_delay<czint>();
    }

    delay<czstring> lset(cref_string key,
        czint index, cref_string element) override final
    {
        use_client(key).lset(key, index, element);
        return make_delay<czstring>();
    }

    delay<czstring> ltrim(cref_string key,
        czint start, czint stop) override final
    {
        use_client(key).ltrim(key, start, stop);
        return make_delay<czstring>();
    }

    delay<reply> rpop(cref_string key) override final
    {
        use_client(key).rpop(key);
        return make_delay<reply>();
    }

    delay<czint> rpush(cref_string key,
        cref_string_array elements) override final
    {
        use_client(key).rpush(key, elements);
        return make_delay<czint>();
    }

    delay<czint> rpushx(cref_string key,
        cref_string_array elements) override final
    {
        use_client(key).rpushx(key, elements);
        return make_delay<czint>();
    }

//sets

    delay<czint> sadd(cref_string key,
        cref_string_array members) override final
    {
        use_client(key).sadd(key, members);
        return make_delay<czint>();
    }

    delay<czint> scard(cref_string key) override final
    {
        use_client(key).scard(key);
        return make_delay<czint>();
    }

    delay<czint> sismember(cref_string key,
        cref_string member) override final
    {
        use_client(key).sismember(key, member);
        return make_delay<czint>();
    }

    delay<string_array> smembers(cref_string key) override final
    {
        use_client(key).smembers(key);
        return make_delay<string_array>();
    }

    delay<reply> spop(cref_string key) override final
    {
        use_client(key).spop(key);
        return make_delay<reply>();
    }

    delay<reply> spop(cref_string key,
        czint count) override final
    {
        use_client(key).spop(key, count);
        return make_delay<reply>();
    }

    delay<reply> srandmember(cref_string key) override final
    {
        use_client(key).srandmember(key);
        return make_delay<reply>();
    }

    delay<string_array> srandmember(cref_string key,
        czint count) override final
    {
        use_client(key).srandmember(key, count);
        return make_delay<string_array>();
    }

    delay<czint> srem(cref_string key,
        cref_string_array members) override final
    {
        use_client(key).srem(key, members);
        return make_delay<czint>();
    }

    delay<scan_result> sscan(cref_string key,
        cref_string cursor, const scan_param& param = scan_param()) override final
    {
        use_client(key).sscan(key, cursor, param);
        return make_delay<scan_result>();
    }

//sorted_sets

    delay<reply> bzpopmax(cref_string key,
        czint timeout) override final
    {
        use_client(key).bzpopmax(key, timeout);
        return make_delay<reply>();
    }

    delay<reply> bzpopmin(cref_string key,
        czint timeout) override final
    {
        use_client(key).bzpopmin(key, timeout);
        return make_delay<reply>();
    }

    delay<reply> zadd(cref_string key,
        const zadd_param& param,
        cref_string_hmap members_scores) override final
    {
        use_client(key).zadd(key, param, members_scores);
        return make_delay<reply>();
    }

    delay<czint> zcard(cref_string key) override final
    {
        use_client(key).zcard(key);
        return make_delay<czint>();
    }

    delay<czint> zcount(cref_string key,
        cref_string min, cref_string max) override final
    {
        use_client(key).zcount(key, min, max);
        return make_delay<czint>();
    }

    delay<czstring> zincrby(cref_string key,
        cref_string increment, cref_string member) override final
    {
        use_client(key).zincrby(key, increment, member);
        return make_delay<czstring>();
    }

    delay<czint> zlexcount(cref_string key,
        cref_string min, cref_string max) override final
    {
        use_client(key).zlexcount(key, min, max);
        return make_delay<czint>();
    }

    delay<string_array> zpopmax(cref_string key) override final
    {
        use_client(key).zpopmax(key);
        return make_delay<string_array>();
    }

    delay<string_array> zpopmax(cref_string key,
        czint count) override final
    {
        use_client(key).zpopmax(key, count);
        return make_delay<string_array>();
    }

    delay<string_array> zpopmin(cref_string key) override final
    {
        use_client(key).zpopmin(key);
        return make_delay<string_array>();
    }

    delay<string_array> zpopmin(cref_string key,
        czint count) override final
    {
        use_client(key).zpopmin(key, count);
        return make_delay<string_array>();
    }

    delay<string_array> zrange(cref_string key,
        czint start, czint stop, bool withscores) override final
    {
        use_client(key).zrange(key, start, stop, withscores);
        return make_delay<string_array>();
    }

    delay<string_array> zrangebylex(cref_string key,
        cref_string max, cref_string min) override final
    {
        use_client(key).zrangebylex(key, max, min);
        return make_delay<string_array>();
    }

    delay<string_array> zrangebylex(cref_string key,
        cref_string max, cref_string min, czint offset, czint count) override final
    {
        use_client(key).zrangebylex(key, max, min);
        return make_delay<string_array>();
    }

    delay<string_array> zrangebyscore(cref_string key,
        cref_string min, cref_string max, bool withscores) override final
    {
        use_client(key).zrangebyscore(key, min, max, withscores);
        return make_delay<string_array>();
    }

    delay<string_array> zrangebyscore(cref_string key,
        cref_string min, cref_string max, bool withscores, czint offset, czint count) override final
    {
        use_client(key).zrangebyscore(key, min, max, withscores, offset, count);
        return make_delay<string_array>();
    }

    delay<reply> zrank(cref_string key,
        cref_string member) override final
    {
        use_client(key).zrank(key, member);
        return make_delay<reply>();
    }

    delay<czint> zrem(cref_string key,
        cref_string_array members) override final
    {
        use_client(key).zrem(key, members);
        return make_delay<czint>();
    }

    delay<czint> zremrangebylex(cref_string key,
        cref_string min, cref_string max) override final
    {
        use_client(key).zremrangebylex(key, min, max);
        return make_delay<czint>();
    }

    delay<czint> zremrangebyrank(cref_string key,
        czint start, czint stop) override final
    {
        use_client(key).zremrangebyrank(key, start, stop);
        return make_delay<czint>();
    }

    delay<czint> zremrangebyscore(cref_string key,
        cref_string min, cref_string max) override final
    {
        use_client(key).zremrangebyscore(key, min, max);
        return make_delay<czint>();
    }

    delay<string_array> zrevrange(cref_string key,
        czint start, czint stop, bool withscores) override final
    {
        use_client(key).zrevrange(key, start, stop, withscores);
        return make_delay<string_array>();
    }

    delay<string_array> zrevrangebylex(cref_string key,
        cref_string max, cref_string min) override final
    {
        use_client(key).zrevrangebylex(key, max, min);
        return make_delay<string_array>();
    }

    delay<string_array> zrevrangebylex(cref_string key,
        cref_string max, cref_string min, czint offset, czint count) override final
    {
        use_client(key).zrevrangebylex(key, max, min, offset, count);
        return make_delay<string_array>();
    }

    delay<string_array> zrevrangebyscore(cref_string key,
        cref_string min, cref_string max, bool withscores) override final
    {
        use_client(key).zrevrangebyscore(key, min, max, withscores);
        return make_delay<string_array>();
    }

    delay<string_array> zrevrangebyscore(cref_string key,
        cref_string min, cref_string max, bool withscores, czint offset, czint count) override final
    {
        use_client(key).zrevrangebyscore(key, min, max, withscores, offset, count);
        return make_delay<string_array>();
    }

    delay<reply> zrevrank(cref_string key,
        cref_string member) override final
    {
        use_client(key).zrevrank(key, member);
        return make_delay<reply>();
    }

    delay<scan_result> zscan(cref_string key,
        cref_string cursor, const scan_param& param = scan_param()) override final
    {
        use_client(key).zscan(key, cursor, param);
        return make_delay<scan_result>();
    }

    delay<reply> zscore(cref_string key,
        cref_string member) override final
    {
        use_client(key).zscore(key, member);
        return make_delay<reply>();
    }

//streams

    delay<czint> xack(cref_string key,
        cref_string group, cref_stream_id_array ids) override final
    {
        use_client(key).xack(key, group, ids);
        return make_delay<czint>();
    }

    delay<stream_id> xadd(cref_string key,
        const xadd_param param, cref_string id, cref_string_hmap fields_values) override final
    {
        use_client(key).xadd(key, param, id, fields_values);
        return make_delay<stream_id>();
    }

    delay<stream_entries> xclaim(cref_string key,
        cref_string group, cref_string consumer, czint min_idle_time, cref_stream_id_array ids,
        const xclaim_param& param = xclaim_param()) override final
    {
        use_client(key).xclaim(key, group, consumer, min_idle_time, ids, param);
        return make_delay<stream_entries>();
    }

    delay<czint> xdel(cref_string key,
        cref_stream_id_array ids) override final
    {
        use_client(key).xdel(key, ids);
        return make_delay<czint>();
    }

    delay<czstring> xgroup_create(cref_string key,
        cref_string groupname, cref_string id, bool mkstream) override final
    {
        use_client(key).xgroup_create(key, groupname, id, mkstream);
        return make_delay<czstring>();
    }

    delay<czint> xgroup_delconsumer(cref_string key,
        cref_string groupname, cref_string consumername) override final
    {
        use_client(key).xgroup_delconsumer(key, groupname, consumername);
        return make_delay<czint>();
    }

    delay<czint> xgroup_destroy(cref_string key,
        cref_string groupname) override final
    {
        use_client(key).xgroup_destroy(key, groupname);
        return make_delay<czint>();
    }

    delay<czstring> xgroup_setid(cref_string key,
        cref_string groupname, cref_string id) override final
    {
        use_client(key).xgroup_setid(key, groupname, id);
        return make_delay<czstring>();
    }

    delay<std::vector<stream_consumer_info>> xinfo_consumers(cref_string key,
        cref_string groupname) override final
    {
        use_client(key).xinfo_consumers(key, groupname);
        return make_delay<std::vector<stream_consumer_info>>();
    }

    delay<std::vector<stream_group_info>> xinfo_groups(cref_string key) override final
    {
        use_client(key).xinfo_groups(key);
        return make_delay<std::vector<stream_group_info>>();
    }

    delay<stream_info> xinfo_stream(cref_string key) override final
    {
        use_client(key).xinfo_stream(key);
        return make_delay<stream_info>();
    }

    delay<czint> xlen(cref_string key) override final
    {
        use_client(key).xlen(key);
        return make_delay<czint>();
    }

    delay<xpending_overall_result> xpending(cref_string key,
        cref_string group) override final
    {
        use_client(key).xpending(key, group);
        return make_delay<xpending_overall_result>();
    }

    delay<std::vector<xpending_result>> xpending(cref_string key,
        cref_string group, cref_string start, cref_string end, czint count) override final
    {
        use_client(key).xpending(key, group, start, end, count);
        return make_delay<std::vector<xpending_result>>();
    }

    delay<std::vector<xpending_result>> xpending(cref_string key,
        cref_string group, cref_string start, cref_string end, czint count,
        cref_string consumer) override final
    {
        use_client(key).xpending(key, group, start, end, count, consumer);
        return make_delay<std::vector<xpending_result>>();
    }

    delay<stream_entries> xrange(cref_string key,
        cref_string start, cref_string end) override final
    {
        use_client(key).xrange(key, start, end);
        return make_delay<stream_entries>();
    }

    delay<stream_entries> xrange(cref_string key,
        cref_string start, cref_string end, czint count) override final
    {
        use_client(key).xrange(key, start, end, count);
        return make_delay<stream_entries>();
    }

    delay<std::pair<czstring, stream_entries>> xread(
        const xread_param& param, cref_string key,
        cref_stream_id id) override final
    {
        use_client(key).xread(param, key, id);
        return make_delay<std::pair<czstring, stream_entries>>();
    }

    delay<std::pair<czstring, stream_entries>> xreadgroup(
        cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string key,
        cref_stream_id id) override final
    {
        use_client(key).xreadgroup(group, consumer, param, noack, key, id);
        return make_delay<std::pair<czstring, stream_entries>>();
    }

    delay<stream_entries> xrevrange(cref_string key,
        cref_string end, cref_string start) override final
    {
        use_client(key).xrevrange(key, end, start);
        return make_delay<stream_entries>();
    }

    delay<stream_entries> xrevrange(cref_string key,
        cref_string end, cref_string start, czint count) override final
    {
        use_client(key).xrevrange(key, end, start, count);
        return make_delay<stream_entries>();
    }

    delay<czint> xtrim(cref_string key,
        czint threshold, bool almost_exact = false) override final
    {
        use_client(key).xtrim(key, threshold, almost_exact);
        return make_delay<czint>();
    }

//strings

    delay<czint> append(cref_string key,
        cref_string value) override final
    {
        use_client(key).append(key, value);
        return make_delay<czint>();
    }

    delay<czint> bitcount(cref_string key) override final
    {
        use_client(key).bitcount(key);
        return make_delay<czint>();
    }

    delay<czint> bitcount(cref_string key,
        czint start, czint end) override final
    {
        use_client(key).bitcount(key, start, end);
        return make_delay<czint>();
    }

    delay<reply_array> bitfield(cref_string key,
        cref_string_array arguments) override final
    {
        use_client(key).bitfield(key, arguments);
        return make_delay<reply_array>();
    }

    delay<reply_array> bitfield_RO(cref_string key,
        cref_string_array arguments) override final
    {
        use_client(key).bitfield_RO(key, arguments);
        return make_delay<reply_array>();
    }

    delay<czint> bitpos(cref_string key,
        czbit bit, const bitpos_param& param = bitpos_param()) override final
    {
        use_client(key).bitpos(key, bit, param);
        return make_delay<czint>();
    }

    delay<czint> decr(cref_string key) override final
    {
        use_client(key).decr(key);
        return make_delay<czint>();
    }

    delay<czint> decrby(cref_string key,
        czint decrement) override final
    {
        use_client(key).decrby(key, decrement);
        return make_delay<czint>();
    }

    delay<reply> get(cref_string key) override final
    {
        use_client(key).get(key);
        return make_delay<reply>();
    }

    delay<czbit> getbit(cref_string key,
        czint offset) override final
    {
        use_client(key).getbit(key, offset);
        return make_delay<czbit>();
    }

    delay<czstring> getrange(cref_string key,
        czint start, czint end) override final
    {
        use_client(key).getrange(key, start, end);
        return make_delay<czstring>();
    }

    delay<reply> getset(cref_string key,
        cref_string value) override final
    {
        use_client(key).getset(key, value);
        return make_delay<reply>();
    }

    delay<czint> incr(cref_string key) override final
    {
        use_client(key).incr(key);
        return make_delay<czint>();
    }

    delay<czint> incrby(cref_string key,
        czint increment) override
    {
        use_client(key).incrby(key, increment);
        return make_delay<czint>();
    }

    delay<double> incrbyfloat(cref_string key,
        double increment) override final
    {
        use_client(key).incrbyfloat(key, increment);
        return make_delay<double>();
    }

    delay<czstring> psetex(cref_string key,
        czint milliseconds, cref_string value) override final
    {
        use_client(key).psetex(key, milliseconds, value);
        return make_delay<czstring>();
    }

    delay<reply> set(cref_string key,
        cref_string value, const set_param& param = set_param()) override final
    {
        use_client(key).set(key, value, param);
        return make_delay<reply>();
    }

    delay<czbit> setbit(cref_string key,
        czint offset, czbit bit) override final
    {
        use_client(key).setbit(key, offset, bit);
        return make_delay<czbit>();
    }

    delay<czstring> setex(cref_string key,
        czint seconds, cref_string value) override final
    {
        use_client(key).setex(key, seconds, value);
        return make_delay<czstring>();
    }

    delay<czint> setnx(cref_string key,
        cref_string value) override final
    {
        use_client(key).setnx(key, value);
        return make_delay<czint>();
    }

    delay<czint> setrange(cref_string key,
        czint offset, cref_string value) override final
    {
        use_client(key).setrange(key, offset, value);
        return make_delay<czint>();
    }

    delay<czint> strlen(cref_string key) override final
    {
        use_client(key).strlen(key);
        return make_delay<czint>();
    }
};

} // namespace detail
} // namespace czredis