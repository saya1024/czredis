#pragma once

#include "detail/client.h"

namespace czredis
{

class pipeline : public detail::interface_commands
{
    using client = detail::client;
    friend class redis;

public:
    reply_array sync_commands()
    {
        return client_.get_all_reply();
    }

    bool exec_and_sync(reply_array& results)
    {
        exec();
        auto r = sync_commands();
        if (r.back().is_array())
        {
            results = std::move(r.back().as_array());
            return true;
        }
        return false;
    }

    bool is_in_multi() const noexcept
    {
        return client_.is_in_multi();
    }

    bool is_in_watch() const noexcept
    {
        return client_.is_in_watch();
    }

//connection

    virtual void auth(cref_string password) override
    {
        client_.auth(password);
    }

    virtual void auth(cref_string username, cref_string password) override
    {
        client_.auth(username, password);
    }

    virtual void echo(cref_string message) override
    {
        client_.echo(message);
    }

    virtual void ping() override
    {
        client_.ping();
    }

    virtual void quit() override
    {
        client_.quit();
        client_.disconnect();
    }

    virtual void select(unsigned index) override
    {
        client_.select(index);
    }

//geo

    virtual void geoadd(cref_string key, double longitude, double latitude,
        cref_string member) override
    {
        client_.geoadd(key, longitude, latitude, member);
    }

    virtual void geoadd(cref_string key,
        std::map<czstring, geo_coordinate> member_coordinate_map) override
    {
        client_.geoadd(key, member_coordinate_map);
    }

    virtual void geodist(cref_string key, cref_string member1,
        cref_string member2, geo_unit unit) override
    {
        client_.geodist(key, member1, member2, unit);
    }

    virtual void geohash(cref_string key, cref_string_array members) override
    {
        client_.geohash(key, members);
    }

    virtual void geopos(cref_string key, cref_string_array members) override
    {
        client_.geopos(key, members);
    }

    virtual void georadius(cref_string key, double longitude, double latitude,
        double radius, geo_unit unit,
        const georadius_param& param = georadius_param(),
        const georadius_store_param& store_param = georadius_store_param()) override
    {
        client_.georadius(key, longitude, latitude, radius,
            unit, param, store_param);
    }

    virtual void georadius_RO(cref_string key, double longitude, double latitude,
        double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override
    {
        client_.georadius_RO(key, longitude, latitude, radius, unit, param);
    }

    virtual void georadiusbymember(cref_string key, cref_string member,
        double radius, geo_unit unit,
        const georadius_param& param = georadius_param(),
        const georadius_store_param& store_param = georadius_store_param()) override
    {
        client_.georadiusbymember(key, member, radius, unit, param, store_param);
    }

    virtual void georadiusbymember_RO(cref_string key, cref_string member,
        double radius, geo_unit unit,
        const georadius_param& param = georadius_param()) override
    {
        client_.georadiusbymember_RO(key, member, radius, unit, param);
    }

// hashes

    virtual void hdel(cref_string key, cref_string_array fields) override
    {
        client_.hdel(key, fields);
    }

    virtual void hexists(cref_string key, cref_string field) override
    {
        client_.hexists(key, field);
    }

    virtual void hget(cref_string key, cref_string field) override
    {
        client_.hget(key, field);
    }

    virtual void hgetall(cref_string key) override
    {
        client_.hgetall(key);
    }

    virtual void hincrby(cref_string key, cref_string field,
        czint increment) override
    {
        client_.hincrby(key, field, increment);
    }

    virtual void hincrbyfloat(cref_string key, cref_string field,
        double increment) override
    {
        client_.hincrbyfloat(key, field, increment);
    }

    virtual void hkeys(cref_string key) override
    {
        client_.hkeys(key);
    }

    virtual void hlen(cref_string key) override
    {
        client_.hlen(key);
    }

    virtual void hmget(cref_string key, cref_string_array fields) override
    {
        client_.hmget(key, fields);
    }

    virtual void hmset(cref_string key, cref_string_map field_value_map) override
    {
        client_.hmset(key, field_value_map);
    }

    virtual void hscan(cref_string key, cref_string cursor,
        const scan_param& param = scan_param()) override
    {
        client_.hscan(key, cursor, param);
    }

    virtual void hset(cref_string key, cref_string field,
        cref_string value) override
    {
        client_.hset(key, field, value);
    }

    virtual void hsetnx(cref_string key, cref_string field,
        cref_string value) override
    {
        client_.hsetnx(key, field, value);
    }

    virtual void hstrlen(cref_string key, cref_string field) override
    {
        client_.hstrlen(key, field);
    }

    virtual void hvals(cref_string key) override
    {
        client_.hvals(key);
    }

//hyper_log_log
    virtual void pfadd(cref_string key, cref_string_array elements) override
    {
        client_.pfadd(key, elements);
    }

    virtual void pfcount(cref_string_array keys) override
    {
        client_.pfcount(keys);
    }

    virtual void pfmerge(cref_string destkey, cref_string_array sourcekeys) override
    {
        client_.pfmerge(destkey, sourcekeys);
    }

//keys

    virtual void del(cref_string_array keys) override
    {
        client_.del(keys);
    }

    virtual void dump(cref_string key) override
    {
        client_.dump(key);
    }

    virtual void exists(cref_string key) override
    {
        client_.exists(key);
    }

    virtual void expire(cref_string key, czint seconds) override
    {
        client_.expire(key, seconds);
    }

    virtual void expireat(cref_string key, czint timestamp) override
    {
        client_.expireat(key, timestamp);
    }

    virtual void keys(cref_string pattern) override
    {
        client_.keys(pattern);
    }

    virtual void migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout,
        const migrate_param& param = migrate_param()) override
    {
        client_.migrate(host, port, key, destination_db, timeout, param);
    }

