#pragma once

#include "resp.h"
#include "comand.h"
#include "../config.h"

namespace czredis
{
namespace detail
{

class client : public socket, public interface_commands
{
    using my_base = socket;
public:
    client(cref_string host, cref_string port, const redis_config& config) :
        host_(host),
        port_(port),
        username_(config.username),
        password_(config.password),
        database_(config.database)
    {
        set_connect_timeout(config.connect_timeout);
        set_read_timeout(config.socket_read_timeout);
        set_write_timeout(config.socket_write_timeout);
    }

    virtual ~client() override
    {}

    void do_connect()
    {
        if (!is_connected())
        {
            my_base::connect(host_, port_);
            if (username_ != "")
                auth(username_, password_);
            else if (password_ != "")
                auth(password_);
            if (database_ > 0)
                select(database_);
            for (auto& r : get_all_reply())
            {
                if (r.is_error())
                    throw redis_commmand_error(r.as_error());
            }
        }
    }

    virtual void disconnect() noexcept override
    {
        if (is_connected())
        {
            my_base::disconnect();
            send_count_ = 0;
            is_in_multi_ = false;
            is_in_watch_ = false;
        }
    }

    void send_command(cref_string_array params)
    {
        check_connect();
        resp_.send_command(params);
        ++send_count_;
    }

    void send_command(cref_string_array params1, cref_string_array params2)
    {
        check_connect();
        resp_.send_command(params1, params2);
        ++send_count_;
    }

    void send_command(std::initializer_list<string_array> params_array)
    {
        check_connect();
        resp_.send_command(params_array);
        ++send_count_;
    }

    void send_command(std::initializer_list<czstring> params)
    {
        check_connect();
        resp_.send_command(params);
        ++send_count_;
    }

    reply get_reply()
    {
        check_connect();
        --send_count_;
        return resp_.get_reply();
    }

    reply_array get_all_reply()
    {
        reply_array arr;
        while (send_count_ > 0)
        {
            arr.emplace_back(get_reply());
        }
        return arr;
    }

    size_t send_count() const noexcept
    {
        return send_count_;
    }

    czstring password() const noexcept
    {
        return password_;
    }

    czstring username() const noexcept
    {
        return username_;
    }

    unsigned database() const noexcept
    {
        return database_;
    }

    void set_password(cref_string pwd) noexcept
    {
        password_ = pwd;
    }

    void set_user(cref_string username) noexcept
    {
        username_ = username;
    }

    void set_database(unsigned db) noexcept
    {
        database_ = db;
    }

    bool is_in_multi() const noexcept
    {
        return is_in_multi_;
    }

    bool is_in_watch() const noexcept
    {
        return is_in_watch_;
    }

//connection

    virtual void auth(cref_string password) override
    {
        send_command({ cmd::connection::AUTH, password });
        set_password(password);
    }

    virtual void auth(cref_string username, cref_string password) override
    {
        send_command({ cmd::connection::AUTH, username, password });
        set_password(password);
    }

    virtual void echo(cref_string message) override
    {
        send_command({ cmd::connection::ECHO, message });
    }

    virtual void ping() override
    {
        send_command({ cmd::connection::PING });
    }

    virtual void quit() override
    {
        send_command({ cmd::connection::QUIT });
    }

    virtual void select(unsigned index) override
    {
        send_command({ cmd::connection::SELECT, std::to_string(index) });
        set_database(index);
    }

//geo

    virtual void geoadd(cref_string key, double longitude,
        double latitude, cref_string member) override
    {
        send_command({ cmd::geo::GEOADD, key,
            std::to_string(longitude), std::to_string(latitude), member });
    }

    virtual void geoadd(cref_string key,
        std::map<czstring, geo_coordinate> member_coordinate_map) override
    {
        string_array params = { cmd::geo::GEOADD ,key };
        for (auto& o : member_coordinate_map)
        {
            params.emplace_back(std::to_string(o.second.longitude));
            params.emplace_back(std::to_string(o.second.latitude));
            params.emplace_back(o.first);
        }
        send_command(params);
    }

    virtual void geodist(cref_string key, cref_string member1,
        cref_string member2, geo_unit unit) override
    {
        send_command({ cmd::geo::GEODIST, key, member1, member2,
            geo_unit_dict.at(unit) });
    }

    virtual void geohash(cref_string key, cref_string_array members) override
    {
        send_command({ cmd::geo::GEOHASH, key }, members);
    }

    virtual void geopos(cref_string key, cref_string_array members) override
    {
        send_command({ cmd::geo::GEOPOS, key }, members);
    }

