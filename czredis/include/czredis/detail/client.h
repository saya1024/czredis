#pragma once

#include "client_config.h"
#include "command.h"
#include "data_cast.h"
#include "delay_queue.h"
#include "interface.h"
#include "resp.h"

namespace czredis
{
namespace detail
{

class client : public socket, public delay_queue, public i_commands
{
    using my_base = socket;

    czstring    host_;
    czstring    port_;
    czstring    username_;
    czstring    password_;
    unsigned    database_;
    bool        is_in_multi_ = false;
    bool        is_in_watch_ = false;
    size_t      send_count_ = 0;
    resp        resp_{ *this };

public:
    client(cref_string host, cref_string port, const client_config& config) :
        host_(host),
        port_(port),
        username_(config.username()),
        password_(config.password()),
        database_(config.database())
    {
        set_connect_timeout(config.connect_timeout());
        set_read_timeout(config.socket_read_timeout());
        set_write_timeout(config.socket_write_timeout());
    }

    ~client() noexcept override
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

    void disconnect() noexcept override
    {
        if (is_connected())
        {
            my_base::disconnect();
            send_count_ = 0;
            is_in_multi_ = false;
            is_in_watch_ = false;
        }
    }

    void clean_state() noexcept
    {
        try
        {
            if (is_connected())
            {
                if (is_in_multi())
                    discard();
                if (is_in_watch())
                    unwatch();
                get_all_reply();
            }
        }
        catch (...)
        {
            disconnect();
        }
    }

    void prepare() override final
    {
        clean_state();
        if (!is_connected())
            do_connect();
    }

    bool check_health() override final
    {
        try
        {
            prepare();
            ping();
            return get_one_reply().as_string() == keyword::PONG;
        }
        catch (...)
        {
            disconnect();
            return false;
        }
    }

    void send_command(cref_string_array params)
    {
        resp_.send_command(params);
        ++send_count_;
    }

    void send_command(cref_string_array params1, cref_string_array params2)
    {
        resp_.send_command(params1, params2);
        ++send_count_;
    }

    void send_command(std::initializer_list<string_array> params_array)
    {
        resp_.send_command(params_array);
        ++send_count_;
    }

    void send_command(std::initializer_list<czstring> params)
    {
        resp_.send_command(params);
        ++send_count_;
    }

    reply get_one_reply()
    {
        --send_count_;
        try
        {
            return resp_.get_reply();
        }
        catch (const std::exception& e)
        {
            resp_.reset_stream();
            throw e;
        }
    }

    reply_array get_all_reply()
    {
        reply_array arr;
        arr.reserve(send_count_);
        while (send_count_ > 0)
        {
            arr.emplace_back(get_one_reply());
        }
        delay_queue_clear();
        return arr;
    }

    template<typename T>
    T get_reply_as()
    {
        return reply_cast<T>(get_one_reply());
    }

    template<typename T>
    delay<T> make_delay()
    {
        return delay_queue::make_delay<T>(is_in_multi_);
    }

    void build_all_delay()
    {
        reply_array arr;
        arr.reserve(send_count_);
        while (send_count_ > 0)
        {
            arr.emplace_back(get_one_reply());
        }
        delay_queue::build_all_delay(std::move(arr));
    }

    size_t send_count() const noexcept { return send_count_; }

    czstring password() const noexcept { return password_; }

    czstring username() const noexcept { return username_; }

    unsigned database() const noexcept { return database_; }

    void set_password(cref_string pwd)
    {
        password_ = pwd;
    }

    void set_username(cref_string name)
    {
        username_ = name;
    }

    void set_database(unsigned db) noexcept
    {
        database_ = db;
    }

    bool is_in_multi() const noexcept { return is_in_multi_; }

    bool is_in_watch() const noexcept { return is_in_watch_; }

private:
    void err_arguments_number(bool wrong, cref_string cmd)
    {
        if (wrong)
            throw redis_commmand_error(
                "ERR wrong number of arguments for '" + cmd + "' command");
    }

public:

//connection

    void auth(cref_string password) override final
    {
        send_command({ command::AUTH, password });
        set_password(password);
    }

    void auth(cref_string username, cref_string password) override final
    {
        send_command({ command::AUTH, username, password });
        set_username(username);
        set_password(password);
    }

    void echo(cref_string message) override final
    {
        send_command({ command::ECHO, message });
    }

    void ping() override final
    {
        send_command({ command::PING });
    }

    void quit() override final
    {
        send_command({ command::QUIT });
    }

    void select(unsigned index) override final
    {
        send_command({ command::SELECT, std::to_string(index) });
        set_database(index);
    }

//geo

    void geoadd(cref_string key, double longitude,
        double latitude, cref_string member) override final
    {
        send_command({ command::GEOADD, key,
            std::to_string(longitude), std::to_string(latitude), member });
    }

    void geoadd(cref_string key,
        hmap<czstring, geo_coordinate> members_coordinates) override final
    {
        err_arguments_number(members_coordinates.empty(), command::GEOADD);
        string_array cmd_params = { command::GEOADD ,key };
        for (auto& o : members_coordinates)
        {
            cmd_params.emplace_back(std::to_string(o.second.longitude));
            cmd_params.emplace_back(std::to_string(o.second.latitude));
            cmd_params.emplace_back(o.first);
        }
        send_command(cmd_params);
    }