    virtual void migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param,
        cref_string_array keys) override
    {
        client_.migrate(host, port, destination_db, timeout, param, keys);
    }

    virtual void move(cref_string key, unsigned db) override
    {
        client_.move(key, db);
    }

    virtual void object_refcount(cref_string key) override
    {
        client_.object_refcount(key);
    }

    virtual void object_encoding(cref_string key) override
    {
        client_.object_encoding(key);
    }

    virtual void object_idletime(cref_string key) override
    {
        client_.object_idletime(key);
    }

    virtual void object_freq(cref_string key) override
    {
        client_.object_freq(key);
    }

    virtual void object_help() override
    {
        client_.object_help();
    }

    virtual void persist(cref_string key) override
    {
        client_.persist(key);
    }

    virtual void pexpire(cref_string key, czint milliseconds) override
    {
        client_.pexpire(key, milliseconds);
    }

    virtual void pexpireat(cref_string key, czint milliseconds_timestamp) override
    {
        client_.pexpireat(key, milliseconds_timestamp);
    }

    virtual void pttl(cref_string key) override
    {
        client_.pttl(key);
    }

    virtual void randomkey() override
    {
        client_.randomkey();
    }

    virtual void rename(cref_string key, cref_string new_key) override
    {
        client_.rename(key, new_key);
    }

    virtual void renamenx(cref_string key, cref_string new_key) override
    {
        client_.renamenx(key, new_key);
    }

    virtual void restore(cref_string key, czint ttl,
        cref_string serialized_value,
        const restore_param& param = restore_param()) override
    {
        client_.restore(key, ttl, serialized_value, param);
    }

    virtual void scan(cref_string cursor,
        const scan_param& param = scan_param()) override
    {
        client_.scan(cursor, param);
    }

    virtual void scan(cref_string cursor,
        const scan_param& param, redis_key_type type) override
    {
        client_.scan(cursor, param, type);
    }

    virtual void sort(cref_string key,
        const sort_param& param = sort_param()) override
    {
        client_.sort(key, param);
    }

    virtual void touch(cref_string_array keys) override
    {
        client_.touch(keys);
    }

    virtual void ttl(cref_string key) override
    {
        client_.ttl(key);
    }

    virtual void type(cref_string key) override
    {
        client_.type(key);
    }

    virtual void unlink(cref_string_array keys) override
    {
        client_.unlink(keys);
    }

    virtual void wait(unsigned numreplicas, czint timeout) override
    {
        client_.wait(numreplicas, timeout);
    }

//lists

    virtual void blpop(cref_string_array keys, czint timeout) override
    {
        client_.blpop(keys, timeout);
    }

    virtual void brpop(cref_string_array keys, czint timeout) override
    {
        client_.brpop(keys, timeout);
    }

    virtual void brpoplpush(cref_string source, cref_string destination,
        czint timeout) override
    {
        client_.brpoplpush(source, destination, timeout);
    }

    virtual void lindex(cref_string key, czint index) override
    {
        client_.lindex(key, index);
    }

    virtual void linsert(cref_string key, insert_place place,
        cref_string pivot, cref_string value) override
    {
        client_.linsert(key, place, pivot, value);
    }

    virtual void llen(cref_string key) override
    {
        client_.llen(key);
    }

    virtual void lpop(cref_string key) override
    {
        client_.lpop(key);
    }

