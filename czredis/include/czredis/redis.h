#pragma once

#include "detail/client.h"
#include "pipeline.h"

namespace czredis
{

class redis : private asio::noncopyable
{
    using client = detail::client;
    using unique_ptr_client = std::unique_ptr<client, std::function<void(client*)>>;
    friend class redis_pool;

public:
    redis(cref_string host = "localhost",
          cref_string port = "6379",
          redis_config config = redis_config()) :
        client_ptr_(new client(host, port, config), [](client* c) { delete c; }),
        client_(*client_ptr_)
    {}

    redis(redis&& r) noexcept :
        client_ptr_(std::move(r.client_ptr_)),
        client_(*client_ptr_)
    {}

    redis(unique_ptr_client&& ptr) :
        client_ptr_(std::move(ptr)),
        client_(*client_ptr_)
    {}

    virtual ~redis()
    {}

    void connect()
    {
        client_.do_connect();
    }

    void disconnect() noexcept
    {
        client_.disconnect();
    }

    czstring username() const noexcept
    {
        return client_.username();
    }

    czstring password() const noexcept
    {
        return client_.password();
    }

    unsigned database() const noexcept
    {
        return client_.database();
    }

    pipeline get_pipline()
    {
        return pipeline(*client_ptr_);
    }

//connection

    czstring auth(cref_string password)
    {
        check_pipline();
        client_.auth(password);
        return get_string_reply();
    }

    czstring auth(cref_string username, cref_string password)
    {
        check_pipline();
        client_.auth(username, password);
        return get_string_reply();
    }

    czstring echo(cref_string message)
    {
        check_pipline();
        client_.echo(message);
        return get_string_reply();
    }

    czstring ping()
    {
        check_pipline();
        client_.ping();
        return get_string_reply();
    }

    void quit()
    {
        check_pipline();
        client_.quit();
        disconnect();
    }

    czstring select(unsigned index)
    {
        check_pipline();
        client_.select(index);
        return get_string_reply();
    }

//geo

    czint geoadd(cref_string key, double longitude, double latitude,
        cref_string member)
    {
        check_pipline();
        client_.geoadd(key, longitude, latitude, member);
        return get_integer_reply();
    }

    czint geoadd(cref_string key,
        std::map<czstring, geo_coordinate> member_coordinate_map)
    {
        check_pipline();
        client_.geoadd(key, member_coordinate_map);
        return get_integer_reply();
    }

    reply geodist(cref_string key, cref_string member1,
        cref_string member2, geo_unit unit)
    {
        check_pipline();
        client_.geodist(key, member1, member2, unit);
        return get_raw_reply();
    }

    reply_array geohash(cref_string key, cref_string_array members)
    {
        check_pipline();
        client_.geohash(key, members);
        return get_array_reply();
    }

    reply_array geopos(cref_string key, cref_string_array members)
    {
        check_pipline();
        client_.geopos(key, members);
        return get_array_reply();
    }

    reply_array georadius(cref_string key, double longitude, double latitude,
        double radius, geo_unit unit,
        const georadius_param& param = georadius_param(),
        const georadius_store_param& store_param = georadius_store_param())
    {
        check_pipline();
        client_.georadius(key, longitude, latitude, radius,
            unit, param, store_param);
        return get_array_reply();
    }

    reply_array georadius_RO(cref_string key, double longitude, double latitude,
        double radius, geo_unit unit,
        const georadius_param& param = georadius_param())
    {
        check_pipline();
        client_.georadius_RO(key, longitude, latitude, radius, unit, param);
        return get_array_reply();
    }

    reply_array georadiusbymember(cref_string key, cref_string member,
        double radius, geo_unit unit,
        const georadius_param& param = georadius_param(),
        const georadius_store_param& store_param = georadius_store_param())
    {
        check_pipline();
        client_.georadiusbymember(key, member, radius, unit, param, store_param);
        return get_array_reply();
    }