    void geodist(cref_string key, cref_string member1,
        cref_string member2, geo_unit unit) override final
    {
        send_command({ command::GEODIST, key, member1, member2,
            geo_unit_dict.at(unit) });
    }

    void geohash(cref_string key, cref_string_array members) override final
    {
        err_arguments_number(members.empty(), command::GEOHASH);
        send_command({ command::GEOHASH, key }, members);
    }

    void geopos(cref_string key, cref_string_array members) override final
    {
        err_arguments_number(members.empty(), command::GEOPOS);
        send_command({ command::GEOPOS, key }, members);
    }

    void georadius(cref_string key, double longitude, double latitude,
        double radius, geo_unit unit, const georadius_param& param,
        const georadius_store_param& store_param) override final
    {
        send_command({ {command::GEORADIUS, key, std::to_string(longitude),
            std::to_string(latitude), std::to_string(radius),
            geo_unit_dict.at(unit)}, param.to_string_array(),
            store_param.to_string_array() });
    }

    void georadius_RO(cref_string key, double longitude, double latitude,
        double radius, geo_unit unit, const georadius_param& param) override final
    {
        send_command({ {command::GEORADIUS_RO, key, std::to_string(longitude),
            std::to_string(latitude), std::to_string(radius),
            geo_unit_dict.at(unit)}, param.to_string_array() });
    }

    void georadiusbymember(cref_string key, cref_string member,
        double radius, geo_unit unit, const georadius_param& param,
        const georadius_store_param& store_param) override final
    {
        send_command({ {command::GEORADIUSBYMEMBER, key, member,
            std::to_string(radius), geo_unit_dict.at(unit)},
            param.to_string_array(), store_param.to_string_array() });
    }

    void georadiusbymember_RO(cref_string key, cref_string member,
        double radius, geo_unit unit, const georadius_param& param) override final
    {
        send_command({ {command::GEORADIUSBYMEMBER_RO, key, member,
            std::to_string(radius), geo_unit_dict.at(unit)},
            param.to_string_array() });
    }

//hashes

    void hdel(cref_string key, cref_string_array fields) override final
    {
        err_arguments_number(fields.empty(), command::HDEL);
        send_command({ command::HDEL }, fields);
    }

    void hexists(cref_string key, cref_string field) override final
    {
        send_command({ command::HEXISTS, key, field });
    }

    void hget(cref_string key, cref_string field) override final
    {
        send_command({ command::HGET, key, field });
    }

    void hgetall(cref_string key) override final
    {
        send_command({ command::HGET, key });
    }

    void hincrby(cref_string key, cref_string field,
        czint increment) override final
    {
        send_command({ command::HINCRBY, key, field,
            std::to_string(increment) });
    }

    void hincrbyfloat(cref_string key, cref_string field,
        double increment) override final
    {
        send_command({ command::HINCRBYFLOAT, key, field,
            std::to_string(increment) });
    }

    void hkeys(cref_string key) override final
    {
        send_command({ command::HKEYS, key });
    }

    void hlen(cref_string key) override final
    {
        send_command({ command::HLEN, key });
    }

    void hmget(cref_string key, cref_string_array fields) override final
    {
        err_arguments_number(fields.empty(), command::HMGET);
        send_command({ command::HMGET, key }, fields);
    }

    void hmset(cref_string key, cref_string_array fields_values) override final
    {
        err_arguments_number(fields_values.empty() ||
            (fields_values.size() % 2 != 0), command::HMSET);
        send_command({ command::HMSET, key }, fields_values);
    }

    void hscan(cref_string key, cref_string cursor,
        const scan_param& param) override final
    {
        send_command({ command::HSCAN, key, cursor },
            param.to_string_array());
    }

    void hset(cref_string key, cref_string field,
        cref_string value) override final
    {
        send_command({ command::HSET, key, field, value });
    }

    void hsetnx(cref_string key, cref_string field,
        cref_string value) override final
    {
        send_command({ command::HSETNX, key, field, value });
    }

    void hstrlen(cref_string key, cref_string field) override final
    {
        send_command({ command::HSTRLEN, key, field });
    }

    void hvals(cref_string key) override final
    {
        send_command({ command::HVALS, key });
    }

//hyper_log_log
    void pfadd(cref_string key, cref_string_array elements) override final
    {
        err_arguments_number(elements.empty(), command::PFADD);
        send_command({ command::PFADD, key }, elements);
    }

    void pfcount(cref_string key) override final
    {
        send_command({ command::PFCOUNT, key });
    }

    void pfcount(cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::PFCOUNT);
        send_command({ command::PFCOUNT }, keys);
    }

    void pfmerge(cref_string destkey, cref_string_array sourcekeys) override final
    {
        err_arguments_number(sourcekeys.empty(), command::PFMERGE);
        send_command({ command::PFMERGE, destkey }, sourcekeys);
    }

//keys

    void del(cref_string key) override final
    {
        send_command({ command::DEL, key });
    }

    void del(cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::DEL);
        send_command({ command::DEL }, keys);
    }

    void dump(cref_string key) override final
    {
        send_command({ command::DUMP, key });
    }

    void exists(cref_string key) override final
    {
        send_command({ command::EXISTS, key });
    }

