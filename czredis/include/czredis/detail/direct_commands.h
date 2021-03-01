#pragma once

#include "call_finally.h"
#include "client.h"

namespace czredis
{
namespace detail
{

class direct_commands : public i_direct_commands
{
    virtual client& use_client() = 0;

public:

//connection

    czstring auth(cref_string password) override final
    {
        auto& c = use_client();
        c.auth(password);
        return c.get_reply_as<czstring>();
    }

    czstring auth(cref_string username, cref_string password) override final
    {
        auto& c = use_client();
        c.auth(username, password);
        return c.get_reply_as<czstring>();
    }

    czstring echo(cref_string message) override final
    {
        auto& c = use_client();
        c.echo(message);
        return c.get_reply_as<czstring>();
    }

    czstring ping() override final
    {
        auto& c = use_client();
        c.ping();
        return c.get_reply_as<czstring>();
    }

    czstring quit() override final
    {
        auto& c = use_client();
        c.quit();
        auto ret = c.get_reply_as<czstring>();
        c.disconnect();
        return ret;
    }

    czstring select(unsigned index) override final
    {
        auto& c = use_client();
        c.select(index);
        return c.get_reply_as<czstring>();
    }

//geo

    reply_array georadius(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param,
        const georadius_store_param& store_param) override final
    {
        auto& c = use_client();
        c.georadius(key, longitude, latitude, radius,
            unit, param, store_param);
        return c.get_reply_as<reply_array>();
    }

    reply_array georadiusbymember(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param,
        const georadius_store_param& store_param) override final
    {
        auto& c = use_client();
        c.georadiusbymember(key, member, radius, unit,
            param, store_param);
        return c.get_reply_as<reply_array>();
    }

//hyper_log_log

    czint pfcount(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.pfcount(keys);
        return c.get_reply_as<czint>();
    }

    czstring pfmerge(cref_string destkey, cref_string_array sourcekeys) override final
    {
        auto& c = use_client();
        c.pfmerge(destkey, sourcekeys);
        return c.get_reply_as<czstring>();
    }

//keys

    czint del(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.del(keys);
        return c.get_reply_as<czint>();
    }

    string_array keys(cref_string pattern) override final
    {
        auto& c = use_client();
        c.keys(pattern);
        return c.get_reply_as<string_array>();
    }

    czstring migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param,
        cref_string_array keys) override final
    {
        auto& c = use_client();
        c.migrate(host, port, destination_db, timeout, param, keys);
        return c.get_reply_as<czstring>();
    }

    string_array object_help() override final
    {
        auto& c = use_client();
        c.object_help();
        return c.get_reply_as<string_array>();
    }

    reply randomkey() override final
    {
        auto& c = use_client();
        c.randomkey();
        return c.get_reply_as<reply>();
    }

    czstring rename(cref_string key,
        cref_string new_key) override final
    {
        auto& c = use_client();
        c.rename(key, new_key);
        return c.get_reply_as<czstring>();
    }

    czint renamenx(cref_string key,
        cref_string new_key) override final
    {
        auto& c = use_client();
        c.renamenx(key, new_key);
        return c.get_reply_as<czint>();
    }

    scan_result scan(cref_string cursor,
        const scan_param& param = scan_param()) override final
    {
        auto& c = use_client();
        c.scan(cursor, param);
        return c.get_reply_as<scan_result>();
    }

    scan_result scan(cref_string cursor,
        const scan_param& param, redis_key_type type) override final
    {
        auto& c = use_client();
        c.scan(cursor, param, type);
        return c.get_reply_as<scan_result>();
    }

    czint sort(cref_string key,
        const sort_param& param, cref_string destination) override final
    {
        auto& c = use_client();
        c.sort(key, param, destination);
        return c.get_reply_as<czint>();
    }

    czint touch(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.touch(keys);
        return c.get_reply_as<czint>();
    }

    czint unlink(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.unlink(keys);
        return c.get_reply_as<czint>();
    }

    czint wait(unsigned numreplicas, czint timeout) override final
    {
        auto& c = use_client();
        c.wait(numreplicas, timeout);
        return c.get_reply_as<czint>();
    }

//lists

    reply blpop(cref_string_array keys, czint timeout) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.blpop(keys, timeout);
        return c.get_reply_as<reply>();
    }

    reply brpop(cref_string_array keys, czint timeout) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.brpop(keys, timeout);
        return c.get_reply_as<reply>();
    }

    reply brpoplpush(cref_string source, cref_string destination,
        czint timeout) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.brpoplpush(source, destination, timeout);
        return c.get_reply_as<reply>();
    }

    reply rpoplpush(cref_string source, cref_string destination) override final
    {
        auto& c = use_client();
        c.rpoplpush(source, destination);
        return c.get_reply_as<reply>();
    }

