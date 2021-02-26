#pragma once

namespace czredis
{
namespace detail
{

struct i_streams
{
    virtual void xack(cref_string key, cref_string group, cref_stream_id_array ids) = 0;
    virtual void xadd(cref_string key, const xadd_param param, cref_string id,
        cref_string_array fields_values) = 0;
    virtual void xclaim(cref_string key, cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids, const xclaim_param& param) = 0;
    virtual void xdel(cref_string key, cref_stream_id_array ids) = 0;
    virtual void xgroup_create(cref_string key, cref_string groupname, cref_string id, bool mkstream) = 0;
    virtual void xgroup_delconsumer(cref_string key, cref_string groupname, cref_string consumername) = 0;
    virtual void xgroup_destroy(cref_string key, cref_string groupname) = 0;
    virtual void xgroup_setid(cref_string key, cref_string groupname, cref_string id) = 0;
    virtual void xgroup_help() = 0;
    virtual void xinfo_consumers(cref_string key, cref_string groupname) = 0;
    virtual void xinfo_groups(cref_string key) = 0;
    virtual void xinfo_stream(cref_string key) = 0;
    virtual void xinfo_help() = 0;
    virtual void xlen(cref_string key) = 0;
    virtual void xpending(cref_string key, cref_string group) = 0;
    virtual void xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count) = 0;
    virtual void xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count, cref_string consumer) = 0;
    virtual void xrange(cref_string key, cref_string start, cref_string end) = 0;
    virtual void xrange(cref_string key, cref_string start, cref_string end, czint count) = 0;
    virtual void xread(const xread_param& param, cref_string key, cref_stream_id id) = 0;
    virtual void xread(const xread_param& param, cref_string_array keys, cref_stream_id_array ids) = 0;
    virtual void xreadgroup(cref_string group, cref_string consumer, const xread_param& param,
        bool noack, cref_string key, cref_stream_id id) = 0;
    virtual void xreadgroup(cref_string group, cref_string consumer, const xread_param& param,
        bool noack, cref_string_array keys, cref_stream_id_array ids) = 0;
    virtual void xrevrange(cref_string key, cref_string end, cref_string start) = 0;
    virtual void xrevrange(cref_string key, cref_string end, cref_string start, czint count) = 0;
    virtual void xtrim(cref_string key, czint threshold, bool almost_exact = false) = 0;
};

struct i_one_key_direct_streams
{
    virtual czint xack(cref_string key, cref_string group, cref_stream_id_array ids) = 0;
    virtual stream_id xadd(cref_string key, const xadd_param param, cref_string id,
        cref_string_array fields_values) = 0;
    virtual stream_entries xclaim(cref_string key, cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids, const xclaim_param& param) = 0;
    virtual czint xdel(cref_string key, cref_stream_id_array ids) = 0;
    virtual czstring xgroup_create(cref_string key, cref_string groupname, cref_string id, bool mkstream) = 0;
    virtual czint xgroup_delconsumer(cref_string key, cref_string groupname, cref_string consumername) = 0;
    virtual czint xgroup_destroy(cref_string key, cref_string groupname) = 0;
    virtual czstring xgroup_setid(cref_string key, cref_string groupname, cref_string id) = 0;
    virtual std::vector<stream_consumer_info> xinfo_consumers(cref_string key, cref_string groupname) = 0;
    virtual std::vector<stream_group_info> xinfo_groups(cref_string key) = 0;
    virtual stream_info xinfo_stream(cref_string key) = 0;
    virtual czint xlen(cref_string key) = 0;
    virtual xpending_overall_result xpending(cref_string key, cref_string group) = 0;
    virtual std::vector<xpending_result> xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count) = 0;
    virtual std::vector<xpending_result> xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count, cref_string consumer) = 0;
    virtual stream_entries xrange(cref_string key, cref_string start, cref_string end) = 0;
    virtual stream_entries xrange(cref_string key, cref_string start, cref_string end, czint count) = 0;
    virtual std::pair<czstring, stream_entries> xread(const xread_param& param,
        cref_string key, cref_stream_id id) = 0;
    virtual std::pair<czstring, stream_entries> xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string key, cref_stream_id id) = 0;
    virtual stream_entries xrevrange(cref_string key, cref_string end, cref_string start) = 0;
    virtual stream_entries xrevrange(cref_string key, cref_string end, cref_string start, czint count) = 0;
    virtual czint xtrim(cref_string key, czint threshold, bool almost_exact = false) = 0;
};