    void expire(cref_string key, czint seconds) override final
    {
        send_command({ command::EXPIRE, key, std::to_string(seconds) });
    }

    void expireat(cref_string key, czint timestamp) override final
    {
        send_command({ command::EXPIREAT, key, std::to_string(timestamp) });
    }

    void keys(cref_string pattern) override final
    {
        send_command({ command::KEYS, pattern });
    }

    void migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout, const migrate_param& param) override final
    {
        send_command({ command::MIGRATE, host, port, key,
            std::to_string(destination_db), std::to_string(timeout) },
            param.to_string_array());
    }

    void migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param,
        cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::MIGRATE);
        send_command({ {command::MIGRATE, host, port, "",
            std::to_string(destination_db), std::to_string(timeout)},
            param.to_string_array(), {keyword::KEYS}, keys });
    }

    void move(cref_string key, unsigned db) override final
    {
        send_command({ command::MOVE, key, std::to_string(db) });
    }

    void object_refcount(cref_string key) override final
    {
        send_command({ command::OBJECT, keyword::REFCOUNT, key });
    }

    void object_encoding(cref_string key) override final
    {
        send_command({ command::OBJECT, keyword::ENCODING, key });
    }

    void object_idletime(cref_string key) override final
    {
        send_command({ command::OBJECT, keyword::IDLETIME, key });
    }

    void object_freq(cref_string key) override final
    {
        send_command({ command::OBJECT, keyword::FREQ, key });
    }

    void object_help() override final
    {
        send_command({ command::OBJECT, keyword::HELP });
    }

    void persist(cref_string key) override final
    {
        send_command({ command::PERSIST, key });
    }

    void pexpire(cref_string key, czint milliseconds) override final
    {
        send_command({ command::PEXPIRE, key, std::to_string(milliseconds) });
    }

    void pexpireat(cref_string key, czint milliseconds_timestamp) override final
    {
        send_command({ command::PEXPIREAT, key,
            std::to_string(milliseconds_timestamp) });
    }

    void pttl(cref_string key) override final
    {
        send_command({ command::PTTL, key });
    }

    void randomkey() override final
    {
        send_command({ command::RANDOMKEY });
    }

    void rename(cref_string key, cref_string new_key) override final
    {
        send_command({ command::RENAME, key, new_key });
    }

    void renamenx(cref_string key, cref_string new_key) override final
    {
        send_command({ command::RENAMENX, key, new_key });
    }

    void restore(cref_string key, czint ttl,
        cref_string serialized_value, const restore_param& param) override final
    {
        send_command({ command::RESTORE, key, std::to_string(ttl),
            serialized_value }, param.to_string_array());
    }

    void scan(cref_string cursor, const scan_param& param) override final
    {
        send_command({ command::PERSIST, cursor }, param.to_string_array());
    }

    void scan(cref_string cursor, const scan_param& param,
        redis_key_type type) override final
    {
        send_command({ {command::PERSIST, cursor},
            param.to_string_array(),
            {keyword::TYPE, redis_key_type_dict.at(type)} });
    }

    void sort(cref_string key, const sort_param& param) override final
    {
        send_command({ command::SORT, key }, param.to_string_array());
    }

    void sort(cref_string key, const sort_param& param, cref_string destination) override final
    {
        send_command({ {command::SORT, key}, param.to_string_array(),
            {keyword::STORE, destination} });
    }

    void touch(cref_string key) override final
    {
        send_command({ command::TOUCH, key });
    }

    void touch(cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::TOUCH);
        send_command({ command::TOUCH }, keys);
    }

    void ttl(cref_string key) override final
    {
        send_command({ command::TTL, key });
    }

    void type(cref_string key) override final
    {
        send_command({ command::TYPE, key });
    }

    void unlink(cref_string key) override final
    {
        send_command({ command::UNLINK, key });
    }

    void unlink(cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::UNLINK);
        send_command({ command::UNLINK }, keys);
    }

    void wait(unsigned numreplicas, czint timeout) override final
    {
        send_command({ command::WAIT, std::to_string(numreplicas),
            std::to_string(timeout) });
    }

