#pragma once

namespace czredis
{
namespace detail
{

struct i_server
{
    virtual void bgrewriteaof() = 0;
    virtual void bgsave(bool schedule) = 0;
    virtual void config_get(cref_string parameter) = 0;
    virtual void config_resetstat() = 0;
    virtual void config_set(cref_string parameter, cref_string value) = 0;
    virtual void dbsize() = 0;
    virtual void flushall(const flush_param& param) = 0;
    virtual void flushdb(const flush_param& param) = 0;
    virtual void info() = 0;
    virtual void info(cref_string section) = 0;
    virtual void lastsave() = 0;
    virtual void memory_doctor() = 0;
    virtual void memory_usage(cref_string key) = 0;
    virtual void memory_usage(cref_string key, czint samples) = 0;
    virtual void module_list() = 0;
    virtual void module_load(cref_string path, cref_string_array args) = 0;
    virtual void module_unload(cref_string name) = 0;
    virtual void replicaof(cref_string host, cref_string port) = 0;
    virtual void replicaof_no_one() = 0;
    virtual void save() = 0;
    virtual void shutdown() = 0;
    virtual void slaveof(cref_string host, cref_string port) = 0;
    virtual void slaveof_no_one() = 0;
    virtual void slowlog_get() = 0;
    virtual void slowlog_get(czint entries) = 0;
    virtual void slowlog_len() = 0;
    virtual void slowlog_reset() = 0;
    virtual void swapdb(unsigned index1, unsigned index2) = 0;
    virtual void time() = 0;
};

struct i_one_key_direct_server
{
    virtual czint memory_usage(cref_string key) = 0;
    virtual czint memory_usage(cref_string key, czint samples) = 0;
};

struct i_direct_server
{
    virtual czstring bgrewriteaof() = 0;
    virtual czstring bgsave(bool schedule) = 0;
    virtual string_array config_get(cref_string parameter) = 0;
    virtual czstring config_resetstat() = 0;
    virtual czstring config_set(cref_string parameter, cref_string value) = 0;
    virtual czint dbsize() = 0;
    virtual czstring flushall(const flush_param& param) = 0;
    virtual czstring flushdb(const flush_param& param) = 0;
    virtual czstring info() = 0;
    virtual czstring info(cref_string section) = 0;
    virtual czint lastsave() = 0;
    virtual czstring memory_doctor() = 0;
    virtual std::vector<module_result> module_list() = 0;
    virtual czstring module_load(cref_string path, cref_string_array args) = 0;
    virtual czstring module_unload(cref_string name) = 0;
    virtual czstring replicaof(cref_string host, cref_string port) = 0;
    virtual czstring replicaof_no_one() = 0;
    virtual czstring save() = 0;
    virtual void shutdown() = 0;
    virtual czstring slaveof(cref_string host, cref_string port) = 0;
    virtual czstring slaveof_no_one() = 0;
    virtual std::vector<slowlog_reslut> slowlog_get() = 0;
    virtual std::vector<slowlog_reslut> slowlog_get(czint entries) = 0;
    virtual czint slowlog_len() = 0;
    virtual czstring slowlog_reset() = 0;
    virtual czstring swapdb(unsigned index1, unsigned index2) = 0;
    virtual unix_time_result time() = 0;
};

struct i_one_key_delay_server
{
    virtual delay<czint> memory_usage(cref_string key) = 0;
    virtual delay<czint> memory_usage(cref_string key, czint samples) = 0;
};

struct i_delay_server
{
    virtual delay<czstring> bgrewriteaof() = 0;
    virtual delay<czstring> bgsave(bool schedule) = 0;
    virtual delay<string_array> config_get(cref_string parameter) = 0;
    virtual delay<czstring> config_resetstat() = 0;
    virtual delay<czstring> config_set(cref_string parameter, cref_string value) = 0;
    virtual delay<czint> dbsize() = 0;
    virtual delay<czstring> flushall(const flush_param& param) = 0;
    virtual delay<czstring> flushdb(const flush_param& param) = 0;
    virtual delay<czstring> info() = 0;
    virtual delay<czstring> info(cref_string section) = 0;
    virtual delay<czint> lastsave() = 0;
    virtual delay<czstring> memory_doctor() = 0;
    virtual delay<std::vector<module_result>> module_list() = 0;
    virtual delay<czstring> module_load(cref_string path, cref_string_array args) = 0;
    virtual delay<czstring> module_unload(cref_string name) = 0;
    virtual delay<czstring> replicaof(cref_string host, cref_string port) = 0;
    virtual delay<czstring> replicaof_no_one() = 0;
    virtual delay<czstring> save() = 0;
    virtual delay<czstring> slaveof(cref_string host, cref_string port) = 0;
    virtual delay<czstring> slaveof_no_one() = 0;
    virtual delay<std::vector<slowlog_reslut>> slowlog_get() = 0;
    virtual delay<std::vector<slowlog_reslut>> slowlog_get(czint entries) = 0;
    virtual delay<czint> slowlog_len() = 0;
    virtual delay<czstring> slowlog_reset() = 0;
    virtual delay<czstring> swapdb(unsigned index1, unsigned index2) = 0;
    virtual delay<unix_time_result> time() = 0;
};

} // namespace detail
} // namespace czredis