    virtual void georadius(cref_string key, double longitude, double latitude,
        double radius, geo_unit unit, const georadius_param& param,
        const georadius_store_param& store_param) override
    {
        send_command({ {cmd::geo::GEORADIUS, key, std::to_string(longitude),
            std::to_string(latitude), std::to_string(radius),
            geo_unit_dict.at(unit)}, param.to_string_array(),
            store_param.to_string_array() });
    }

    virtual void georadius_RO(cref_string key, double longitude, double latitude,
        double radius, geo_unit unit, const georadius_param& param) override
    {
        send_command({ {cmd::geo::GEORADIUS_RO, key, std::to_string(longitude),
            std::to_string(latitude), std::to_string(radius),
            geo_unit_dict.at(unit)}, param.to_string_array() });
    }

    virtual void georadiusbymember(cref_string key, cref_string member,
        double radius, geo_unit unit, const georadius_param& param,
        const georadius_store_param& store_param) override
    {
        send_command({ {cmd::geo::GEORADIUSBYMEMBER, key, member,
            std::to_string(radius), geo_unit_dict.at(unit)},
            param.to_string_array(), store_param.to_string_array() });
    }

    virtual void georadiusbymember_RO(cref_string key, cref_string member,
        double radius, geo_unit unit, const georadius_param& param) override
    {
        send_command({ {cmd::geo::GEORADIUSBYMEMBER_RO, key, member,
            std::to_string(radius), geo_unit_dict.at(unit)},
            param.to_string_array() });
    }

//hashes

    virtual void hdel(cref_string key, cref_string_array fields) override
    {
        send_command({ cmd::hashes::HDEL }, fields);
    }

    virtual void hexists(cref_string key, cref_string field) override
    {
        send_command({ cmd::hashes::HEXISTS, key, field });
    }

    virtual void hget(cref_string key, cref_string field) override
    {
        send_command({ cmd::hashes::HGET, key, field });
    }

    virtual void hgetall(cref_string key) override
    {
        send_command({ cmd::hashes::HGET, key });
    }

    virtual void hincrby(cref_string key, cref_string field,
        czint increment) override
    {
        send_command({ cmd::hashes::HINCRBY, key, field,
            std::to_string(increment) });
    }

    virtual void hincrbyfloat(cref_string key, cref_string field,
        double increment) override
    {
        send_command({ cmd::hashes::HINCRBYFLOAT, key, field,
            std::to_string(increment) });
    }

    virtual void hkeys(cref_string key) override
    {
        send_command({ cmd::hashes::HKEYS, key });
    }

    virtual void hlen(cref_string key) override
    {
        send_command({ cmd::hashes::HLEN, key });
    }

    virtual void hmget(cref_string key, cref_string_array fields) override
    {
        send_command({ cmd::hashes::HMGET, key }, fields);
    }

    virtual void hmset(cref_string key, cref_string_map field_value_map) override
    {
        string_array params = { cmd::hashes::HMSET, key };
        for (auto& o : field_value_map)
        {
            params.emplace_back(o.first);
            params.emplace_back(o.second);
        }
        send_command(params);
    }

    virtual void hscan(cref_string key, cref_string cursor,
        const scan_param& param) override
    {
        send_command({ cmd::hashes::HSCAN, key, cursor },
            param.to_string_array());
    }

    virtual void hset(cref_string key, cref_string field,
        cref_string value) override
    {
        send_command({ cmd::hashes::HSET, key, field, value });
    }

    virtual void hsetnx(cref_string key, cref_string field,
        cref_string value) override
    {
        send_command({ cmd::hashes::HSETNX, key, field, value });
    }

    virtual void hstrlen(cref_string key, cref_string field) override
    {
        send_command({ cmd::hashes::HSTRLEN, key, field });
    }

    virtual void hvals(cref_string key) override
    {
        send_command({ cmd::hashes::HVALS, key });
    }

//hyper_log_log
    virtual void pfadd(cref_string key, cref_string_array elements) override
    {
        send_command({ cmd::hyper_log_log::PFADD, key }, elements);
    }

    virtual void pfcount(cref_string_array keys) override
    {
        send_command({ cmd::hyper_log_log::PFCOUNT }, keys);
    }

    virtual void pfmerge(cref_string destkey, cref_string_array sourcekeys) override
    {
        send_command({ cmd::hyper_log_log::PFMERGE, destkey }, sourcekeys);
    }

//keys

    virtual void del(cref_string_array keys) override
    {
        send_command({ cmd::keys::DEL }, keys);
    }

    virtual void dump(cref_string key) override
    {
        send_command({ cmd::keys::DUMP, key });
    }

    virtual void exists(cref_string key) override
    {
        send_command({ cmd::keys::EXISTS, key });
    }