//lists

    void blpop(cref_string key, czint timeout) override final
    {
        send_command({ command::BLPOP, key, std::to_string(timeout) });
    }

    void blpop(cref_string_array keys, czint timeout) override final
    {
        err_arguments_number(keys.empty(), command::BLPOP);
        send_command({{ command::BLPOP }, keys, { std::to_string(timeout) }});
    }

    void brpop(cref_string key, czint timeout) override final
    {
        send_command({ command::BRPOP, key, std::to_string(timeout) });
    }

    void brpop(cref_string_array keys, czint timeout) override final
    {
        err_arguments_number(keys.empty(), command::BRPOP);
        send_command({ { command::BRPOP }, keys, { std::to_string(timeout) } });
    }

    void brpoplpush(cref_string source, cref_string destination,
        czint timeout) override final
    {
        send_command({ command::BRPOPLPUSH, source, destination,
            std::to_string(timeout) });
    }

    void lindex(cref_string key, czint index) override final
    {
        send_command({ command::LINDEX, std::to_string(index) });
    }

    void linsert(cref_string key, insert_place place,
        cref_string pivot, cref_string value) override final
    {
        send_command({ command::LINSERT, insert_place_dict.at(place),
            pivot, value });
    }

    void llen(cref_string key) override final
    {
        send_command({ command::LLEN, key });
    }

    void lpop(cref_string key) override final
    {
        send_command({ command::LPOP, key });
    }

    void lpush(cref_string key, cref_string_array elements) override final
    {
        err_arguments_number(elements.empty(), command::LPUSH);
        send_command({ command::LPUSH, key }, elements);
    }

    void lpushx(cref_string key, cref_string_array elements) override final
    {
        err_arguments_number(elements.empty(), command::LPUSHX);
        send_command({ command::LPUSHX, key }, elements);
    }

    void lrange(cref_string key, czint start, czint stop) override final
    {
        send_command({ command::LRANGE, key,
            std::to_string(start), std::to_string(stop) });
    }

    void lrem(cref_string key, czint count, cref_string element) override final
    {
        send_command({ command::LREM, key, std::to_string(count), element });
    }

    void lset(cref_string key, czint index, cref_string element) override final
    {
        send_command({ command::LSET, key, std::to_string(index), element });
    }

    void ltrim(cref_string key, czint start, czint stop) override final
    {
        send_command({ command::LTRIM, key,
            std::to_string(start), std::to_string(stop) });
    }

    void rpop(cref_string key) override final
    {
        send_command({ command::RPOP, key });
    }

    void rpoplpush(cref_string source, cref_string destination) override final
    {
        send_command({ command::BRPOPLPUSH, source, destination });
    }

    void rpush(cref_string key, cref_string_array elements) override final
    {
        err_arguments_number(elements.empty(), command::RPUSH);
        send_command({ command::RPUSH, key }, elements);
    }

    void rpushx(cref_string key, cref_string_array elements) override final
    {
        err_arguments_number(elements.empty(), command::RPUSHX);
        send_command({ command::RPUSHX, key }, elements);
    }

//scripting

    void eval(cref_string script,
        cref_string_array keys, cref_string_array args) override final
    {
        send_command({{ command::EVAL, script,
            std::to_string(keys.size()) }, keys, args});
    }

    void evalsha(cref_string sha1,
        cref_string_array keys, cref_string_array args) override final
    {
        send_command({ { command::EVALSHA, sha1,
            std::to_string(keys.size()) }, keys, args });
    }

    void script_exists(cref_string sha1) override final
    {
        send_command({ command::SCRIPT, keyword::EXISTS, sha1 });
    }

    void script_exists(cref_string_array sha1s) override final
    {
        send_command({ command::SCRIPT, keyword::EXISTS }, sha1s);
    }

    void script_flush() override final
    {
        send_command({ command::SCRIPT, keyword::FLUSH });
    }

    void script_kill() override final
    {
        send_command({ command::SCRIPT, keyword::KILL });
    }

    void script_load(cref_string script) override final
    {
        send_command({ command::SCRIPT, keyword::LOAD, script });
    }

//server

    void bgrewriteaof() override final
    {
        send_command({ command::BGREWRITEAOF });
    }

    void bgsave(bool schedule) override final
    {
        if (schedule)
            send_command({ command::BGSAVE, keyword::SCHEDULE });
        else
            send_command({ command::BGSAVE });
    }

    void config_get(cref_string parameter)
    {
        send_command({ command::CONFIG, keyword::GET, parameter });
    }

    void config_resetstat() override final
    {
        send_command({ command::CONFIG, keyword::RESETSTAT });
    }

    void config_set(cref_string parameter, cref_string value) override final
    {
        send_command({ command::CONFIG, keyword::SET });
    }

    void dbsize() override final
    {
        send_command({ command::DBSIZE });
    }

    void flushall(const flush_param& param) override final
    {
        send_command({ command::FLUSHALL }, param.to_string_array());
    }

    void flushdb(const flush_param& param) override final
    {
        send_command({ command::FLUSHDB }, param.to_string_array());
    }

    void info() override final
    {
        send_command({ command::INFO });
    }

    void info(cref_string section) override final
    {
        send_command({ command::INFO, section });
    }

    void lastsave() override final
    {
        send_command({ command::LASTSAVE });
    }

    void memory_doctor() override final
    {
        send_command({ command::MEMORY, keyword::DOCTOR });
    }

    void memory_usage(cref_string key) override final
    {
        send_command({ command::MEMORY, keyword::USAGE, key });
    }

    void memory_usage(cref_string key, czint samples) override final
    {
        send_command({ command::MEMORY, keyword::USAGE, key,
            keyword::SAMPLES, std::to_string(samples) });
    }

    void module_list() override final
    {
        send_command({ command::MODULE, keyword::LIST });
    }

    void module_load(cref_string path, cref_string_array args) override final
    {
        send_command({ command::MODULE, keyword::LOAD });
    }

    void module_unload(cref_string name) override final
    {
        send_command({ command::MODULE, keyword::UNLOAD });
    }

    void replicaof(cref_string host, cref_string port) override final
    {
        send_command({ command::REPLICAOF, host, port });
    }

    void replicaof_no_one() override final
    {
        send_command({ command::REPLICAOF, keyword::NO, keyword::ONE });
    }

    void save() override final
    {
        send_command({ command::SAVE });
    }

    void shutdown() override final
    {
        send_command({ command::SHUTDOWN });
    }

    void slaveof(cref_string host, cref_string port) override final
    {
        send_command({ command::SLAVEOF, host, port });
    }

    void slaveof_no_one() override final
    {
        send_command({ command::SLAVEOF, keyword::NO, keyword::ONE });
    }

    void slowlog_get() override final
    {
        send_command({ command::SLOWLOG, keyword::GET });
    }

    void slowlog_get(czint entries) override final
    {
        send_command({ command::SLOWLOG, keyword::GET, std::to_string(entries) });
    }

    void slowlog_len() override final
    {
        send_command({ command::SLOWLOG, keyword::LEN });
    }

    void slowlog_reset() override final
    {
        send_command({ command::SLOWLOG, keyword::RESET });
    }

    void swapdb(unsigned index1, unsigned index2) override final
    {
        send_command({ command::SWAPDB, std::to_string(index1), std::to_string(index2) });
    }

    void time() override final
    {
        send_command({ command::TIME });
    }