    reply_array georadiusbymember_RO(cref_string key, cref_string member,
        double radius, geo_unit unit,
        const georadius_param& param = georadius_param())
    {
        check_pipline();
        client_.georadiusbymember_RO(key, member, radius, unit, param);
        return get_array_reply();
    }

//hashes

    czint hdel(cref_string key, cref_string_array fields)
    {
        check_pipline();
        client_.hdel(key, fields);
        return get_integer_reply();
    }

    czint hexists(cref_string key, cref_string field)
    {
        check_pipline();
        client_.hexists(key, field);
        return get_integer_reply();
    }

    reply hget(cref_string key, cref_string field)
    {
        check_pipline();
        client_.hget(key, field);
        return get_raw_reply();
    }

    reply_array hgetall(cref_string key)
    {
        check_pipline();
        client_.hgetall(key);
        return get_array_reply();
    }

    czint hincrby(cref_string key, cref_string field,
        czint increment)
    {
        check_pipline();
        client_.hincrby(key, field, increment);
        return get_integer_reply();
    }

    double hincrbyfloat(cref_string key, cref_string field,
        double increment)
    {
        check_pipline();
        client_.hincrbyfloat(key, field, increment);
        return std::stod(get_string_reply());
    }

    string_array hkeys(cref_string key)
    {
        check_pipline();
        client_.hkeys(key);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czint hlen(cref_string key)
    {
        check_pipline();
        client_.hlen(key);
        return get_integer_reply();
    }

    reply_array hmget(cref_string key, cref_string_array fields)
    {
        check_pipline();
        client_.hmget(key, fields);
        return get_array_reply();
    }

    czstring hmset(cref_string key, cref_string_map field_value_map)
    {
        check_pipline();
        client_.hmset(key, field_value_map);
        return get_string_reply();
    }

    scan_result hscan(cref_string key, cref_string cursor,
        const scan_param& param = scan_param())
    {
        check_pipline();
        client_.hscan(key, cursor, param);
        return detail::reply_array_to_scan_result(get_array_reply());
    }

    czint hset(cref_string key, cref_string field,
        cref_string value)
    {
        check_pipline();
        client_.hset(key, field, value);
        return get_integer_reply();
    }

    czint hsetnx(cref_string key, cref_string field,
        cref_string value)
    {
        check_pipline();
        client_.hsetnx(key, field, value);
        return get_integer_reply();
    }

    czint hstrlen(cref_string key, cref_string field)
    {
        check_pipline();
        client_.hstrlen(key, field);
        return get_integer_reply();
    }

    string_array hvals(cref_string key)
    {
        check_pipline();
        client_.hvals(key);
        return detail::reply_array_to_string_array(get_array_reply());
    }

//hyper_log_log
    czint pfadd(cref_string key, cref_string_array elements)
    {
        check_pipline();
        client_.pfadd(key, elements);
        return get_integer_reply();
    }

    czint pfcount(cref_string_array keys)
    {
        check_pipline();
        client_.pfcount(keys);
        return get_integer_reply();
    }

    czstring pfmerge(cref_string destkey, cref_string_array sourcekeys)
    {
        check_pipline();
        client_.pfmerge(destkey, sourcekeys);
        return get_string_reply();
    }

//keys

    czint del(cref_string_array keys)
    {
        check_pipline();
        client_.del(keys);
        return get_integer_reply();
    }

    reply dump(cref_string key)
    {
        check_pipline();
        client_.dump(key);
        return get_raw_reply();
    }

    czint exists(cref_string key)
    {
        check_pipline();
        client_.exists(key);
        return get_integer_reply();
    }

    czint expire(cref_string key, czint seconds)
    {
        check_pipline();
        client_.expire(key, seconds);
        return get_integer_reply();
    }

    czint expireat(cref_string key, czint timestamp)
    {
        check_pipline();
        client_.expireat(key, timestamp);
        return get_integer_reply();
    }

    string_array keys(cref_string pattern)
    {
        check_pipline();
        client_.keys(pattern);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czstring migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout,
        const migrate_param& param = migrate_param())
    {
        check_pipline();
        client_.migrate(host, port, key, destination_db, timeout, param);
        return get_string_reply();
    }

    czstring migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param,
        cref_string_array keys)
    {
        check_pipline();
        client_.migrate(host, port, destination_db, timeout, param, keys);
        return get_string_reply();
    }

