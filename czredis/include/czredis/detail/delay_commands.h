#pragma once

#include "client.h"
#include "delay_queue.h"

namespace czredis
{
namespace detail
{

class delay_commands :
    virtual public delay_queue,
    public i_delay_commands
{
    virtual client& use_client() = 0;

public:

    delay<reply> send_command(cref_string cmd, cref_string_array args)
    {
        use_client().send_command({ cmd }, args);
        return make_delay<reply>();
    }

//geo

    delay<reply_array> georadius(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param = georadius_param(),
        const georadius_store_param& store_param = georadius_store_param()) override final
    {
        use_client().georadius(key, longitude, latitude, radius, unit,
            param, store_param);
        return make_delay<reply_array>();
    }

    delay<reply_array> georadiusbymember(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param = georadius_param(),
        const georadius_store_param& store_param = georadius_store_param()) override final
    {
        use_client().georadiusbymember(key, member, radius, unit,
            param, store_param);
        return make_delay<reply_array>();
    }

//hyper_log_log
    delay<czint> pfcount(cref_string_array keys) override final
    {
        use_client().pfcount(keys);
        return make_delay<czint>();
    }

    delay<czstring> pfmerge(cref_string destkey, cref_string_array sourcekeys) override final
    {
        use_client().pfmerge(destkey, sourcekeys);
        return make_delay<czstring>();
    }

//keys
    delay<czint> del(cref_string_array keys) override final
    {
        use_client().del(keys);
        return make_delay<czint>();
    }

    delay<string_array> keys(cref_string pattern) override final
    {
        use_client().keys(pattern);
        return make_delay<string_array>();
    }

    delay<czstring> migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param,
        cref_string_array keys) override final
    {
        use_client().migrate(host, port, destination_db, timeout, param, keys);
        return make_delay<czstring>();
    }

    delay<string_array> object_help() override final
    {
        use_client().object_help();
        return make_delay<string_array>();
    }

    delay<reply> randomkey() override final
    {
        use_client().randomkey();
        return make_delay<reply>();
    }

    delay<czstring> rename(cref_string key, cref_string new_key) override final
    {
        use_client().rename(key, new_key);
        return make_delay<czstring>();
    }

    delay<czint> renamenx(cref_string key, cref_string new_key) override final
    {
        use_client().renamenx(key, new_key);
        return make_delay<czint>();
    }

    delay<scan_result> scan(cref_string cursor,
        const scan_param& param = scan_param()) override final
    {
        use_client().scan(cursor, param);
        return make_delay<scan_result>();
    }

    delay<scan_result> scan(cref_string cursor,
        const scan_param& param, redis_key_type type) override final
    {
        use_client().scan(cursor, param, type);
        return make_delay<scan_result>();
    }

    delay<czint> sort(cref_string key,
        const sort_param& param, cref_string destination) override final
    {
        use_client().sort(key, param, destination);
        return make_delay<czint>();
    }

    delay<czint> touch(cref_string_array keys) override final
    {
        use_client().touch(keys);
        return make_delay<czint>();
    }

    delay<czint> unlink(cref_string_array keys) override final
    {
        use_client().unlink(keys);
        return make_delay<czint>();
    }

    delay<czint> wait(unsigned numreplicas, czint timeout) override final
    {
        use_client().wait(numreplicas, timeout);
        return make_delay<czint>();
    }

//lists
    delay<reply> blpop(cref_string_array keys, czint timeout) override final
    {
        use_client().blpop(keys, timeout);
        return make_delay<reply>();
    }

    delay<reply> brpop(cref_string_array keys, czint timeout) override final
    {
        use_client().brpop(keys, timeout);
        return make_delay<reply>();
    }

    delay<reply> brpoplpush(cref_string source, cref_string destination,
        czint timeout) override final
    {
        use_client().brpoplpush(source, destination, timeout);
        return make_delay<reply>();
    }

    delay<reply> rpoplpush(cref_string source, cref_string destination) override final
    {
        use_client().rpoplpush(source, destination);
        return make_delay<reply>();
    }

//scripting

    delay<reply> eval(cref_string script,
        cref_string_array keys, cref_string_array args) override final
    {
        use_client().eval(script, keys, args);
        return make_delay<reply>();
    }