//sets

    void sadd(cref_string key, cref_string_array members) override final
    {
        err_arguments_number(members.empty(), command::SADD);
        send_command({ command::SADD, key }, members);
    }

    void scard(cref_string key) override final
    {
        send_command({ command::SCARD, key });
    }

    void sdiff(cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::SDIFF);
        send_command({ command::SDIFF }, keys);
    }

    void sdiffstore(cref_string destination, cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::SDIFFSTORE);
        send_command({ command::SDIFFSTORE, destination }, keys);
    }

    void sinter(cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::SINTER);
        send_command({ command::SINTER }, keys);
    }

    void sinterstore(cref_string destination, cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::SINTERSTORE);
        send_command({ command::SINTERSTORE, destination }, keys);
    }

    void sismember(cref_string key, cref_string member) override final
    {
        send_command({ command::SISMEMBER, key, member });
    }

    void smembers(cref_string key) override final
    {
        send_command({ command::SMEMBERS, key });
    }

    void smove(cref_string source, cref_string destination,
        cref_string member) override final
    {
        send_command({ command::SMOVE, source, destination, member });
    }

    void spop(cref_string key) override final
    {
        send_command({ command::SPOP, key });
    }

    void spop(cref_string key, czint count) override final
    {
        send_command({ command::SPOP, key,
            keyword::COUNT, std::to_string(count) });
    }

    void srandmember(cref_string key) override final
    {
        send_command({ command::SRANDMEMBER, key });
    }

    void srandmember(cref_string key, czint count) override final
    {
        send_command({ command::SRANDMEMBER, key,
            keyword::COUNT, std::to_string(count) });
    }

    void srem(cref_string key, cref_string_array members) override final
    {
        err_arguments_number(members.empty(), command::SREM);
        send_command({ command::SREM, key }, members);
    }

    void sscan(cref_string key, cref_string cursor,
        const scan_param& param) override final
    {
        send_command({ command::SSCAN, key, cursor },
            param.to_string_array());
    }

    void sunion(cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::SUNION);
        send_command({ command::SUNION }, keys);
    }

    void sunionstore(cref_string destination, cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::SUNIONSTORE);
        send_command({ command::SUNIONSTORE, destination }, keys);
    }

