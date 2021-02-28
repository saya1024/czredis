#pragma once

#include "client.h"
#include "delay_queue.h"

namespace czredis
{
namespace detail
{

class delay_commands : public i_delay_commands
{
    virtual client& use_client() = 0;

public:

//geo

    delay<reply_array> georadius(cref_string key,
        double longitude, double latitude, double radius, geo_unit unit,
        const georadius_param& param = georadius_param(),
        const georadius_store_param& store_param = georadius_store_param()) override final
    {
        auto& c = use_client();
        c.georadius(key, longitude, latitude, radius, unit,
            param, store_param);
        return c.make_delay<reply_array>();
    }

    delay<reply_array> georadiusbymember(cref_string key,
        cref_string member, double radius, geo_unit unit,
        const georadius_param& param = georadius_param(),
        const georadius_store_param& store_param = georadius_store_param()) override final
    {
        auto& c = use_client();
        c.georadiusbymember(key, member, radius, unit,
            param, store_param);
        return c.make_delay<reply_array>();
    }

//hyper_log_log
    delay<czint> pfcount(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.pfcount(keys);
        return c.make_delay<czint>();
    }

    delay<czstring> pfmerge(cref_string destkey, cref_string_array sourcekeys) override final
    {
        auto& c = use_client();
        c.pfmerge(destkey, sourcekeys);
        return c.make_delay<czstring>();
    }

//keys
    delay<czint> del(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.del(keys);
        return c.make_delay<czint>();
    }

    delay<string_array> keys(cref_string pattern) override final
    {
        auto& c = use_client();
        c.keys(pattern);
        return c.make_delay<string_array>();
    }

    delay<czstring> migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param,
        cref_string_array keys) override final
    {
        auto& c = use_client();
        c.migrate(host, port, destination_db, timeout, param, keys);
        return c.make_delay<czstring>();
    }

    delay<string_array> object_help() override final
    {
        auto& c = use_client();
        c.object_help();
        return c.make_delay<string_array>();
    }

    delay<reply> randomkey() override final
    {
        auto& c = use_client();
        c.randomkey();
        return c.make_delay<reply>();
    }

    delay<czstring> rename(cref_string key, cref_string new_key) override final
    {
        auto& c = use_client();
        c.rename(key, new_key);
        return c.make_delay<czstring>();
    }

    delay<czint> renamenx(cref_string key, cref_string new_key) override final
    {
        auto& c = use_client();
        c.renamenx(key, new_key);
        return c.make_delay<czint>();
    }

    delay<scan_result> scan(cref_string cursor,
        const scan_param& param = scan_param()) override final
    {
        auto& c = use_client();
        c.scan(cursor, param);
        return c.make_delay<scan_result>();
    }

    delay<scan_result> scan(cref_string cursor,
        const scan_param& param, redis_key_type type) override final
    {
        auto& c = use_client();
        c.scan(cursor, param, type);
        return c.make_delay<scan_result>();
    }

    delay<czint> sort(cref_string key,
        const sort_param& param, cref_string destination) override final
    {
        auto& c = use_client();
        c.sort(key, param, destination);
        return c.make_delay<czint>();
    }

    delay<czint> touch(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.touch(keys);
        return c.make_delay<czint>();
    }

    delay<czint> unlink(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.unlink(keys);
        return c.make_delay<czint>();
    }

    delay<czint> wait(unsigned numreplicas, czint timeout) override final
    {
        auto& c = use_client();
        c.wait(numreplicas, timeout);
        return c.make_delay<czint>();
    }

//lists
    delay<reply> blpop(cref_string_array keys, czint timeout) override final
    {
        auto& c = use_client();
        c.blpop(keys, timeout);
        return c.make_delay<reply>();
    }

    delay<reply> brpop(cref_string_array keys, czint timeout) override final
    {
        auto& c = use_client();
        c.brpop(keys, timeout);
        return c.make_delay<reply>();
    }

    delay<reply> brpoplpush(cref_string source, cref_string destination,
        czint timeout) override final
    {
        auto& c = use_client();
        c.brpoplpush(source, destination, timeout);
        return c.make_delay<reply>();
    }

    delay<reply> rpoplpush(cref_string source, cref_string destination) override final
    {
        auto& c = use_client();
        c.rpoplpush(source, destination);
        return c.make_delay<reply>();
    }

//scripting

    delay<reply> eval(cref_string script,
        cref_string_array keys, cref_string_array args) override final
    {
        auto& c = use_client();
        c.eval(script, keys, args);
        return c.make_delay<reply>();
    }