    virtual void lpush(cref_string key, cref_string_array elements) override
    {
        client_.lpush(key, elements);
    }

    virtual void lpushx(cref_string key, cref_string_array elements) override
    {
        client_.lpushx(key, elements);
    }

    virtual void lrange(cref_string key, czint start, czint stop) override
    {
        client_.lrange(key, start, stop);
    }

    virtual void lrem(cref_string key, czint count, cref_string element) override
    {
        client_.lrem(key, count, element);
    }

    virtual void lset(cref_string key, czint index, cref_string element) override
    {
        client_.lset(key, index, element);
    }

    virtual void ltrim(cref_string key, czint start, czint stop) override
    {
        client_.ltrim(key, start, stop);
    }

    virtual void rpop(cref_string key) override
    {
        client_.rpop(key);
    }

    virtual void rpoplpush(cref_string source, cref_string destination) override
    {
        client_.rpoplpush(source, destination);
    }

    virtual void rpush(cref_string key, cref_string_array elements) override
    {
        client_.rpush(key, elements);
    }

    virtual void rpushx(cref_string key, cref_string_array elements) override
    {
        client_.rpushx(key, elements);
    }

//scripting

    virtual void eval(cref_string script,
        cref_string_array keys, cref_string_array args) override
    {
        client_.eval(script, keys, args);
    }

    virtual void evalsha(cref_string sha1,
        cref_string_array keys, cref_string_array args) override
    {
        client_.evalsha(sha1, keys, args);
    }

    virtual void script_exists(cref_string_array sha1s) override
    {
        client_.script_exists(sha1s);
    }

    virtual void script_flush() override
    {
        client_.script_flush();
    }

    virtual void script_kill() override
    {
        client_.script_flush();
    }

    virtual void script_load(cref_string script) override
    {
        client_.script_load(script);
    }

//sets

    virtual void sadd(cref_string key, cref_string_array members) override
    {
        client_.sadd(key, members);
    }

    virtual void scard(cref_string key) override
    {
        client_.scard(key);
    }

    virtual void sdiff(cref_string_array keys) override
    {
        client_.sdiff(keys);
    }

    virtual void sdiffstore(cref_string destination, cref_string_array keys) override
    {
        client_.sdiffstore(destination, keys);
    }

    virtual void sinter(cref_string_array keys) override
    {
        client_.sinter(keys);
    }

    virtual void sinterstore(cref_string destination, cref_string_array keys) override
    {
        client_.sinterstore(destination, keys);
    }

    virtual void sismember(cref_string key, cref_string member) override
    {
        client_.sismember(key, member);
    }

    virtual void smembers(cref_string key) override
    {
        client_.smembers(key);
    }

    virtual void smove(cref_string source, cref_string destination,
        cref_string member) override
    {
        client_.smove(source, destination, member);
    }

    virtual void spop(cref_string key) override
    {
        client_.spop(key);
    }

    virtual void spop(cref_string key, czint count) override
    {
        client_.spop(key, count);
    }

    virtual void srandmember(cref_string key) override
    {
        client_.srandmember(key);
    }

    virtual void srandmember(cref_string key, czint count) override
    {
        client_.srandmember(key, count);
    }

    virtual void srem(cref_string key, cref_string_array members) override
    {
        client_.srem(key, members);
    }

    virtual void sscan(cref_string key, cref_string cursor,
        const scan_param& param = scan_param()) override
    {
        client_.sscan(key, cursor, param);
    }

    virtual void sunion(cref_string_array keys) override
    {
        client_.sunion(keys);
    }

    virtual void sunionstore(cref_string destination, cref_string_array keys) override
    {
        client_.sunionstore(destination, keys);
    }

//sorted_sets

    virtual void bzpopmax(cref_string_array keys, czint timeout) override
    {
        client_.bzpopmax(keys, timeout);
    }

    virtual void bzpopmin(cref_string_array keys, czint timeout) override
    {
        client_.bzpopmin(keys, timeout);
    }

    virtual void zadd(cref_string key, const zadd_param& param,
        cref_string_map member_score_map) override
    {
        client_.zadd(key, param, member_score_map);
    }

    virtual void zcard(cref_string key) override
    {
        client_.zcard(key);
    }

    virtual void zcount(cref_string key, cref_string min, cref_string max) override
    {
        client_.zcount(key, min, max);
    }

    virtual void zincrby(cref_string key, cref_string increment,
        cref_string member) override
    {
        client_.zincrby(key, increment, member);
    }

    virtual void zinterstore(cref_string destination, cref_string_array keys,
        const z_param& param) override
    {
        client_.zinterstore(destination, keys, param);
    }