//sorted_sets

    void bzpopmax(cref_string key, czint timeout) override final
    {
        send_command({ command::BZPOPMAX, key,std::to_string(timeout) });
    }

    void bzpopmax(cref_string_array keys, czint timeout) override final
    {
        err_arguments_number(keys.empty(), command::BZPOPMAX);
        send_command({ {command::BZPOPMAX}, keys, {std::to_string(timeout)} });
    }

    void bzpopmin(cref_string key, czint timeout) override final
    {
        send_command({ command::BZPOPMIN, key,std::to_string(timeout) });
    }

    void bzpopmin(cref_string_array keys, czint timeout) override final
    {
        err_arguments_number(keys.empty(), command::BZPOPMIN);
        send_command({ {command::BZPOPMIN}, keys, {std::to_string(timeout)} });
    }

    void zadd(cref_string key, const zadd_param& param,
        cref_string_array scores_members) override final
    {
        err_arguments_number(scores_members.empty() ||
            (scores_members.size() % 2 != 0), command::ZADD);
        send_command({ {command::ZADD, key},
            param.to_string_array(), scores_members });
    }

    void zcard(cref_string key) override final
    {
        send_command({ command::ZCARD, key });
    }

    void zcount(cref_string key, cref_string min, cref_string max) override final
    {
        send_command({ command::ZCOUNT, key, min, max });
    }

    void zincrby(cref_string key, cref_string increment,
        cref_string member) override final
    {
        send_command({ command::ZINCRBY, key, increment, member });
    }

    void zinterstore(cref_string destination, cref_string_array keys,
        const zstore_param& param) override final
    {
        err_arguments_number(keys.empty(), command::ZINTERSTORE);
        send_command({{ command::ZINTERSTORE, destination,
            std::to_string(keys.size()) }, keys, param.to_string_array()});
    }

    void zlexcount(cref_string key, cref_string min, cref_string max) override final
    {
        send_command({ command::ZLEXCOUNT, key, min, max });
    }

    void zpopmax(cref_string key) override final
    {
        send_command({ command::ZPOPMAX, key });
    }

    void zpopmax(cref_string key, czint count) override final
    {
        send_command({ command::ZPOPMAX, key,
            std::to_string(count) });
    }

    void zpopmin(cref_string key) override final
    {
        send_command({ command::ZPOPMIN, key });
    }

    void zpopmin(cref_string key, czint count) override final
    {
        send_command({ command::ZPOPMIN, key,
            std::to_string(count) });
    }

    void zrange(cref_string key, czint start, czint stop,
        bool withscores = false) override final
    {
        string_array cmd_params = { command::ZRANGE, key,
            std::to_string(start), std::to_string(stop) };
        if (withscores)
            cmd_params.emplace_back(keyword::WITHSCORES);
        send_command(cmd_params);
    }

    void zrangebylex(cref_string key, cref_string max, cref_string min) override final
    {
        send_command({ command::ZRANGEBYLEX, key, max, min });
    }

    void zrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) override final
    {
        send_command({ command::ZRANGEBYLEX, key, max, min,
            keyword::LIMIT, std::to_string(offset), std::to_string(count) });
    }

    void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores = false) override final
    {
        string_array cmd_params = { command::ZRANGEBYSCORE, key,
            min, max };
        if (withscores)
            cmd_params.emplace_back(keyword::WITHSCORES);
        send_command(cmd_params);
    }

    void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override final
    {
        string_array cmd_params = { command::ZRANGEBYSCORE, key,
            min, max };
        if (withscores)
            cmd_params.emplace_back(keyword::WITHSCORES);
        cmd_params.emplace_back(keyword::LIMIT);
        cmd_params.emplace_back(std::to_string(offset));
        cmd_params.emplace_back(std::to_string(count));
        send_command(cmd_params);
    }

    void zrank(cref_string key, cref_string member) override final
    {
        send_command({ command::ZRANK, key, member });
    }

    void zrem(cref_string key, cref_string_array members) override final
    {
        err_arguments_number(members.empty(), command::ZREM);
        send_command({ command::ZREM, key }, members);
    }

    void zremrangebylex(cref_string key,
        cref_string min, cref_string max) override final
    {
        send_command({ command::ZREMRANGEBYLEX, key, min, max });
    }

    void zremrangebyrank(cref_string key,
        czint start, czint stop) override final
    {
        send_command({ command::ZREMRANGEBYRANK, key,
            std::to_string(start), std::to_string(stop) });
    }

    void zremrangebyscore(cref_string key,
        cref_string min, cref_string max) override final
    {
        send_command({ command::ZREMRANGEBYSCORE, key, min, max });
    }

    void zrevrange(cref_string key, czint start, czint stop,
        bool withscores = false) override final
    {
        string_array cmd_params = { command::ZREVRANGE, key,
            std::to_string(start), std::to_string(stop) };
        if (withscores)
            cmd_params.emplace_back(keyword::WITHSCORES);
        send_command(cmd_params);
    }

    void zrevrangebylex(cref_string key,
        cref_string max, cref_string min) override final
    {
        send_command({ command::ZREVRANGEBYLEX, key, max, min });
    }

    void zrevrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) override final
    {
        send_command({ command::ZREVRANGEBYLEX, key, max, min,
            keyword::LIMIT, std::to_string(offset), std::to_string(count) });
    }

    void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores = false) override final
    {
        string_array cmd_params = { command::ZREVRANGEBYSCORE, key,
            min, max };
        if (withscores)
            cmd_params.emplace_back(keyword::WITHSCORES);
        send_command(cmd_params);
    }

    void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) override final
    {
        string_array cmd_params = { command::ZREVRANGEBYSCORE, key,
            min, max };
        if (withscores)
            cmd_params.emplace_back(keyword::WITHSCORES);
        cmd_params.emplace_back(keyword::LIMIT);
        cmd_params.emplace_back(std::to_string(offset));
        cmd_params.emplace_back(std::to_string(count));
        send_command(cmd_params);
    }

    void zrevrank(cref_string key, cref_string member) override final
    {
        send_command({ command::ZREVRANK, key, member });
    }

    void zscan(cref_string key, cref_string cursor,
        const scan_param& param) override final
    {
        send_command({ command::ZSCAN, key, cursor },
            param.to_string_array());
    }

    void zscore(cref_string key, cref_string member) override final
    {
        send_command({ command::ZSCORE, key, member });
    }

    void zunionstore(cref_string destination, cref_string_array keys,
        const zstore_param& param) override final
    {
        err_arguments_number(keys.empty(), command::ZUNIONSTORE);
        send_command({ { command::ZUNIONSTORE, destination,
            std::to_string(keys.size()) }, keys, param.to_string_array() });
    }