    delay <reply> evalsha(cref_string sha1,
        cref_string_array keys, cref_string_array args) override final
    {
        use_client().evalsha(sha1, keys, args);
        return make_delay<reply>();
    }

    delay<czint> script_exists(cref_string sha1) override final
    {
        use_client().script_exists(sha1);
        return make_delay<czint>();
    }

    delay<std::vector<czint>> script_exists(cref_string_array sha1s) override final
    {
        use_client().script_exists(sha1s);
        return make_delay<std::vector<czint>>();
    }

    delay<czstring> script_flush() override final
    {
        use_client().script_flush();
        return make_delay<czstring>();
    }

    delay<czstring> script_kill() override final
    {
        use_client().script_kill();
        return make_delay<czstring>();
    }

    delay<czstring> script_load(cref_string script) override final
    {
        use_client().script_load(script);
        return make_delay<czstring>();
    }

//sets
    delay<string_array> sdiff(cref_string_array keys) override final
    {
        use_client().sdiff(keys);
        return make_delay<string_array>();
    }

    delay<czint> sdiffstore(cref_string destination, cref_string_array keys) override final
    {
        use_client().sdiffstore(destination, keys);
        return make_delay<czint>();
    }

    delay<string_array> sinter(cref_string_array keys) override final
    {
        use_client().sinter(keys);
        return make_delay<string_array>();
    }

    delay<czint> sinterstore(cref_string destination, cref_string_array keys) override final
    {
        use_client().sinterstore(destination, keys);
        return make_delay<czint>();
    }

    delay<czint> smove(cref_string source, cref_string destination,
        cref_string member) override final
    {
        use_client().smove(source, destination, member);
        return make_delay<czint>();
    }

    delay<string_array> sunion(cref_string_array keys) override final
    {
        use_client().sunion(keys);
        return make_delay<string_array>();
    }

    delay<czint> sunionstore(cref_string destination,
        cref_string_array keys) override final
    {
        use_client().sunionstore(destination, keys);
        return make_delay<czint>();
    }

//sorted_sets
    delay<reply> bzpopmax(cref_string_array keys, czint timeout) override final
    {
        use_client().bzpopmax(keys, timeout);
        return make_delay<reply>();
    }

    delay<reply> bzpopmin(cref_string_array keys, czint timeout) override final
    {
        use_client().bzpopmin(keys, timeout);
        return make_delay<reply>();
    }

    delay<czint> zinterstore(cref_string destination,
        cref_string_array keys, const z_param& param = z_param()) override final
    {
        use_client().zinterstore(destination, keys, param);
        return make_delay<czint>();
    }

    delay<czint> zunionstore(cref_string destination,
        cref_string_array keys, const z_param& param = z_param()) override final
    {
        use_client().zunionstore(destination, keys, param);
        return make_delay<czint>();
    }

//streams
    delay<string_array> xgroup_help() override final
    {
        use_client().xgroup_help();
        return make_delay<string_array>();
    }

    delay<string_array> xinfo_help() override final
    {
        use_client().xinfo_help();
        return make_delay<string_array>();
    }

    delay<hmap<czstring, stream_entries>> xread(const xread_param& param,
        cref_string_array keys, cref_stream_id_array ids) override final
    {
        use_client().xread(param, keys, ids);
        return make_delay<hmap<czstring, stream_entries>>();
    }

    delay<hmap<czstring, stream_entries>> xreadgroup(
        cref_string group, cref_string consumer,
        const xread_param& param, bool noack,
        cref_string_array keys, cref_stream_id_array ids) override final
    {
        use_client().xreadgroup(group, consumer, param, noack, keys, ids);
        return make_delay<hmap<czstring, stream_entries>>();
    }

//strings
    delay<czint> bitop(bit_operation operation,
        cref_string destkey, cref_string_array keys) override final
    {
        use_client().bitop(operation, destkey, keys);
        return make_delay<czint>();
    }

    delay<reply_array> mget(cref_string_array keys) override final
    {
        use_client().mget(keys);
        return make_delay<reply_array>();
    }

    delay<czstring> mset(cref_string_hmap keys_valus) override final
    {
        use_client().mset(keys_valus);
        return make_delay<czstring>();
    }

    delay<czint> msetnx(cref_string_hmap keys_valus) override final
    {
        use_client().msetnx(keys_valus);
        return make_delay<czint>();
    }
};

} // namespace detail
} // namespace czredis