//scripting

    reply eval(cref_string script, cref_string_array keys,
        cref_string_array args) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.eval(script, keys, args);
        return c.get_reply_as<reply>();
    }

    reply evalsha(cref_string sha1, cref_string_array keys,
        cref_string_array args) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.evalsha(sha1, keys, args);
        return c.get_reply_as<reply>();
    }

    czint script_exists(cref_string sha1) override final
    {
        auto& c = use_client();
        c.script_exists(sha1);
        return c.get_reply_as<czint>();
    }

    std::vector<czint> script_exists(cref_string_array sha1s) override final
    {
        auto& c = use_client();
        c.script_exists(sha1s);
        return c.get_reply_as<std::vector<czint>>();
    }

    czstring script_flush() override final
    {
        auto& c = use_client();
        c.script_flush();
        return c.get_reply_as<czstring>();
    }

    czstring script_kill() override final
    {
        auto& c = use_client();
        c.script_flush();
        return c.get_reply_as<czstring>();
    }

    czstring script_load(cref_string script) override final
    {
        auto& c = use_client();
        c.script_load(script);
        return c.get_reply_as<czstring>();
    }

//server

    czstring bgrewriteaof() override final
    {
        auto& c = use_client();
        c.bgrewriteaof();
        return c.get_reply_as<czstring>();
    }

    czstring bgsave(bool schedule = false) override final
    {
        auto& c = use_client();
        c.bgsave(schedule);
        return c.get_reply_as<czstring>();
    }

    string_array config_get(cref_string parameter)
    {
        auto& c = use_client();
        c.config_get(parameter);
        return c.get_reply_as<string_array>();
    }

    czstring config_resetstat() override final
    {
        auto& c = use_client();
        c.config_resetstat();
        return c.get_reply_as<czstring>();
    }

    czstring config_set(cref_string parameter, cref_string value) override final
    {
        auto& c = use_client();
        c.config_set(parameter, value);
        return c.get_reply_as<czstring>();
    }

    czint dbsize() override final
    {
        auto& c = use_client();
        c.dbsize();
        return c.get_reply_as<czint>();
    }

    czstring flushall(const flush_param& param = flush_param()) override final
    {
        auto& c = use_client();
        c.flushall(param);
        return c.get_reply_as<czstring>();
    }

    czstring flushdb(const flush_param& param = flush_param()) override final
    {
        auto& c = use_client();
        c.flushdb(param);
        return c.get_reply_as<czstring>();
    }

    czstring info() override final
    {
        auto& c = use_client();
        c.info();
        return c.get_reply_as<czstring>();
    }

    czstring info(cref_string section) override final
    {
        auto& c = use_client();
        c.info(section);
        return c.get_reply_as<czstring>();
    }

    czint lastsave() override final
    {
        auto& c = use_client();
        c.lastsave();
        return c.get_reply_as<czint>();
    }

    czstring memory_doctor() override final
    {
        auto& c = use_client();
        c.memory_doctor();
        return c.get_reply_as<czstring>();
    }

    std::vector<module_result> module_list() override final
    {
        auto& c = use_client();
        c.module_list();
        return c.get_reply_as<std::vector<module_result>>();
    }

    czstring module_load(cref_string path, cref_string_array args) override final
    {
        auto& c = use_client();
        c.module_load(path, args);
        return c.get_reply_as<czstring>();
    }

    czstring module_unload(cref_string name) override final
    {
        auto& c = use_client();
        c.module_unload(name);
        return c.get_reply_as<czstring>();
    }

    czstring replicaof(cref_string host, cref_string port) override final
    {
        auto& c = use_client();
        c.replicaof(host, port);
        return c.get_reply_as<czstring>();
    }

    czstring replicaof_no_one() override final
    {
        auto& c = use_client();
        c.replicaof_no_one();
        return c.get_reply_as<czstring>();
    }

    czstring save() override final
    {
        auto& c = use_client();
        c.save();
        return c.get_reply_as<czstring>();
    }

    void shutdown(const shutdown_param& param = shutdown_param()) override final
    {
        auto& c = use_client();
        c.shutdown(param);
        try
        {
            c.get_reply_as<reply>();
        }
        catch (const redis_io_error&)
        {
            c.disconnect();
        }
    }

    czstring slaveof(cref_string host, cref_string port) override final
    {
        auto& c = use_client();
        c.slaveof(host, port);
        return c.get_reply_as<czstring>();
    }

    czstring slaveof_no_one() override final
    {
        auto& c = use_client();
        c.slaveof_no_one();
        return c.get_reply_as<czstring>();
    }

    std::vector<slowlog_reslut> slowlog_get() override final
    {
        auto& c = use_client();
        c.slowlog_get();
        return c.get_reply_as<std::vector<slowlog_reslut>>();
    }

    std::vector<slowlog_reslut> slowlog_get(czint entries) override final
    {
        auto& c = use_client();
        c.slowlog_get(entries);
        return c.get_reply_as<std::vector<slowlog_reslut>>();
    }

    czint slowlog_len() override final
    {
        auto& c = use_client();
        c.slowlog_len();
        return c.get_reply_as<czint>();
    }

    czstring slowlog_reset() override final
    {
        auto& c = use_client();
        c.slowlog_reset();
        return c.get_reply_as<czstring>();
    }

    czstring swapdb(unsigned index1, unsigned index2) override final
    {
        auto& c = use_client();
        c.swapdb(index1, index2);
        return c.get_reply_as<czstring>();
    }

    unix_time_result time() override final
    {
        auto& c = use_client();
        c.time();
        return c.get_reply_as<unix_time_result>();
    }