    delay <reply> evalsha(cref_string sha1,
        cref_string_array keys, cref_string_array args) override final
    {
        auto& c = use_client();
        c.evalsha(sha1, keys, args);
        return c.make_delay<reply>();
    }

    delay<czint> script_exists(cref_string sha1) override final
    {
        auto& c = use_client();
        c.script_exists(sha1);
        return c.make_delay<czint>();
    }

    delay<std::vector<czint>> script_exists(cref_string_array sha1s) override final
    {
        auto& c = use_client();
        c.script_exists(sha1s);
        return c.make_delay<std::vector<czint>>();
    }

    delay<czstring> script_flush() override final
    {
        auto& c = use_client();
        c.script_flush();
        return c.make_delay<czstring>();
    }

    delay<czstring> script_kill() override final
    {
        auto& c = use_client();
        c.script_kill();
        return c.make_delay<czstring>();
    }

    delay<czstring> script_load(cref_string script) override final
    {
        auto& c = use_client();
        c.script_load(script);
        return c.make_delay<czstring>();
    }

//server

    delay<czstring> bgrewriteaof() override final
    {
        auto& c = use_client();
        c.bgrewriteaof();
        return c.make_delay<czstring>();
    }

    delay<czstring> bgsave(bool schedule) override final
    {
        auto& c = use_client();
        c.bgsave(schedule);
        return c.make_delay<czstring>();
    }

    delay<string_array> config_get(cref_string parameter)
    {
        auto& c = use_client();
        c.config_get(parameter);
        return c.make_delay<string_array>();
    }

    delay<czstring> config_resetstat() override final
    {
        auto& c = use_client();
        c.config_resetstat();
        return c.make_delay<czstring>();
    }

    delay<czstring> config_set(cref_string parameter, cref_string value) override final
    {
        auto& c = use_client();
        c.config_set(parameter, value);
        return c.make_delay<czstring>();
    }

    delay<czint> dbsize() override final
    {
        auto& c = use_client();
        c.dbsize();
        return c.make_delay<czint>();
    }

    delay<czstring> flushall(const flush_param& param) override final
    {
        auto& c = use_client();
        c.flushall(param);
        return c.make_delay<czstring>();
    }

    delay<czstring> flushdb(const flush_param& param) override final
    {
        auto& c = use_client();
        c.flushdb(param);
        return c.make_delay<czstring>();
    }

    delay<czstring> info() override final
    {
        auto& c = use_client();
        c.info();
        return c.make_delay<czstring>();
    }

    delay<czstring> info(cref_string section) override final
    {
        auto& c = use_client();
        c.info(section);
        return c.make_delay<czstring>();
    }

    delay<czint> lastsave() override final
    {
        auto& c = use_client();
        c.lastsave();
        return c.make_delay<czint>();
    }

    delay<czstring> memory_doctor() override final
    {
        auto& c = use_client();
        c.memory_doctor();
        return c.make_delay<czstring>();
    }

    delay<std::vector<module_result>> module_list() override final
    {
        auto& c = use_client();
        c.module_list();
        return c.make_delay<std::vector<module_result>>();
    }

    delay<czstring> module_load(cref_string path, cref_string_array args) override final
    {
        auto& c = use_client();
        c.module_load(path, args);
        return c.make_delay<czstring>();
    }

    delay<czstring> module_unload(cref_string name) override final
    {
        auto& c = use_client();
        c.module_unload(name);
        return c.make_delay<czstring>();
    }

    delay<czstring> replicaof(cref_string host, cref_string port) override final
    {
        auto& c = use_client();
        c.replicaof(host, port);
        return c.make_delay<czstring>();
    }

    delay<czstring> replicaof_no_one() override final
    {
        auto& c = use_client();
        c.replicaof_no_one();
        return c.make_delay<czstring>();
    }

    delay<czstring> save() override final
    {
        auto& c = use_client();
        c.save();
        return c.make_delay<czstring>();
    }

    delay<czstring> slaveof(cref_string host, cref_string port) override final
    {
        auto& c = use_client();
        c.slaveof(host, port);
        return c.make_delay<czstring>();
    }

    delay<czstring> slaveof_no_one() override final
    {
        auto& c = use_client();
        c.slaveof_no_one();
        return c.make_delay<czstring>();
    }

    delay<std::vector<slowlog_reslut>> slowlog_get() override final
    {
        auto& c = use_client();
        c.slowlog_get();
        return c.make_delay<std::vector<slowlog_reslut>>();
    }