    virtual void expire(cref_string key, czint seconds) override
    {
        send_command({ cmd::keys::EXPIRE, key, std::to_string(seconds) });
    }

    virtual void expireat(cref_string key, czint timestamp) override
    {
        send_command({ cmd::keys::EXPIREAT, key, std::to_string(timestamp) });
    }

    virtual void keys(cref_string pattern) override
    {
        send_command({ cmd::keys::KEYS, pattern });
    }

    virtual void migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout, const migrate_param& param) override
    {
        send_command({ cmd::keys::MIGRATE, host, port, key,
            std::to_string(destination_db), std::to_string(timeout) },
            param.to_string_array());
    }

    virtual void migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param,
        cref_string_array keys) override
    {
        send_command({ {cmd::keys::MIGRATE, host, port, "",
            std::to_string(destination_db), std::to_string(timeout)},
            param.to_string_array(), {kwd::KEYS}, keys });
    }

    virtual void move(cref_string key, unsigned db) override
    {
        send_command({ cmd::keys::MOVE, key, std::to_string(db) });
    }

    virtual void object_refcount(cref_string key) override
    {
        send_command({ cmd::keys::OBJECT, kwd::REFCOUNT, key });
    }

    virtual void object_encoding(cref_string key) override
    {
        send_command({ cmd::keys::OBJECT, kwd::ENCODING, key });
    }

    virtual void object_idletime(cref_string key) override
    {
        send_command({ cmd::keys::OBJECT, kwd::IDLETIME, key });
    }

    virtual void object_freq(cref_string key) override
    {
        send_command({ cmd::keys::OBJECT, kwd::FREQ, key });
    }

    virtual void object_help() override
    {
        send_command({ cmd::keys::OBJECT, kwd::HELP });
    }

    virtual void persist(cref_string key) override
    {
        send_command({ cmd::keys::PERSIST, key });
    }

    virtual void pexpire(cref_string key, czint milliseconds) override
    {
        send_command({ cmd::keys::PEXPIRE, key, std::to_string(milliseconds) });
    }

    virtual void pexpireat(cref_string key, czint milliseconds_timestamp) override
    {
        send_command({ cmd::keys::PEXPIREAT, key,
            std::to_string(milliseconds_timestamp) });
    }

    virtual void pttl(cref_string key) override
    {
        send_command({ cmd::keys::PTTL, key });
    }

    virtual void randomkey() override
    {
        send_command({ cmd::keys::RANDOMKEY });
    }

    virtual void rename(cref_string key, cref_string new_key) override
    {
        send_command({ cmd::keys::RENAME, key, new_key });
    }

    virtual void renamenx(cref_string key, cref_string new_key) override
    {
        send_command({ cmd::keys::RENAMENX, key, new_key });
    }

    virtual void restore(cref_string key, czint ttl,
        cref_string serialized_value, const restore_param& param) override
    {
        send_command({ cmd::keys::RESTORE, key, std::to_string(ttl),
            serialized_value }, param.to_string_array());
    }

    virtual void scan(cref_string cursor, const scan_param& param) override
    {
        send_command({ cmd::keys::PERSIST, cursor }, param.to_string_array());
    }

    virtual void scan(cref_string cursor, const scan_param& param,
        redis_key_type type) override
    {
        send_command({ {cmd::keys::PERSIST, cursor},
            param.to_string_array(),
            {kwd::TYPE, redis_key_type_dict.at(type)} });
    }

    virtual void sort(cref_string key, const sort_param& param) override
    {
        send_command({ cmd::keys::SORT, key }, param.to_string_array());
    }

    virtual void touch(cref_string_array keys) override
    {
        send_command({ cmd::keys::TOUCH }, keys);
    }

    virtual void ttl(cref_string key) override
    {
        send_command({ cmd::keys::TTL, key });
    }

    virtual void type(cref_string key) override
    {
        send_command({ cmd::keys::TYPE, key });
    }

    virtual void unlink(cref_string_array keys) override
    {
        send_command({ cmd::keys::UNLINK }, keys);
    }

    virtual void wait(unsigned numreplicas, czint timeout) override
    {
        send_command({ cmd::keys::WAIT, std::to_string(numreplicas),
            std::to_string(timeout) });
    }

//lists

    virtual void blpop(cref_string_array keys, czint timeout) override
    {
        send_command({{ cmd::lists::BLPOP }, keys, { std::to_string(timeout) }});
    }

    virtual void brpop(cref_string_array keys, czint timeout) override
    {
        send_command({ { cmd::lists::BRPOP }, keys, { std::to_string(timeout) } });
    }

    virtual void brpoplpush(cref_string source, cref_string destination,
        czint timeout) override
    {
        send_command({ cmd::lists::BRPOPLPUSH, source, destination,
            std::to_string(timeout) });
    }