//sets

    string_array sdiff(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sdiff(keys);
        return c.get_reply_as<string_array>();
    }

    czint sdiffstore(cref_string destination, cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sdiffstore(destination, keys);
        return c.get_reply_as<czint>();
    }

    string_array sinter(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sinter(keys);
        return c.get_reply_as<string_array>();
    }

    czint sinterstore(cref_string destination, cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sinterstore(destination, keys);
        return c.get_reply_as<czint>();
    }

    czint smove(cref_string source, cref_string destination,
        cref_string member) override final
    {
        auto& c = use_client();
        c.smove(source, destination, member);
        return c.get_reply_as<czint>();
    }

    string_array sunion(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sunion(keys);
        return c.get_reply_as<string_array>();
    }

    czint sunionstore(cref_string destination, cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sunionstore(destination, keys);
        return c.get_reply_as<czint>();
    }

//sorted_sets

    reply bzpopmax(cref_string_array keys, czint timeout) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.bzpopmax(keys, timeout);
        return c.get_reply_as<reply>();
    }

    reply bzpopmin(cref_string_array keys, czint timeout) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        c.set_read_timeout(0);
        c.bzpopmin(keys, timeout);
        return c.get_reply_as<reply>();
    }

    czint zinterstore(cref_string destination, cref_string_array keys,
        const zstore_param& param = zstore_param()) override final
    {
        auto& c = use_client();
        c.zinterstore(destination, keys, param);
        return c.get_reply_as<czint>();
    }

    czint zunionstore(cref_string destination, cref_string_array keys,
        const zstore_param& param = zstore_param()) override final
    {
        auto& c = use_client();
        c.zunionstore(destination, keys, param);
        return c.get_reply_as<czint>();
    }

//streams

    string_array xgroup_help() override final
    {
        auto& c = use_client();
        c.xgroup_help();
        return c.get_reply_as<string_array>();
    }

    string_array xinfo_help() override final
    {
        auto& c = use_client();
        c.xinfo_help();
        return c.get_reply_as<string_array>();
    }

    tmap<czstring, stream_entries> xread(const xread_param& param,
        cref_string_array keys, cref_stream_id_array ids) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        if (param.is_block())
            c.set_read_timeout(0);
        c.xread(param, keys, ids);
        return c.get_reply_as<tmap<czstring, stream_entries>>();
    }

    tmap<czstring, stream_entries> xreadgroup(cref_string group,
        cref_string consumer, const xread_param& param, bool noack,
        cref_string_array keys, cref_stream_id_array ids) override final
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        if (param.is_block())
            c.set_read_timeout(0);
        c.xreadgroup(group, consumer, param, noack, keys, ids);
        return c.get_reply_as<tmap<czstring, stream_entries>>();
    }

//string

    czint bitop(bit_operation op,
        cref_string dest_key, cref_string_array keys) override final
    {
        auto& c = use_client();
        c.bitop(op, dest_key, keys);
        return c.get_reply_as<czint>();
    }

    reply_array mget(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.mget(keys);
        return c.get_reply_as<reply_array>();
    }

    czstring mset(cref_string_array keys_values) override final
    {
        auto& c = use_client();
        c.mset(keys_values);
        return c.get_reply_as<czstring>();
    }

    czint msetnx(cref_string_array keys_values) override final
    {
        auto& c = use_client();
        c.msetnx(keys_values);
        return c.get_reply_as<czint>();
    }
};

} // namespace detail
} // namespace czredis