//streams

    void xack(cref_string key, cref_string group,
        cref_stream_id_array ids) override final
    {
        err_arguments_number(ids.empty(), command::XACK);
        send_command({ command::XACK, key, group },
            to_string_array(ids));
    }

    void xadd(cref_string key, const xadd_param param,
        cref_string id, cref_string_array fields_values) override final
    {
        err_arguments_number(fields_values.empty(), command::XADD);
        send_command({ {command::XADD, key}, param.to_string_array(),
            {id}, fields_values });
    }

    void xclaim(cref_string key, cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids,
        const xclaim_param& param) override final
    {
        err_arguments_number(ids.empty(), command::XCLAIM);
        send_command({ {command::XCLAIM, key, group, consumer,
            std::to_string(min_idle_time)},
            to_string_array(ids), param.to_string_array() });
    }

    void xdel(cref_string key, cref_stream_id_array ids) override final
    {
        err_arguments_number(ids.empty(), command::XDEL);
        send_command({ command::XDEL, key },
            to_string_array(ids));
    }

    void xgroup_create(cref_string key, cref_string groupname,
        cref_string id, bool mkstream = false) override final
    {
        string_array cmd_params = { command::XGROUP, keyword::CREATE,
            key, groupname, id };
        if (mkstream)
            cmd_params.emplace_back(keyword::MKSTREAM);
        send_command(cmd_params);
    }

    void xgroup_delconsumer(cref_string key, cref_string groupname,
        cref_string consumername) override final
    {
        send_command({ command::XGROUP, keyword::DELCONSUMER, key,
            groupname, consumername });
    }

    void xgroup_destroy(cref_string key, cref_string groupname) override final
    {
        send_command({ command::XGROUP, keyword::DESTROY, key, groupname });
    }

    void xgroup_setid(cref_string key, cref_string groupname,
        cref_string id) override final
    {
        send_command({ command::XGROUP, keyword::SETID, groupname, id });
    }

    void xgroup_help() override final
    {
        send_command({ command::XGROUP, keyword::HELP });
    }

    void xinfo_consumers(cref_string key, cref_string groupname) override final
    {
        send_command({ command::XINFO, keyword::CONSUMERS, key, groupname });
    }

    void xinfo_groups(cref_string key) override final
    {
        send_command({ command::XINFO, keyword::GROUPS, key });
    }

    void xinfo_stream(cref_string key) override final
    {
        send_command({ command::XINFO, keyword::STREAM, key });
    }

    void xinfo_help() override final
    {
        send_command({ command::XINFO, keyword::HELP });
    }

    void xlen(cref_string key) override final
    {
        send_command({ command::XLEN, key });
    }

    void xpending(cref_string key, cref_string group) override final
    {
        send_command({ command::XPENDING, key, group });
    }

    void xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count) override final
    {
        send_command({ command::XPENDING, key, group,
            start, end, std::to_string(count) });
    }

    void xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count,
        cref_string consumer) override final
    {
        send_command({ command::XPENDING, key, group,
            start, end, std::to_string(count), consumer });
    }

    void xrange(cref_string key,
        cref_string start, cref_string end) override final
    {
        send_command({ command::XRANGE, key, start, end });
    }

    void xrange(cref_string key,
        cref_string start, cref_string end, czint count) override final
    {
        send_command({ command::XRANGE, key, start, end,
            keyword::COUNT, std::to_string(count) });
    }

    void xread(const xread_param& param, cref_string key,
        cref_stream_id id) override final
    {
        string_array param_array;
        param.append_params(param_array);
        param_array.emplace_back(keyword::STREAMS);
        send_command({ {command::XREAD}, param_array,
            {key, id.to_string()} });
    }

    void xread(const xread_param& param, cref_string_array keys,
        cref_stream_id_array ids) override final
    {
        err_arguments_number(keys.empty() ||
            (keys.size() != ids.size()), command::XREAD);
        string_array param_array;
        param.append_params(param_array);
        param_array.emplace_back(keyword::STREAMS);
        send_command({ {command::XREAD}, param_array,
            keys, to_string_array(ids) });
    }

    void xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string key,
        cref_stream_id id) override final
    {
        string_array param_array;
        param.append_params(param_array);
        if (noack)
            param_array.emplace_back(keyword::NOACK);
        param_array.emplace_back(keyword::STREAMS);
        send_command({ {command::XREADGROUP}, param_array,
            {key, id.to_string()} });
    }

    void xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string_array keys,
        cref_stream_id_array ids) override final
    {
        err_arguments_number(keys.empty() ||
            (keys.size() != ids.size()), command::XREADGROUP);
        string_array param_array;
        param.append_params(param_array);
        if (noack)
            param_array.emplace_back(keyword::NOACK);
        param_array.emplace_back(keyword::STREAMS);
        send_command({ {command::XREADGROUP}, param_array,
            keys, to_string_array(ids) });
    }

    void xrevrange(cref_string key,
        cref_string end, cref_string start) override final
    {
        send_command({ command::XREVRANGE, key, start, end });
    }

    void xrevrange(cref_string key,
        cref_string end, cref_string start, czint count) override final
    {
        send_command({ command::XREVRANGE, key, start, end,
            keyword::COUNT, std::to_string(count) });
    }

    void xtrim(cref_string key, czint threshold,
        bool almost_exact = false) override final
    {
        string_array cmd_params = { command::XTRIM, key };
        cmd_params.emplace_back(keyword::MAXLEN);
        if (almost_exact)
            cmd_params.emplace_back(keyword::ALMOST_EXACT);
        cmd_params.emplace_back(std::to_string(threshold));
        send_command(cmd_params);
    }