    virtual void lindex(cref_string key, czint index) override
    {
        send_command({ cmd::lists::LINDEX, std::to_string(index) });
    }

    virtual void linsert(cref_string key, insert_place place,
        cref_string pivot, cref_string value) override
    {
        send_command({ cmd::lists::LINSERT, insert_place_dict.at(place),
            pivot, value });
    }

    virtual void llen(cref_string key) override
    {
        send_command({ cmd::lists::LLEN, key });
    }

    virtual void lpop(cref_string key) override
    {
        send_command({ cmd::lists::LPOP, key });
    }

    virtual void lpush(cref_string key, cref_string_array elements) override
    {
        send_command({ cmd::lists::LPUSH, key }, elements);
    }

    virtual void lpushx(cref_string key, cref_string_array elements) override
    {
        send_command({ cmd::lists::LPUSHX, key }, elements);
    }

    virtual void lrange(cref_string key, czint start, czint stop) override
    {
        send_command({ cmd::lists::LRANGE, key,
            std::to_string(start), std::to_string(stop) });
    }

    virtual void lrem(cref_string key, czint count, cref_string element) override
    {
        send_command({ cmd::lists::LREM, key, std::to_string(count), element });
    }

    virtual void lset(cref_string key, czint index, cref_string element) override
    {
        send_command({ cmd::lists::LSET, key, std::to_string(index), element });
    }

    virtual void ltrim(cref_string key, czint start, czint stop) override
    {
        send_command({ cmd::lists::LTRIM, key,
            std::to_string(start), std::to_string(stop) });
    }

    virtual void rpop(cref_string key) override
    {
        send_command({ cmd::lists::RPOP, key });
    }

    virtual void rpoplpush(cref_string source, cref_string destination) override
    {
        send_command({ cmd::lists::BRPOPLPUSH, source, destination });
    }

    virtual void rpush(cref_string key, cref_string_array elements) override
    {
        send_command({ cmd::lists::RPUSH, key }, elements);
    }

    virtual void rpushx(cref_string key, cref_string_array elements) override
    {
        send_command({ cmd::lists::RPUSHX, key }, elements);
    }

//scripting

    virtual void eval(cref_string script,
        cref_string_array keys, cref_string_array args) override
    {
        send_command({{ cmd::scripting::EVAL, script,
            std::to_string(keys.size()) }, keys, args});
    }

    virtual void evalsha(cref_string sha1,
        cref_string_array keys, cref_string_array args) override
    {
        send_command({ { cmd::scripting::EVALSHA, sha1,
            std::to_string(keys.size()) }, keys, args });
    }

    virtual void script_exists(cref_string_array sha1s) override
    {
        send_command({ cmd::scripting::SCRIPT, kwd::EXISTS }, sha1s);
    }

    virtual void script_flush() override
    {
        send_command({ cmd::scripting::SCRIPT, kwd::FLUSH });
    }

    virtual void script_kill() override
    {
        send_command({ cmd::scripting::SCRIPT, kwd::KILL });
    }

    virtual void script_load(cref_string script) override
    {
        send_command({ cmd::scripting::SCRIPT, kwd::LOAD, script });
    }

//sets

    virtual void sadd(cref_string key, cref_string_array members) override
    {
        send_command({ cmd::sets::SADD, key }, members);
    }

    virtual void scard(cref_string key) override
    {
        send_command({ cmd::sets::SCARD, key });
    }

    virtual void sdiff(cref_string_array keys) override
    {
        send_command({ cmd::sets::SDIFF }, keys);
    }

    virtual void sdiffstore(cref_string destination, cref_string_array keys) override
    {
        send_command({ cmd::sets::SADD, destination }, keys);
    }

    virtual void sinter(cref_string_array keys) override
    {
        send_command({ cmd::sets::SINTER }, keys);
    }

    virtual void sinterstore(cref_string destination, cref_string_array keys) override
    {
        send_command({ cmd::sets::SINTERSTORE, destination }, keys);
    }

    virtual void sismember(cref_string key, cref_string member) override
    {
        send_command({ cmd::sets::SISMEMBER, key, member });
    }

    virtual void smembers(cref_string key) override
    {
        send_command({ cmd::sets::SMEMBERS, key });
    }

    virtual void smove(cref_string source, cref_string destination,
        cref_string member) override
    {
        send_command({ cmd::sets::SMOVE, source, destination, member });
    }

    virtual void spop(cref_string key) override
    {
        send_command({ cmd::sets::SPOP, key });
    }

    virtual void spop(cref_string key, czint count) override
    {
        send_command({ cmd::sets::SPOP, key,
            kwd::COUNT, std::to_string(count) });
    }