    virtual void zlexcount(cref_string key, cref_string min, cref_string max) override
    {
        client_.zlexcount(key, min, max);
    }

    virtual void zpopmax(cref_string key) override
    {
        client_.zpopmax(key);
    }

    virtual void zpopmax(cref_string key, czint count) override
    {
        client_.zpopmax(key, count);
    }

    virtual void zpopmin(cref_string key) override
    {
        client_.zpopmin(key);
    }

    virtual void zpopmin(cref_string key, czint count) override
    {
        client_.zpopmin(key, count);
    }

    virtual void zrange(cref_string key, czint start, czint stop,
        bool withscores) override
    {
        client_.zrange(key, start, stop, withscores);
    }

    virtual void zrangebylex(cref_string key, cref_string max, cref_string min) override
    {
        client_.zrangebylex(key, max, min);
    }

    virtual void zrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) override
    {
        client_.zrangebylex(key, max, min);
    }

    virtual void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) override
    {
        client_.zrangebyscore(key, min, max, withscores);
    }

    virtual void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override
    {
        client_.zrangebyscore(key, min, max, withscores, offset, count);
    }

    virtual void zrank(cref_string key, cref_string member) override
    {
        client_.zrank(key, member);
    }

    virtual void zrem(cref_string key, cref_string_array members) override
    {
        client_.zrem(key, members);
    }

    virtual void zremrangebylex(cref_string key,
        cref_string min, cref_string max) override
    {
        client_.zremrangebylex(key, min, max);
    }

    virtual void zremrangebyrank(cref_string key,
        czint start, czint stop) override
    {
        client_.zremrangebyrank(key, start, stop);
    }

    virtual void zremrangebyscore(cref_string key,
        cref_string min, cref_string max) override
    {
        client_.zremrangebyscore(key, min, max);
    }

    virtual void zrevrange(cref_string key, czint start, czint stop,
        bool withscores) override
    {
        client_.zrevrange(key, start, stop, withscores);
    }

    virtual void zrevrangebylex(cref_string key,
        cref_string max, cref_string min) override
    {
        client_.zrevrangebylex(key, max, min);
    }

    virtual void zrevrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) override
    {
        client_.zrevrangebylex(key, max, min, offset, count);
    }

    virtual void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) override
    {
        client_.zrevrangebyscore(key, min, max, withscores);
    }

    virtual void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override
    {
        client_.zrevrangebyscore(key, min, max, withscores, offset, count);
    }

    virtual void zrevrank(cref_string key, cref_string member) override
    {
        client_.zrevrank(key, member);
    }

    virtual void zscan(cref_string key, cref_string cursor, const scan_param& param) override
    {
        client_.zscan(key, cursor, param);
    }

    virtual void zscore(cref_string key, cref_string member) override
    {
        client_.zscore(key, member);
    }

    virtual void zunionstore(cref_string destination, cref_string_array keys,
        const z_param& param) override
    {
        client_.zunionstore(destination, keys, param);
    }