//strings

    void append(cref_string key, cref_string value) override final
    {
        send_command({ command::APPEND, value });
    }

    void bitcount(cref_string key) override final
    {
        send_command({ command::BITCOUNT, key });
    }

    void bitcount(cref_string key, czint start, czint end) override final
    {
        send_command({ command::BITCOUNT, key,
            std::to_string(start), std::to_string(end) });
    }

    void bitfield(cref_string key, cref_string_array arguments) override final
    {
        err_arguments_number(arguments.empty(), command::BITFIELD);
        send_command({ command::BITFIELD, key }, arguments);
    }

    void bitfield_RO(cref_string key, cref_string_array arguments) override final
    {
        err_arguments_number(arguments.empty(), command::BITFIELD_RO);
        send_command({ command::BITFIELD_RO, key }, arguments);
    }

    void bitop(bit_operation operation, cref_string destkey,
        cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::BITOP);
        send_command({ command::BITOP, bit_operation_dict.at(operation),
            destkey }, keys);
    }

    void bitpos(cref_string key, czbit bit, const bitpos_param& param) override final
    {
        send_command({ command::BITPOS, key, std::to_string(bit) },
            param.to_string_array());
    }

    void decr(cref_string key) override final
    {
        send_command({ command::DECR, key });
    }

    void decrby(cref_string key, czint decrement) override final
    {
        send_command({ command::DECRBY, key, std::to_string(decrement) });
    }

    void get(cref_string key) override final
    {
        send_command({ command::GET, key });
    }

    void getbit(cref_string key, czint offset) override final
    {
        if (offset < 0)
            throw redis_commmand_error("ERR bit offset is not an integer or out of range");
        send_command({ command::GETBIT, key, std::to_string(offset) });
    }

    void getrange(cref_string key, czint start, czint end) override final
    {
        send_command({ command::GETRANGE, key,
            std::to_string(start), std::to_string(end) });
    }

    void getset(cref_string key, cref_string value) override final
    {
        send_command({ command::GETSET, key, value });
    }

    void incr(cref_string key) override final
    {
        send_command({ command::INCR, key });
    }

    void incrby(cref_string key, czint increment) override final
    {
        send_command({ command::INCRBY, key, std::to_string(increment) });
    }

    void incrbyfloat(cref_string key, double increment) override final
    {
        send_command({ command::INCRBYFLOAT, key, std::to_string(increment) });
    }

    void mget(cref_string_array keys) override final
    {
        err_arguments_number(keys.empty(), command::MGET);
        send_command({ command::MGET }, keys);
    }

    void mset(cref_string_array keys_values) override final
    {
        err_arguments_number(keys_values.empty() ||
            (keys_values.size() % 2 != 0), command::MSET);
        send_command({ command::MSET }, keys_values);
    }

    void msetnx(cref_string_array keys_values) override final
    {
        err_arguments_number(keys_values.empty() ||
            (keys_values.size() % 2 != 0), command::MSETNX);
        send_command({ command::MSETNX }, keys_values);
    }

    void psetex(cref_string key, czint milliseconds, cref_string value) override final
    {
        if (milliseconds <= 0)
            throw redis_commmand_error("ERR invalid expire time in psetex");
        send_command({ command::PSETEX, key, std::to_string(milliseconds), value });
    }

    void set(cref_string key, cref_string value) override final
    {
        send_command({ command::SET, key, value });
    }

    void set(cref_string key, cref_string value, const set_param& param) override final
    {
        send_command({ command::SET, key, value }, param.to_string_array());
    }

    void setbit(cref_string key, czint offset, czbit bit) override final
    {
        if (offset < 0)
            throw redis_commmand_error("ERR bit offset is not an integer or out of range");
        send_command({ command::SETBIT, key, std::to_string(offset),
            std::to_string(bit) });
    }

    void setex(cref_string key, czint seconds, cref_string value) override final
    {
        if (seconds <= 0)
            throw redis_commmand_error("ERR invalid expire time in setex");
        send_command({ command::SETEX, key, std::to_string(seconds), value });
    }

    void setnx(cref_string key, cref_string value) override final
    {
        send_command({ command::SETNX, key, value });
    }

    void setrange(cref_string key, czint offset, cref_string value) override final
    {
        if (offset < 0)
            throw redis_commmand_error("ERR offset is out of range");
        send_command({ command::SETRANGE, key, std::to_string(offset), value });
    }

    void strlen(cref_string key) override final
    {
        send_command({ command::STRLEN, key });
    }

//transactions

    void discard() override final
    {
        if (!is_in_multi())
            throw redis_commmand_error("ERR DISCARD without MULTI");

        send_command({ command::DISCARD });
        is_in_multi_ = false;
        is_in_watch_ = false;
    }

    void exec() override final
    {
        if (!is_in_multi())
            throw redis_commmand_error("ERR EXEC without MULTI");

        send_command({ command::EXEC });
        is_in_multi_ = false;
        is_in_watch_ = false;
    }

    void multi() override final
    {
        if (is_in_multi())
            throw redis_commmand_error("ERR MULTI calls can not be nested");

        send_command({ command::MULTI });
        is_in_multi_ = true;
    }

    void unwatch() override final
    {
        send_command({ command::UNWATCH });
        is_in_watch_ = false;
    }

    void watch(cref_string_array keys) override final
    {
        if (is_in_multi())
            throw redis_commmand_error("ERR WATCH inside MULTI is not allowed");
        err_arguments_number(keys.empty(), command::WATCH);
        send_command({ command::WATCH }, keys);
        is_in_watch_ = true;
    }
};

} // namespace detail
} // namespace czredis