    virtual void srandmember(cref_string key) override
    {
        send_command({ cmd::sets::SRANDMEMBER, key });
    }

    virtual void srandmember(cref_string key, czint count) override
    {
        send_command({ cmd::sets::SRANDMEMBER, key,
            kwd::COUNT, std::to_string(count) });
    }

    virtual void srem(cref_string key, cref_string_array members) override
    {
        send_command({ cmd::sets::SREM, key }, members);
    }

    virtual void sscan(cref_string key, cref_string cursor,
        const scan_param& param) override
    {
        send_command({ cmd::sets::SSCAN, key, cursor },
            param.to_string_array());
    }

    virtual void sunion(cref_string_array keys) override
    {
        send_command({ cmd::sets::SUNION }, keys);
    }

    virtual void sunionstore(cref_string destination, cref_string_array keys) override
    {
        send_command({ cmd::sets::SUNIONSTORE, destination }, keys);
    }

//sorted_sets

    virtual void bzpopmax(cref_string_array keys, czint timeout) override
    {
        send_command({ {cmd::sorted_sets::BZPOPMIN},
            keys, {std::to_string(timeout)} });
    }

    virtual void bzpopmin(cref_string_array keys, czint timeout) override
    {
        send_command({ {cmd::sorted_sets::BZPOPMIN},
            keys, {std::to_string(timeout)} });
    }

    virtual void zadd(cref_string key, const zadd_param& param,
        cref_string_map member_score_map) override
    {
        string_array cmd_params = { cmd::sorted_sets::ZADD, key };
        param.append_params(cmd_params);
        for (auto& o : member_score_map)
        {
            cmd_params.emplace_back(o.second);
            cmd_params.emplace_back(o.first);
        }
        send_command(cmd_params);
    }

    virtual void zcard(cref_string key) override
    {
        send_command({ cmd::sorted_sets::ZCARD, key });
    }

    virtual void zcount(cref_string key, cref_string min, cref_string max) override
    {
        send_command({ cmd::sorted_sets::ZCOUNT, key, min, max });
    }

    virtual void zincrby(cref_string key, cref_string increment,
        cref_string member) override
    {
        send_command({ cmd::sorted_sets::ZINCRBY, key, increment, member });
    }

    virtual void zinterstore(cref_string destination, cref_string_array keys,
        const z_param& param) override
    {
        send_command({{ cmd::sorted_sets::ZINTERSTORE, destination,
            std::to_string(keys.size()) }, keys, param.to_string_array()});
    }

    virtual void zlexcount(cref_string key, cref_string min, cref_string max) override
    {
        send_command({ cmd::sorted_sets::ZLEXCOUNT, key, min, max });
    }

    virtual void zpopmax(cref_string key) override
    {
        send_command({ cmd::sorted_sets::ZPOPMAX, key });
    }

    virtual void zpopmax(cref_string key, czint count) override
    {
        send_command({ cmd::sorted_sets::ZPOPMAX, key,
            std::to_string(count) });
    }

    virtual void zpopmin(cref_string key) override
    {
        send_command({ cmd::sorted_sets::ZPOPMIN, key });
    }

    virtual void zpopmin(cref_string key, czint count) override
    {
        send_command({ cmd::sorted_sets::ZPOPMIN, key,
            std::to_string(count) });
    }

    virtual void zrange(cref_string key, czint start, czint stop,
        bool withscores) override
    {
        string_array cmd_params = { cmd::sorted_sets::ZRANGE, key,
            std::to_string(start), std::to_string(stop) };
        if (withscores)
            cmd_params.emplace_back(kwd::WITHSCORES);
        send_command(cmd_params);
    }

    virtual void zrangebylex(cref_string key, cref_string max, cref_string min) override
    {
        send_command({ cmd::sorted_sets::ZRANGEBYLEX, key, max, min });
    }