//streams

    virtual void xack(cref_string key, cref_string group,
        cref_stream_id_array ids) override
    {
        client_.xack(key, group, ids);
    }

    virtual void xadd(cref_string key, const xadd_param param,
        cref_string id, cref_string_map field_value_map) override
    {
        client_.xadd(key, param, id, field_value_map);
    }

    virtual void xclaim(cref_string key, cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids,
        const xclaim_param& param) override
    {
        client_.xclaim(key, group, consumer, min_idle_time, ids, param);
    }

    virtual void xdel(cref_string key, cref_stream_id_array ids) override
    {
        client_.xdel(key, ids);
    }

    virtual void xgroup_create(cref_string key, cref_string groupname,
        cref_string id, bool mkstream) override
    {
        client_.xgroup_create(key, groupname, id, mkstream);
    }

    virtual void xgroup_delconsumer(cref_string key, cref_string groupname,
        cref_string consumername) override
    {
        client_.xgroup_delconsumer(key, groupname, consumername);
    }

    virtual void xgroup_destroy(cref_string key, cref_string groupname) override
    {
        client_.xgroup_destroy(key, groupname);
    }

    virtual void xgroup_setid(cref_string key, cref_string groupname,
        cref_string id) override
    {
        client_.xgroup_setid(key, groupname, id);
    }

    virtual void xgroup_help() override
    {
        client_.xgroup_help();
    }

    virtual void xinfo_consumers(cref_string key, cref_string groupname) override
    {
        client_.xinfo_consumers(key, groupname);
    }

    virtual void xinfo_groups(cref_string key) override
    {
        client_.xinfo_groups(key);
    }

    virtual void xinfo_stream(cref_string key) override
    {
        client_.xinfo_stream(key);
    }

    virtual void xinfo_help() override
    {
        client_.xinfo_help();
    }

    virtual void xlen(cref_string key) override
    {
        client_.xlen(key);
    }

    virtual void xpending(cref_string key, cref_string group) override
    {
        client_.xpending(key, group);
    }

    virtual void xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count) override
    {
        client_.xpending(key, group, start, end, count);
    }

    virtual void xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count,
        cref_string consumer) override
    {
        client_.xpending(key, group, start, end, count, consumer);
    }

    virtual void xrange(cref_string key,
        cref_string start, cref_string end) override
    {
        client_.xrange(key, start, end);
    }

    virtual void xrange(cref_string key,
        cref_string start, cref_string end, czint count) override
    {
        client_.xrange(key, start, end, count);
    }

    virtual void xread(const xread_param& param, cref_string_array keys,
        cref_stream_id_array ids) override
    {
        client_.xread(param, keys, ids);
    }

    virtual void xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string_array keys,
        cref_stream_id_array ids) override
    {
        client_.xreadgroup(group, consumer, param, noack, keys, ids);
    }

    virtual void xrevrange(cref_string key,
        cref_string end, cref_string start) override
    {
        client_.xrevrange(key, end, start);
    }

    virtual void xrevrange(cref_string key,
        cref_string end, cref_string start, czint count) override
    {
        client_.xrevrange(key, end, start, count);
    }

    virtual void xtrim(cref_string key, czint threshold,
        bool almost_exact = false) override
    {
        client_.xtrim(key, threshold, almost_exact);
    }

//strings

    virtual void append(cref_string key, cref_string value) override
    {
        client_.append(key, value);
    }

    virtual void bitcount(cref_string key, czint start, czint end) override
    {
        client_.bitcount(key, start, end);
    }

    virtual void bitop(bit_operation op, cref_string dest_key,
        cref_string_array keys) override
    {
        client_.bitop(op, dest_key, keys);
    }

    virtual void decr(cref_string key) override
    {
        client_.decr(key);
    }

    virtual void decrby(cref_string key, czint decrement) override
    {
        client_.decrby(key, decrement);
    }

    virtual void get(cref_string key) override
    {
        client_.get(key);
    }

    virtual void getbit(cref_string key, czint offset) override
    {
        client_.getbit(key, offset);
    }

    virtual void getrange(cref_string key, czint start, czint end) override
    {
        client_.getrange(key, start, end);
    }

    virtual void getset(cref_string key, cref_string value) override
    {
        client_.getset(key, value);
    }

    virtual void incr(cref_string key) override
    {
        client_.incr(key);
    }

    virtual void incrby(cref_string key, czint increment)
    {
        client_.incrby(key, increment);
    }

    virtual void incrbyfloat(cref_string key, double increment) override
    {
        client_.incrbyfloat(key, increment);
    }

    virtual void mget(cref_string_array keys) override
    {
        client_.mget(keys);
    }

    virtual void mset(cref_string_array key_value_pairs) override
    {
        client_.mset(key_value_pairs);
    }

    virtual void msetnx(cref_string_array key_value_pairs) override
    {
        client_.mset(key_value_pairs);
    }

    virtual void psetex(cref_string key, czint milliseconds,
        cref_string value) override
    {
        client_.psetex(key, milliseconds, value);
    }

    virtual void set(cref_string key, cref_string value,
        cref_string_array params = {}) override
    {
        client_.set(key, value, params);
    }

    virtual void setbit(cref_string key, czint offset, czbit bit) override
    {
        client_.setbit(key, offset, bit);
    }

    virtual void setex(cref_string key, czint seconds, cref_string value) override
    {
        client_.setex(key, seconds, value);
    }

    virtual void setnx(cref_string key, cref_string value)
    {
        client_.setnx(key, value);
    }

    virtual void setrange(cref_string key, czint offset, cref_string value) override
    {
        client_.setrange(key, offset, value);
    }

    virtual void strlen(cref_string key) override
    {
        client_.strlen(key);
    }

//transactions

    virtual void discard() override
    {
        client_.discard();
    }

    virtual void exec() override
    {
        client_.exec();
    }

    virtual void multi() override
    {
        client_.multi();
    }
    
    virtual void unwatch() override
    {
        client_.unwatch();
    }

    virtual void watch(cref_string_array keys) override
    {
        client_.watch(keys);
    }

protected:
    pipeline(client& c) :
        client_(c)
    {
    }

private:
    client& client_;
};

}