    czint move(cref_string key, unsigned db)
    {
        check_pipline();
        client_.move(key, db);
        return get_integer_reply();
    }

    reply object_refcount(cref_string key)
    {
        check_pipline();
        client_.object_refcount(key);
        return get_raw_reply();
    }

    reply object_encoding(cref_string key)
    {
        check_pipline();
        client_.object_encoding(key);
        return get_raw_reply();
    }

    reply object_idletime(cref_string key)
    {
        check_pipline();
        client_.object_idletime(key);
        return get_raw_reply();
    }

    reply object_freq(cref_string key)
    {
        check_pipline();
        client_.object_freq(key);
        return get_raw_reply();
    }

    string_array object_help()
    {
        check_pipline();
        client_.object_help();
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czint persist(cref_string key)
    {
        check_pipline();
        client_.persist(key);
        return get_integer_reply();
    }

    czint pexpire(cref_string key, czint milliseconds)
    {
        check_pipline();
        client_.pexpire(key, milliseconds);
        return get_integer_reply();
    }

    czint pexpireat(cref_string key, czint milliseconds_timestamp)
    {
        check_pipline();
        client_.pexpireat(key, milliseconds_timestamp);
        return get_integer_reply();
    }

    czint pttl(cref_string key)
    {
        check_pipline();
        client_.pttl(key);
        return get_integer_reply();
    }

    reply randomkey()
    {
        check_pipline();
        client_.randomkey();
        return get_raw_reply();
    }

    czstring rename(cref_string key, cref_string new_key)
    {
        check_pipline();
        client_.rename(key, new_key);
        return get_string_reply();
    }

    czint renamenx(cref_string key, cref_string new_key)
    {
        check_pipline();
        client_.renamenx(key, new_key);
        return get_integer_reply();
    }

    czstring restore(cref_string key, czint ttl,
        cref_string serialized_value,
        const restore_param& param = restore_param())
    {
        check_pipline();
        client_.restore(key, ttl, serialized_value, param);
        return get_string_reply();
    }

    scan_result scan(cref_string cursor,
        const scan_param& param = scan_param())
    {
        check_pipline();
        client_.scan(cursor, param);
        return detail::reply_array_to_scan_result(get_array_reply());
    }

    scan_result scan(cref_string cursor,
        const scan_param& param, redis_key_type type)
    {
        check_pipline();
        client_.scan(cursor, param, type);
        return detail::reply_array_to_scan_result(get_array_reply());
    }

    reply sort(cref_string key,
        const sort_param& param = sort_param())
    {
        check_pipline();
        client_.sort(key, param);
        return get_raw_reply();
    }

    czint touch(cref_string_array keys)
    {
        check_pipline();
        client_.touch(keys);
        return get_integer_reply();
    }

    czint ttl(cref_string key)
    {
        check_pipline();
        client_.ttl(key);
        return get_integer_reply();
    }

    czstring type(cref_string key)
    {
        check_pipline();
        client_.type(key);
        return get_string_reply();
    }

    czint unlink(cref_string_array keys)
    {
        check_pipline();
        client_.unlink(keys);
        return get_integer_reply();
    }

    czint wait(unsigned numreplicas, czint timeout)
    {
        check_pipline();
        client_.wait(numreplicas, timeout);
        return get_integer_reply();
    }

//lists

    reply blpop(cref_string_array keys, czint timeout)
    {
        check_pipline();
        client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.blpop(keys, timeout);
        return get_raw_reply();
    }

    reply brpop(cref_string_array keys, czint timeout)
    {
        check_pipline();
        client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.brpop(keys, timeout);
        return get_raw_reply();
    }

    reply brpoplpush(cref_string source, cref_string destination,
        czint timeout)
    {
        check_pipline();
        client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.brpoplpush(source, destination, timeout);
        return get_raw_reply();
    }

    reply lindex(cref_string key, czint index)
    {
        check_pipline();
        client_.lindex(key, index);
        return get_raw_reply();
    }

    czint linsert(cref_string key, insert_place place,
        cref_string pivot, cref_string value)
    {
        check_pipline();
        client_.linsert(key, place, pivot, value);
        return get_integer_reply();
    }

    czint llen(cref_string key)
    {
        check_pipline();
        client_.llen(key);
        return get_integer_reply();
    }

    reply lpop(cref_string key)
    {
        check_pipline();
        client_.lpop(key);
        return get_raw_reply();
    }

    czint lpush(cref_string key, cref_string_array elements)
    {
        check_pipline();
        client_.lpush(key, elements);
        return get_integer_reply();
    }

    czint lpushx(cref_string key, cref_string_array elements)
    {
        check_pipline();
        client_.lpushx(key, elements);
        return get_integer_reply();
    }

    string_array lrange(cref_string key, czint start, czint stop)
    {
        check_pipline();
        client_.lrange(key, start, stop);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czint lrem(cref_string key, czint count, cref_string element)
    {
        check_pipline();
        client_.lrem(key, count, element);
        return get_integer_reply();
    }

    czstring lset(cref_string key, czint index, cref_string element)
    {
        check_pipline();
        client_.lset(key, index, element);
        return get_string_reply();
    }

    czstring ltrim(cref_string key, czint start, czint stop)
    {
        check_pipline();
        client_.ltrim(key, start, stop);
        return get_string_reply();
    }

    reply rpop(cref_string key)
    {
        check_pipline();
        client_.rpop(key);
        return get_raw_reply();
    }

    reply rpoplpush(cref_string source, cref_string destination)
    {
        check_pipline();
        client_.rpoplpush(source, destination);
        return get_raw_reply();
    }

    czint rpush(cref_string key, cref_string_array elements)
    {
        check_pipline();
        client_.rpush(key, elements);
        return get_integer_reply();
    }

    czint rpushx(cref_string key, cref_string_array elements)
    {
        check_pipline();
        client_.rpushx(key, elements);
        return get_integer_reply();
    }

//scripting

    reply eval(cref_string script,
        cref_string_array keys, cref_string_array args)
    {
        check_pipline();
        client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.eval(script, keys, args);
        return get_raw_reply();
    }

    reply evalsha(cref_string sha1,
        cref_string_array keys, cref_string_array args)
    {
        check_pipline();
        client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.evalsha(sha1, keys, args);
        return get_raw_reply();
    }

    std::vector<czint> script_exists(cref_string_array sha1s)
    {
        check_pipline();
        client_.script_exists(sha1s);
        return detail::reply_array_to_integer_array(get_array_reply());
    }

    czstring script_flush()
    {
        check_pipline();
        client_.script_flush();
        return get_string_reply();
    }

    czstring script_kill()
    {
        check_pipline();
        client_.script_flush();
        return get_string_reply();
    }

    czstring script_load(cref_string script)
    {
        check_pipline();
        client_.script_load(script);
        return get_string_reply();
    }

//sets

    czint sadd(cref_string key, cref_string_array members)
    {
        check_pipline();
        client_.sadd(key, members);
        return get_integer_reply();
    }

    czint scard(cref_string key)
    {
        check_pipline();
        client_.scard(key);
        return get_integer_reply();
    }

    string_array sdiff(cref_string_array keys)
    {
        check_pipline();
        client_.sdiff(keys);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czint sdiffstore(cref_string destination, cref_string_array keys)
    {
        check_pipline();
        client_.sdiffstore(destination, keys);
        return get_integer_reply();
    }

    string_array sinter(cref_string_array keys)
    {
        check_pipline();
        client_.sinter(keys);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czint sinterstore(cref_string destination, cref_string_array keys)
    {
        check_pipline();
        client_.sinterstore(destination, keys);
        return get_integer_reply();
    }

    czint sismember(cref_string key, cref_string member)
    {
        check_pipline();
        client_.sismember(key, member);
        return get_integer_reply();
    }

    string_array smembers(cref_string key)
    {
        check_pipline();
        client_.smembers(key);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czint smove(cref_string source, cref_string destination,
        cref_string member)
    {
        check_pipline();
        client_.smove(source, destination, member);
        return get_integer_reply();
    }

    reply spop(cref_string key)
    {
        check_pipline();
        client_.spop(key);
        return get_raw_reply();
    }

    reply_array spop(cref_string key, czint count)
    {
        check_pipline();
        client_.spop(key, count);
        return get_array_reply();
    }

    reply srandmember(cref_string key)
    {
        check_pipline();
        client_.srandmember(key);
        return get_raw_reply();
    }

    reply_array srandmember(cref_string key, czint count)
    {
        check_pipline();
        client_.srandmember(key, count);
        return get_array_reply();
    }

    czint srem(cref_string key, cref_string_array members)
    {
        check_pipline();
        client_.srem(key, members);
        return get_integer_reply();
    }

    scan_result sscan(cref_string key, cref_string cursor,
        const scan_param& param = scan_param())
    {
        check_pipline();
        client_.sscan(key, cursor, param);
        return detail::reply_array_to_scan_result(get_array_reply());
    }

    string_array sunion(cref_string_array keys)
    {
        check_pipline();
        client_.sunion(keys);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czint sunionstore(cref_string destination, cref_string_array keys)
    {
        check_pipline();
        client_.sunionstore(destination, keys);
        return get_integer_reply();
    }

//sorted_sets

    reply bzpopmax(cref_string_array keys, czint timeout)
    {
        check_pipline();
        client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.bzpopmax(keys, timeout);
        return get_raw_reply();
    }

    reply bzpopmin(cref_string_array keys, czint timeout)
    {
        check_pipline();
        client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.bzpopmin(keys, timeout);
        return get_raw_reply();
    }

    reply zadd(cref_string key, const zadd_param& param,
        cref_string_map member_score_map)
    {
        check_pipline();
        client_.zadd(key, param,  member_score_map);
        return get_raw_reply();
    }

    czint zcard(cref_string key)
    {
        check_pipline();
        client_.zcard(key);
        return get_integer_reply();
    }

    czint zcount(cref_string key, cref_string min, cref_string max)
    {
        check_pipline();
        client_.zcount(key, min, max);
        return get_integer_reply();
    }

    czstring zincrby(cref_string key, cref_string increment,
        cref_string member)
    {
        check_pipline();
        client_.zincrby(key, increment, member);
        return get_string_reply();
    }

    czint zinterstore(cref_string destination, cref_string_array keys,
        const z_param& param)
    {
        check_pipline();
        client_.zinterstore(destination, keys, param);
        return get_integer_reply();
    }

    czint zlexcount(cref_string key, cref_string min, cref_string max)
    {
        check_pipline();
        client_.zlexcount(key, min, max);
        return get_integer_reply();
    }

    string_array zpopmax(cref_string key)
    {
        check_pipline();
        client_.zpopmax(key);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zpopmax(cref_string key, czint count)
    {
        check_pipline();
        client_.zpopmax(key, count);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zpopmin(cref_string key)
    {
        check_pipline();
        client_.zpopmin(key);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zpopmin(cref_string key, czint count)
    {
        check_pipline();
        client_.zpopmin(key, count);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrange(cref_string key, czint start, czint stop,
        bool withscores)
    {
        check_pipline();
        client_.zrange(key, start, stop, withscores);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrangebylex(cref_string key, cref_string max, cref_string min)
    {
        check_pipline();
        client_.zrangebylex(key, max, min);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count)
    {
        check_pipline();
        client_.zrangebylex(key, max, min);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores)
    {
        check_pipline();
        client_.zrangebyscore(key, min, max, withscores);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count)
    {
        check_pipline();
        client_.zrangebyscore(key, min, max, withscores, offset, count);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    reply zrank(cref_string key, cref_string member)
    {
        check_pipline();
        client_.zrank(key, member);
        return get_raw_reply();
    }

    czint zrem(cref_string key, cref_string_array members)
    {
        check_pipline();
        client_.zrem(key, members);
        return get_integer_reply();
    }

    czint zremrangebylex(cref_string key,
        cref_string min, cref_string max)
    {
        check_pipline();
        client_.zremrangebylex(key, min, max);
        return get_integer_reply();
    }

    czint zremrangebyrank(cref_string key,
        czint start, czint stop)
    {
        check_pipline();
        client_.zremrangebyrank(key, start, stop);
        return get_integer_reply();
    }

    czint zremrangebyscore(cref_string key,
        cref_string min, cref_string max)
    {
        check_pipline();
        client_.zremrangebyscore(key, min, max);
        return get_integer_reply();
    }

    string_array zrevrange(cref_string key, czint start, czint stop,
        bool withscores)
    {
        check_pipline();
        client_.zrevrange(key, start, stop, withscores);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrevrangebylex(cref_string key,
        cref_string max, cref_string min)
    {
        check_pipline();
        client_.zrevrangebylex(key, max, min);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrevrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count)
    {
        check_pipline();
        client_.zrevrangebylex(key, max, min, offset, count);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores)
    {
        check_pipline();
        client_.zrevrangebyscore(key, min, max, withscores);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    string_array zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count)
    {
        check_pipline();
        client_.zrevrangebyscore(key, min, max, withscores, offset, count);
        return detail::reply_array_to_string_array(get_array_reply());
    }

    reply zrevrank(cref_string key, cref_string member)
    {
        check_pipline();
        client_.zrevrank(key, member);
        return get_raw_reply();
    }

    scan_result zscan(cref_string key, cref_string cursor, const scan_param& param)
    {
        check_pipline();
        client_.zscan(key, cursor, param);
        return detail::reply_array_to_scan_result(get_array_reply());
    }

    reply zscore(cref_string key, cref_string member)
    {
        check_pipline();
        client_.zscore(key, member);
        return get_raw_reply();
    }

    czint zunionstore(cref_string destination, cref_string_array keys,
        const z_param& param)
    {
        check_pipline();
        client_.zunionstore(destination, keys, param);
        return get_integer_reply();
    }

//streams

    czint xack(cref_string key, cref_string group,
        cref_stream_id_array ids)
    {
        check_pipline();
        client_.xack(key, group, ids);
        return get_integer_reply();
    }

    stream_id xadd(cref_string key, const xadd_param param,
        cref_string id, cref_string_map field_value_map)
    {
        check_pipline();
        client_.xadd(key, param, id, field_value_map);
        return get_string_reply();
    }

    stream_entries xclaim(cref_string key, cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids,
        const xclaim_param& param)
    {
        check_pipline();
        client_.xclaim(key, group, consumer, min_idle_time, ids, param);
        return get_array_reply();
    }

    czint xdel(cref_string key, cref_stream_id_array ids)
    {
        check_pipline();
        client_.xdel(key, ids);
        return get_integer_reply();
    }

    czstring xgroup_create(cref_string key, cref_string groupname,
        cref_string id, bool mkstream)
    {
        check_pipline();
        client_.xgroup_create(key, groupname, id, mkstream);
        return get_string_reply();
    }

    czint xgroup_delconsumer(cref_string key, cref_string groupname,
        cref_string consumername)
    {
        check_pipline();
        client_.xgroup_delconsumer(key, groupname, consumername);
        return get_integer_reply();
    }

    czint xgroup_destroy(cref_string key, cref_string groupname)
    {
        check_pipline();
        client_.xgroup_destroy(key, groupname);
        return get_integer_reply();
    }

    czstring xgroup_setid(cref_string key, cref_string groupname,
        cref_string id)
    {
        check_pipline();
        client_.xgroup_setid(key, groupname, id);
        return get_string_reply();
    }

    string_array xgroup_help()
    {
        check_pipline();
        client_.xgroup_help();
        return detail::reply_array_to_string_array(get_array_reply());
    }

    std::vector<stream_consumer_info> xinfo_consumers(cref_string key, cref_string groupname)
    {
        check_pipline();
        client_.xinfo_consumers(key, groupname);
        std::vector<stream_consumer_info> arr;
        for (auto& r : get_array_reply())
        {
            arr.emplace_back(detail::reply_array_to_reply_map(std::move(r.as_array())));
        }
        return arr;
    }

    std::vector<stream_group_info> xinfo_groups(cref_string key)
    {
        check_pipline();
        client_.xinfo_groups(key);
        std::vector<stream_group_info> arr;
        for (auto& r : get_array_reply())
        {
            arr.emplace_back(detail::reply_array_to_reply_map(std::move(r.as_array())));
        }
        return arr;
    }

    stream_info xinfo_stream(cref_string key)
    {
        check_pipline();
        client_.xinfo_stream(key);
        return detail::reply_array_to_reply_map(get_array_reply());
    }

    string_array xinfo_help()
    {
        check_pipline();
        client_.xinfo_help();
        return detail::reply_array_to_string_array(get_array_reply());
    }

    czint xlen(cref_string key)
    {
        check_pipline();
        client_.xlen(key);
        return get_integer_reply();
    }

    xpending_overall_result xpending(cref_string key, cref_string group)
    {
        check_pipline();
        client_.xpending(key, group);
        return get_array_reply();
    }

    std::vector<xpending_result> xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count)
    {
        check_pipline();
        client_.xpending(key, group, start, end, count);
        std::vector<xpending_result> arr;
        for (auto& r : get_array_reply())
        {
            arr.emplace_back(r.as_array());
        }
        return arr;
    }

    std::vector<xpending_result> xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count,
        cref_string consumer)
    {
        check_pipline();
        client_.xpending(key, group, start, end, count, consumer);
        check_pipline();
        client_.xpending(key, group, start, end, count);
        std::vector<xpending_result> arr;
        for (auto& r : get_array_reply())
        {
            arr.emplace_back(r.as_array());
        }
        return arr;
    }

    stream_entries xrange(cref_string key,
        cref_string start, cref_string end)
    {
        check_pipline();
        client_.xrange(key, start, end);
        return get_array_reply();
    }

    stream_entries xrange(cref_string key,
        cref_string start, cref_string end, czint count)
    {
        check_pipline();
        client_.xrange(key, start, end, count);
        return get_array_reply();
    }

    std::map<czstring, stream_entries> xread(const xread_param& param,
        cref_string_array keys, cref_stream_id_array ids)
    {
        check_pipline();
        if (param.is_block())
            client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.xread(param, keys, ids);
        return detail::reply_array_to_stream_entries_map(get_array_reply());
    }

    std::map<czstring, stream_entries> xreadgroup(cref_string group,
        cref_string consumer, const xread_param& param, bool noack,
        cref_string_array keys, cref_stream_id_array ids)
    {
        check_pipline();
        if (param.is_block())
            client_.set_block(true);
        detail::call_finally func([this]() {
            client_.set_block(false);
        });
        client_.xreadgroup(group, consumer, param, noack, keys, ids);
        return detail::reply_array_to_stream_entries_map(get_array_reply());
    }

    stream_entries xrevrange(cref_string key,
        cref_string end, cref_string start)
    {
        check_pipline();
        client_.xrevrange(key, end, start);
        return get_array_reply();
    }

    stream_entries xrevrange(cref_string key,
        cref_string end, cref_string start, czint count)
    {
        check_pipline();
        client_.xrevrange(key, end, start, count);
        return get_array_reply();
    }

    czint xtrim(cref_string key, czint threshold,
        bool almost_exact = false)
    {
        check_pipline();
        client_.xtrim(key, threshold, almost_exact);
        return get_integer_reply();
    }

//string

    czint append(cref_string key, cref_string value)
    {
        check_pipline();
        client_.append(key, value);
        return get_integer_reply();
    }

    czint bitcount(cref_string key)
    {
        check_pipline();
        client_.bitcount(key, 0, -1);
        return get_integer_reply();
    }

    czint bitcount(cref_string key, czint start, czint end)
    {
        check_pipline();
        client_.bitcount(key, start, end);
        return get_integer_reply();
    }

    czint bitop(bit_operation op, cref_string dest_key, cref_string_array keys)
    {
        check_pipline();
        client_.bitop(op, dest_key, keys);
        return get_integer_reply();
    }

    czint decr(cref_string key)
    {
        check_pipline();
        client_.decr(key);
        return get_integer_reply();
    }
    czint decrby(cref_string key, czint decrement)
    {
        check_pipline();
        client_.decrby(key, decrement);
        return get_integer_reply();
    }

    reply get(cref_string key)
    {
        check_pipline();
        client_.get(key);
        return get_raw_reply();
    }

    czint getbit(cref_string key, czint offset)
    {
        check_pipline();
        client_.getbit(key, offset);
        return get_integer_reply();
    }

    czstring getrange(cref_string key, czint start, czint end)
    {
        check_pipline();
        client_.getrange(key, start, end);
        return get_string_reply();
    }

    reply getset(cref_string key, cref_string value)
    {
        check_pipline();
        client_.getset(key, value);
        return get_raw_reply();
    }

    czint incr(cref_string key)
    {
        check_pipline();
        client_.incr(key);
        return get_integer_reply();
    }

    czint incrby(cref_string key, czint increment)
    {
        check_pipline();
        client_.incrby(key, increment);
        return get_integer_reply();
    }

    double incrbyfloat(cref_string key, double increment)
    {
        check_pipline();
        client_.incrbyfloat(key, increment);
        return std::stod(get_string_reply());
    }

    reply_array mget(cref_string_array keys)
    {
        check_pipline();
        client_.mget(keys);
        return get_array_reply();
    }

    czstring mset(cref_string_array key_value_pairs)
    {
        check_pipline();
        client_.mset(key_value_pairs);
        return get_string_reply();
    }

    czint msetnx(cref_string_array key_value_pairs)
    {
        check_pipline();
        client_.msetnx(key_value_pairs);
        return get_integer_reply();
    }

    czstring psetex(cref_string key, czint milliseconds, cref_string value)
    {
        check_pipline();
        client_.psetex(key, milliseconds, value);
        return get_string_reply();
    }

    czstring set(cref_string key, cref_string value, cref_string_array params = {})
    {
        check_pipline();
        client_.set(key, value, params);
        return get_string_reply();
    }

    czbit setbit(cref_string key, czint offset, czbit bit)
    {
        check_pipline();
        client_.setbit(key, offset, bit);
        return static_cast<czbit>(get_integer_reply());
    }

    czstring setex(cref_string key, czint seconds, cref_string value)
    {
        check_pipline();
        client_.setex(key, seconds, value);
        return get_string_reply();
    }

    czint setnx(cref_string key, cref_string value)
    {
        check_pipline();
        client_.setnx(key, value);
        return get_integer_reply();
    }

    czint setrange(cref_string key, czint offset, cref_string value)
    {
        check_pipline();
        client_.setrange(key, offset, value);
        return get_integer_reply();
    }

    czint strlen(cref_string key)
    {
        check_pipline();
        client_.strlen(key);
        return get_integer_reply();
    }


private:
    unique_ptr_client client_ptr_;
    client& client_;

    reply get_raw_reply()
    {
        auto r = client_.get_reply();
        if (r.is_error())
        {
            throw redis_commmand_error(r.as_error());
        }
        return r;
    }

    czint get_integer_reply()
    {
        return client_.get_reply().as_integer();
    }

    czstring get_string_reply()
    {
        return std::move(client_.get_reply().as_string());
    }

    reply_array get_array_reply()
    {
        return std::move(client_.get_reply().as_array());
    }

    void check_pipline()
    {
        if (client_.send_count() > 0)
            throw redis_data_error("pipeline is in use");
    }
};

} // namespace czredis