    virtual void zrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) override
    {
        send_command({ cmd::sorted_sets::ZRANGEBYLEX, key, max, min,
            kwd::LIMIT, std::to_string(offset), std::to_string(count) });
    }

    virtual void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) override
    {
        string_array cmd_params = { cmd::sorted_sets::ZRANGEBYSCORE, key,
            min, max };
        if (withscores)
            cmd_params.emplace_back(kwd::WITHSCORES);
        send_command(cmd_params);
    }

    virtual void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override
    {
        string_array cmd_params = { cmd::sorted_sets::ZRANGEBYSCORE, key,
            min, max };
        if (withscores)
            cmd_params.emplace_back(kwd::WITHSCORES);
        cmd_params.emplace_back(kwd::LIMIT);
        cmd_params.emplace_back(std::to_string(offset));
        cmd_params.emplace_back(std::to_string(count));
        send_command(cmd_params);
    }

    virtual void zrank(cref_string key, cref_string member) override
    {
        send_command({ cmd::sorted_sets::ZRANK, key, member });
    }

    virtual void zrem(cref_string key, cref_string_array members) override
    {
        send_command({ cmd::sorted_sets::ZREM, key }, members);
    }

    virtual void zremrangebylex(cref_string key,
        cref_string min, cref_string max) override
    {
        send_command({ cmd::sorted_sets::ZREMRANGEBYLEX, key, min, max });
    }

    virtual void zremrangebyrank(cref_string key,
        czint start, czint stop) override
    {
        send_command({ cmd::sorted_sets::ZREMRANGEBYRANK, key,
            std::to_string(start), std::to_string(stop) });
    }

    virtual void zremrangebyscore(cref_string key,
        cref_string min, cref_string max) override
    {
        send_command({ cmd::sorted_sets::ZREMRANGEBYSCORE, key, min, max });
    }

    virtual void zrevrange(cref_string key, czint start, czint stop,
        bool withscores) override
    {
        string_array cmd_params = { cmd::sorted_sets::ZREVRANGE, key,
            std::to_string(start), std::to_string(stop) };
        if (withscores)
            cmd_params.emplace_back(kwd::WITHSCORES);
        send_command(cmd_params);
    }

    virtual void zrevrangebylex(cref_string key,
        cref_string max, cref_string min) override
    {
        send_command({ cmd::sorted_sets::ZREVRANGEBYLEX, key, max, min });
    }

    virtual void zrevrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) override
    {
        send_command({ cmd::sorted_sets::ZREVRANGEBYLEX, key, max, min,
            kwd::LIMIT, std::to_string(offset), std::to_string(count) });
    }

    virtual void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) override
    {
        string_array cmd_params = { cmd::sorted_sets::ZREVRANGEBYSCORE, key,
            min, max };
        if (withscores)
            cmd_params.emplace_back(kwd::WITHSCORES);
        send_command(cmd_params);
    }

    virtual void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override
    {
        string_array cmd_params = { cmd::sorted_sets::ZREVRANGEBYSCORE, key,
            min, max };
        if (withscores)
            cmd_params.emplace_back(kwd::WITHSCORES);
        cmd_params.emplace_back(kwd::LIMIT);
        cmd_params.emplace_back(std::to_string(offset));
        cmd_params.emplace_back(std::to_string(count));
        send_command(cmd_params);
    }

    virtual void zrevrank(cref_string key, cref_string member) override
    {
        send_command({ cmd::sorted_sets::ZREVRANK, key, member });
    }

    virtual void zscan(cref_string key, cref_string cursor,
        const scan_param& param) override
    {
        send_command({ cmd::sorted_sets::ZSCAN, key, cursor },
            param.to_string_array());
    }

    virtual void zscore(cref_string key, cref_string member) override
    {
        send_command({ cmd::sorted_sets::ZSCORE, key, member });
    }

    virtual void zunionstore(cref_string destination, cref_string_array keys,
        const z_param& param) override
    {
        send_command({ { cmd::sorted_sets::ZUNIONSTORE, destination,
            std::to_string(keys.size()) }, keys, param.to_string_array() });
    }