struct i_direct_streams
{
    virtual string_array xgroup_help() = 0;
    virtual string_array xinfo_help() = 0;
    virtual hmap<czstring, stream_entries> xread(const xread_param& param,
        cref_string_array keys, cref_stream_id_array ids) = 0;
    virtual hmap<czstring, stream_entries> xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string_array keys, cref_stream_id_array ids) = 0;
};

struct i_one_key_delay_streams
{
    virtual delay<czint> xack(cref_string key, cref_string group, cref_stream_id_array ids) = 0;
    virtual delay<stream_id> xadd(cref_string key, const xadd_param param, cref_string id,
        cref_string_array fields_values) = 0;
    virtual delay<stream_entries> xclaim(cref_string key, cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids, const xclaim_param& param) = 0;
    virtual delay<czint> xdel(cref_string key, cref_stream_id_array ids) = 0;
    virtual delay<czstring> xgroup_create(cref_string key, cref_string groupname, cref_string id, bool mkstream) = 0;
    virtual delay<czint> xgroup_delconsumer(cref_string key, cref_string groupname, cref_string consumername) = 0;
    virtual delay<czint> xgroup_destroy(cref_string key, cref_string groupname) = 0;
    virtual delay<czstring> xgroup_setid(cref_string key, cref_string groupname, cref_string id) = 0;
    virtual delay<std::vector<stream_consumer_info>> xinfo_consumers(cref_string key, cref_string groupname) = 0;
    virtual delay<std::vector<stream_group_info>> xinfo_groups(cref_string key) = 0;
    virtual delay<stream_info> xinfo_stream(cref_string key) = 0;
    virtual delay<czint> xlen(cref_string key) = 0;
    virtual delay<xpending_overall_result> xpending(cref_string key, cref_string group) = 0;
    virtual delay<std::vector<xpending_result>> xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count) = 0;
    virtual delay<std::vector<xpending_result>> xpending(cref_string key, cref_string group,
        cref_string start, cref_string end, czint count, cref_string consumer) = 0;
    virtual delay<stream_entries> xrange(cref_string key, cref_string start, cref_string end) = 0;
    virtual delay<stream_entries> xrange(cref_string key, cref_string start, cref_string end, czint count) = 0;
    virtual delay<std::pair<czstring, stream_entries>> xread(const xread_param& param,
        cref_string key, cref_stream_id id) = 0;
    virtual delay<std::pair<czstring, stream_entries>> xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string key, cref_stream_id id) = 0;
    virtual delay<stream_entries> xrevrange(cref_string key, cref_string end, cref_string start) = 0;
    virtual delay<stream_entries> xrevrange(cref_string key, cref_string end, cref_string start, czint count) = 0;
    virtual delay<czint> xtrim(cref_string key, czint threshold, bool almost_exact = false) = 0;

};

struct i_delay_streams
{
    virtual delay<string_array> xgroup_help() = 0;
    virtual delay<string_array> xinfo_help() = 0;
    virtual delay<hmap<czstring, stream_entries>> xread(const xread_param& param,
        cref_string_array keys, cref_stream_id_array ids) = 0;
    virtual delay<hmap<czstring, stream_entries>> xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string_array keys, cref_stream_id_array ids) = 0;
};

} // namespace detail
} // namespace czredis