    delay<std::vector<slowlog_reslut>> slowlog_get(czint entries) override final
    {
        auto& c = use_client();
        c.slowlog_get(entries);
        return c.make_delay<std::vector<slowlog_reslut>>();
    }

    delay<czint> slowlog_len() override final
    {
        auto& c = use_client();
        c.slowlog_len();
        return c.make_delay<czint>();
    }

    delay<czstring> slowlog_reset() override final
    {
        auto& c = use_client();
        c.slowlog_reset();
        return c.make_delay<czstring>();
    }

    delay<czstring> swapdb(unsigned index1, unsigned index2) override final
    {
        auto& c = use_client();
        c.swapdb(index1, index2);
        return c.make_delay<czstring>();
    }

    delay<unix_time_result> time() override final
    {
        auto& c = use_client();
        c.time();
        return c.make_delay<unix_time_result>();
    }

//sets
    delay<string_array> sdiff(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sdiff(keys);
        return c.make_delay<string_array>();
    }

    delay<czint> sdiffstore(cref_string destination, cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sdiffstore(destination, keys);
        return c.make_delay<czint>();
    }

    delay<string_array> sinter(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sinter(keys);
        return c.make_delay<string_array>();
    }

    delay<czint> sinterstore(cref_string destination, cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sinterstore(destination, keys);
        return c.make_delay<czint>();
    }

    delay<czint> smove(cref_string source, cref_string destination,
        cref_string member) override final
    {
        auto& c = use_client();
        c.smove(source, destination, member);
        return c.make_delay<czint>();
    }

    delay<string_array> sunion(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sunion(keys);
        return c.make_delay<string_array>();
    }

    delay<czint> sunionstore(cref_string destination,
        cref_string_array keys) override final
    {
        auto& c = use_client();
        c.sunionstore(destination, keys);
        return c.make_delay<czint>();
    }

//sorted_sets
    delay<reply> bzpopmax(cref_string_array keys, czint timeout) override final
    {
        auto& c = use_client();
        c.bzpopmax(keys, timeout);
        return c.make_delay<reply>();
    }

    delay<reply> bzpopmin(cref_string_array keys, czint timeout) override final
    {
        auto& c = use_client();
        c.bzpopmin(keys, timeout);
        return c.make_delay<reply>();
    }

    delay<czint> zinterstore(cref_string destination, cref_string_array keys,
        const zstore_param& param = zstore_param()) override final
    {
        auto& c = use_client();
        c.zinterstore(destination, keys, param);
        return c.make_delay<czint>();
    }

    delay<czint> zunionstore(cref_string destination, cref_string_array keys,
        const zstore_param& param = zstore_param()) override final
    {
        auto& c = use_client();
        c.zunionstore(destination, keys, param);
        return c.make_delay<czint>();
    }

//streams
    delay<string_array> xgroup_help() override final
    {
        auto& c = use_client();
        c.xgroup_help();
        return c.make_delay<string_array>();
    }

    delay<string_array> xinfo_help() override final
    {
        auto& c = use_client();
        c.xinfo_help();
        return c.make_delay<string_array>();
    }

    delay<hmap<czstring, stream_entries>> xread(const xread_param& param,
        cref_string_array keys, cref_stream_id_array ids) override final
    {
        auto& c = use_client();
        c.xread(param, keys, ids);
        return c.make_delay<hmap<czstring, stream_entries>>();
    }

    delay<hmap<czstring, stream_entries>> xreadgroup(
        cref_string group, cref_string consumer,
        const xread_param& param, bool noack,
        cref_string_array keys, cref_stream_id_array ids) override final
    {
        auto& c = use_client();
        c.xreadgroup(group, consumer, param, noack, keys, ids);
        return c.make_delay<hmap<czstring, stream_entries>>();
    }

//strings
    delay<czint> bitop(bit_operation operation,
        cref_string destkey, cref_string_array keys) override final
    {
        auto& c = use_client();
        c.bitop(operation, destkey, keys);
        return c.make_delay<czint>();
    }

    delay<reply_array> mget(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.mget(keys);
        return c.make_delay<reply_array>();
    }

    delay<czstring> mset(cref_string_array keys_values) override final
    {
        auto& c = use_client();
        c.mset(keys_values);
        return c.make_delay<czstring>();
    }

    delay<czint> msetnx(cref_string_array keys_values) override final
    {
        auto& c = use_client();
        c.msetnx(keys_values);
        return c.make_delay<czint>();
    }
};

} // namespace detail
} // namespace czredis