//streams

    virtual void xack(cref_string key, cref_string group,
        cref_stream_id_array ids) override
    {
        send_command({ cmd::streams::XACK, key, group },
            stream_id_array_to_string_array(ids));
    }

    virtual void xadd(cref_string key, const xadd_param param,
        cref_string id, cref_string_map field_value_map) override
    {
        string_array cmd_params = { cmd::streams::XADD, key };
        param.append_params(cmd_params);
        cmd_params.emplace_back(id);
        for (auto& o : field_value_map)
        {
            cmd_params.emplace_back(o.first);
            cmd_params.emplace_back(o.second);
        }
        send_command(cmd_params);
    }

    virtual void xclaim(cref_string key, cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids,
        const xclaim_param& param) override
    {
        send_command({ {cmd::streams::XCLAIM, key, group, consumer,
            std::to_string(min_idle_time)},
            stream_id_array_to_string_array(ids), param.to_string_array() });
    }

    virtual void xdel(cref_string key, cref_stream_id_array ids) override
    {
        send_command({ cmd::streams::XDEL, key },
            stream_id_array_to_string_array(ids));
    }

    virtual void xgroup_create(cref_string key, cref_string groupname,
        cref_string id, bool mkstream) override
    {
        string_array cmd_params = { cmd::streams::XGROUP, kwd::CREATE,
            key, groupname, id };
        if (mkstream)
            cmd_params.emplace_back(kwd::MKSTREAM);
        send_command(cmd_params);
    }

    virtual void xgroup_delconsumer(cref_string key, cref_string groupname,
        cref_string consumername) override
    {
        send_command({ cmd::streams::XGROUP, kwd::DELCONSUMER, key,
            groupname, consumername });
    }

    virtual void xgroup_destroy(cref_string key, cref_string groupname) override
    {
        send_command({ cmd::streams::XGROUP, kwd::DESTROY, key, groupname });
    }

    virtual void xgroup_setid(cref_string key, cref_string groupname,
        cref_string id) override
    {
        send_command({ cmd::streams::XGROUP, kwd::SETID, groupname, id });
    }

    virtual void xgroup_help() override
    {
        send_command({ cmd::streams::XGROUP, kwd::HELP });
    }

    virtual void xinfo_consumers(cref_string key, cref_string groupname) override
    {
        send_command({ cmd::streams::XINFO, kwd::CONSUMERS, key, groupname });
    }

    virtual void xinfo_groups(cref_string key) override
    {
        send_command({ cmd::streams::XINFO, kwd::GROUPS, key });
    }

    virtual void xinfo_stream(cref_string key) override
    {
        send_command({ cmd::streams::XINFO, kwd::STREAM, key });
    }

    virtual void xinfo_help() override
    {
        send_command({ cmd::streams::XINFO, kwd::HELP });
    }

    virtual void xlen(cref_string key) override
    {
        send_command({ cmd::streams::XLEN, key });
    }

    virtual void xpending(cref_string key, cref_string group) override
    {
        send_command({ cmd::streams::XPENDING, key, group });
    }

    virtual void xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count) override
    {
        send_command({ cmd::streams::XPENDING, key, group,
            start, end, std::to_string(count) });
    }

    virtual void xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count,
        cref_string consumer) override
    {
        send_command({ cmd::streams::XPENDING, key, group,
            start, end, std::to_string(count), consumer });
    }

    virtual void xrange(cref_string key,
        cref_string start, cref_string end) override
    {
        send_command({ cmd::streams::XRANGE, key, start, end });
    }

    virtual void xrange(cref_string key,
        cref_string start, cref_string end, czint count) override
    {
        send_command({ cmd::streams::XRANGE, key, start, end,
            kwd::COUNT, std::to_string(count) });
    }

    virtual void xread(const xread_param& param, cref_string_array keys,
        cref_stream_id_array ids) override
    {
        string_array param_array;
        param.append_params(param_array);
        param_array.emplace_back(kwd::STREAMS);
        send_command({ {cmd::streams::XREAD}, param_array,
            keys, stream_id_array_to_string_array(ids) });
    }

    virtual void xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string_array keys,
        cref_stream_id_array ids) override
    {
        string_array param_array;
        param.append_params(param_array);
        if (noack)
            param_array.emplace_back(kwd::NOACK);
        param_array.emplace_back(kwd::STREAMS);
        send_command({ {cmd::streams::XREADGROUP}, param_array,
            keys, stream_id_array_to_string_array(ids) });
    }

    virtual void xrevrange(cref_string key,
        cref_string end, cref_string start) override
    {
        send_command({ cmd::streams::XREVRANGE, key, start, end });
    }

    virtual void xrevrange(cref_string key,
        cref_string end, cref_string start, czint count) override
    {
        send_command({ cmd::streams::XREVRANGE, key, start, end,
            kwd::COUNT, std::to_string(count) });
    }

    virtual void xtrim(cref_string key, czint threshold,
        bool almost_exact = false) override
    {
        string_array cmd_params = { cmd::streams::XTRIM, key };
        cmd_params.emplace_back(kwd::MAXLEN);
        if (almost_exact)
            cmd_params.emplace_back(kwd::ALMOST_EXACT);
        cmd_params.emplace_back(std::to_string(threshold));
        send_command(cmd_params);
    }

//strings

    virtual void append(cref_string key, cref_string value) override
    {
        send_command({ cmd::strings::APPEND, value });
    }

    virtual void bitcount(cref_string key, czint start, czint end) override
    {
        send_command({ cmd::strings::BITCOUNT, key,
            std::to_string(start), std::to_string(end) });
    }

    virtual void bitop(bit_operation op, cref_string dest_key,
        cref_string_array keys) override
    {
        send_command({ cmd::strings::BITOP, bit_operation_dict.at(op), dest_key }, keys);
    }

    virtual void decr(cref_string key) override
    {
        send_command({ cmd::strings::DECR, key });
    }

    virtual void decrby(cref_string key, czint decrement) override
    {
        send_command({ cmd::strings::DECRBY, key, std::to_string(decrement) });
    }

    virtual void get(cref_string key) override
    {
        send_command({ cmd::strings::GET, key });
    }

    virtual void getbit(cref_string key, czint offset) override
    {
        if (offset < 0)
            throw redis_commmand_error("ERR bit offset is not an integer or out of range");
        send_command({ cmd::strings::GETBIT, key, std::to_string(offset) });
    }

    virtual void getrange(cref_string key, czint start, czint end) override
    {
        send_command({ cmd::strings::GETRANGE, key,
            std::to_string(start), std::to_string(end) });
    }

    virtual void getset(cref_string key, cref_string value) override
    {
        send_command({ cmd::strings::GETSET, key, value });
    }

    virtual void incr(cref_string key) override
    {
        send_command({ cmd::strings::INCR, key });
    }

    virtual void incrby(cref_string key, czint increment)
    {
        send_command({ cmd::strings::INCRBY, key, std::to_string(increment) });
    }

    virtual void incrbyfloat(cref_string key, double increment) override
    {
        send_command({ cmd::strings::INCRBYFLOAT, key, std::to_string(increment) });
    }

    virtual void mget(cref_string_array keys) override
    {
        send_command({ cmd::strings::MGET }, keys);
    }

    virtual void mset(cref_string_array key_value_pairs) override
    {
        if (key_value_pairs.size() == 0 || key_value_pairs.size() % 2 != 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'mset' command");
        send_command({ cmd::strings::MSET }, key_value_pairs);
    }

    virtual void msetnx(cref_string_array key_value_pairs) override
    {
        if (key_value_pairs.size() == 0 || key_value_pairs.size() % 2 != 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'msetnx' command");
        send_command({ cmd::strings::MSETNX }, key_value_pairs);
    }

    virtual void psetex(cref_string key, czint milliseconds, cref_string value) override
    {
        if (milliseconds <= 0)
            throw redis_commmand_error("ERR invalid expire time in psetex");
        send_command({ cmd::strings::PSETEX, key, std::to_string(milliseconds), value });
    }

    virtual void set(cref_string key, cref_string value, cref_string_array params = {}) override
    {
        if (params.size() == 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'set' command");
        send_command({ cmd::strings::SET, key, value }, params);
    }

    virtual void setbit(cref_string key, czint offset, czbit bit) override
    {
        send_command({ cmd::strings::SETBIT, key, std::to_string(offset), (bit ? "1" : "0") });
    }

    virtual void setex(cref_string key, czint seconds, cref_string value) override
    {
        if (seconds <= 0)
            throw redis_commmand_error("ERR invalid expire time in setex");
        send_command({ cmd::strings::SETEX, key, std::to_string(seconds), value });
    }

    virtual void setnx(cref_string key, cref_string value) override
    {
        send_command({ cmd::strings::SETNX, key, value });
    }

    virtual void setrange(cref_string key, czint offset, cref_string value) override
    {
        if (offset < 0)
            throw redis_commmand_error("ERR offset is out of range");
        send_command({ cmd::strings::SETRANGE, key, std::to_string(offset), value });
    }

    virtual void strlen(cref_string key) override
    {
        send_command({ cmd::strings::STRLEN, key });
    }

//transactions

    virtual void discard() override
    {
        if (!is_in_multi())
            throw redis_commmand_error("ERR DISCARD without MULTI");

        send_command({ cmd::transactions::DISCARD });
        is_in_multi_ = false;
        is_in_watch_ = false;
    }

    virtual void exec() override
    {
        if (!is_in_multi())
            throw redis_commmand_error("ERR EXEC without MULTI");

        send_command({ cmd::transactions::EXEC });
        is_in_multi_ = false;
        is_in_watch_ = false;
    }

    virtual void multi() override
    {
        if (is_in_multi())
            throw redis_commmand_error("ERR MULTI calls can not be nested");

        send_command({ cmd::transactions::MULTI });
        is_in_multi_ = true;
    }

    virtual void unwatch() override
    {
        send_command({ cmd::transactions::UNWATCH });
        is_in_watch_ = false;
    }

    virtual void watch(cref_string_array keys) override
    {
        send_command({ cmd::transactions::WATCH }, keys);
        is_in_watch_ = true;
    }

private:
    std::string     host_;
    std::string     port_;
    czstring        username_;
    czstring        password_;
    unsigned        database_;
    bool            is_in_multi_ = false;
    bool            is_in_watch_ = false;
    size_t          send_count_ = 0;

    resp            resp_{ *this };

    void check_connect() const
    {
        if (!is_connected())
            throw redis_connection_error("not connected");
    }
};

} // namespace detail
} // namespace czredis
