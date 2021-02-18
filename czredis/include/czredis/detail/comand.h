#pragma once

#include "../common.h"

namespace czredis
{
namespace detail
{

namespace cmd
{

using command = const czstring;

namespace connection
{
command AUTH        = "AUTH";
command ECHO        = "ECHO";
command PING        = "PING";
command QUIT        = "QUIT";
command SELECT      = "SELECT";
}

struct interface_connection
{
    virtual void auth(cref_string password) = 0;
    virtual void auth(cref_string username, cref_string password) = 0;
    virtual void echo(cref_string message) = 0;
    virtual void ping() = 0;
    virtual void quit() = 0;
    virtual void select(unsigned index) = 0;
};

namespace geo
{
command GEOADD      = "GEOADD";
command GEODIST     = "GEODIST";
command GEOHASH     = "GEOHASH";
command GEOPOS      = "GEOPOS";
command GEORADIUS   = "GEORADIUS";
command GEORADIUS_RO = "GEORADIUS_RO";
command GEORADIUSBYMEMBER = "GEORADIUSBYMEMBER";
command GEORADIUSBYMEMBER_RO = "GEORADIUSBYMEMBER_RO";
}

struct interface_geo
{
    virtual void geoadd(cref_string key, double longitude, double latitude, cref_string member) = 0;
    virtual void geoadd(cref_string key, std::map<czstring, geo_coordinate> member_coordinate_map) = 0;
    virtual void geodist(cref_string key, cref_string member1, cref_string member2, geo_unit unit) = 0;
    virtual void geohash(cref_string key, cref_string_array members) = 0;
    virtual void geopos(cref_string key, cref_string_array members) = 0;
    virtual void georadius(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param, const georadius_store_param& store_param) = 0;
    virtual void georadius_RO(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param) = 0;
    virtual void georadiusbymember(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param, const georadius_store_param& store_param) = 0;
    virtual void georadiusbymember_RO(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param) = 0;
};

namespace hashes
{
command HDEL        = "HDEL";
command HEXISTS     = "HEXISTS";
command HGET        = "HGET";
command HGETALL     = "HGETALL";
command HINCRBY     = "HINCRBY";
command HINCRBYFLOAT = "HINCRBYFLOAT";
command HKEYS       = "HKEYS";
command HLEN        = "HLEN";
command HMGET       = "HMGET";
command HMSET       = "HMSET";
command HSCAN       = "HSCAN";
command HSET        = "HSET";
command HSETNX      = "HSETNX";
command HSTRLEN     = "HSTRLEN";
command HVALS       = "HVALS";
}

struct interface_hashes
{
    virtual void hdel(cref_string key, cref_string_array fields) = 0;
    virtual void hexists(cref_string key, cref_string field) = 0;
    virtual void hget(cref_string key, cref_string field) = 0;
    virtual void hgetall(cref_string key) = 0;
    virtual void hincrby(cref_string key, cref_string field, czint increment) = 0;
    virtual void hincrbyfloat(cref_string key, cref_string field, double increment) = 0;
    virtual void hkeys(cref_string key) = 0;
    virtual void hlen(cref_string key) = 0;
    virtual void hmget(cref_string key, cref_string_array fields) = 0;
    virtual void hmset(cref_string key, cref_string_map field_value_map) = 0;
    virtual void hscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual void hset(cref_string key, cref_string field, cref_string value) = 0;
    virtual void hsetnx(cref_string key, cref_string field, cref_string value) = 0;
    virtual void hstrlen(cref_string key, cref_string field) = 0;
    virtual void hvals(cref_string key) = 0;
};

namespace hyper_log_log
{
command PFADD       = "PFADD";
command PFCOUNT     = "PFCOUNT";
command PFMERGE     = "PFMERGE";
}

struct interface_hyper_log_log
{
    virtual void pfadd(cref_string key, cref_string_array elements) = 0;
    virtual void pfcount(cref_string_array keys) = 0;
    virtual void pfmerge(cref_string destkey, cref_string_array sourcekeys) = 0;
};

namespace keys
{
command DEL         = "DEL";
command DUMP        = "DUMP";
command EXISTS      = "EXISTS";
command EXPIRE      = "EXPIRE";
command EXPIREAT    = "EXPIREAT";
command KEYS        = "KEYS";
command MIGRATE     = "MIGRATE";
command MOVE        = "MOVE";
command OBJECT      = "OBJECT";
command PERSIST     = "PERSIST";
command PEXPIRE     = "PEXPIRE";
command PEXPIREAT   = "PEXPIREAT";
command PTTL        = "PTTL";
command RANDOMKEY   = "RANDOMKEY";
command RENAME      = "RENAME";
command RENAMENX    = "RENAMENX";
command RESTORE     = "RESTORE";
command SCAN        = "SCAN";
command SORT        = "SORT";
command TOUCH       = "TOUCH";
command TTL         = "TTL";
command TYPE        = "TYPE";
command UNLINK      = "UNLINK";
command WAIT        = "WAIT";
}

struct interface_keys
{
    virtual void del(cref_string_array keys) = 0;
    virtual void dump(cref_string key) = 0;
    virtual void exists(cref_string key) = 0;
    virtual void expire(cref_string key, czint seconds) = 0;
    virtual void expireat(cref_string key, czint timestamp) = 0;
    virtual void keys(cref_string pattern) = 0;
    virtual void migrate(cref_string host, cref_string port, cref_string key,
        unsigned destination_db, czint timeout, const migrate_param& param) = 0;
    virtual void migrate(cref_string host, cref_string port,
        unsigned destination_db, czint timeout, const migrate_param& param,
        cref_string_array keys) = 0;
    virtual void move(cref_string key, unsigned db) = 0;
    virtual void object_refcount(cref_string key) = 0;
    virtual void object_encoding(cref_string key) = 0;
    virtual void object_idletime(cref_string key) = 0;
    virtual void object_freq(cref_string key) = 0;
    virtual void object_help() = 0;
    virtual void persist(cref_string key) = 0;
    virtual void pexpire(cref_string key, czint milliseconds) = 0;
    virtual void pexpireat(cref_string key, czint milliseconds_timestamp) = 0;
    virtual void pttl(cref_string key) = 0;
    virtual void randomkey() = 0;
    virtual void rename(cref_string key, cref_string new_key) = 0;
    virtual void renamenx(cref_string key, cref_string new_key) = 0;
    virtual void restore(cref_string key, czint ttl,
        cref_string serialized_value, const restore_param& param) = 0;
    virtual void scan(cref_string cursor, const scan_param& param) = 0;
    virtual void scan(cref_string cursor, const scan_param& param, redis_key_type type) = 0;
    virtual void sort(cref_string key, const sort_param& param) = 0;
    virtual void touch(cref_string_array keys) = 0;
    virtual void ttl(cref_string key) = 0;
    virtual void type(cref_string key) = 0;
    virtual void unlink(cref_string_array keys) = 0;
    virtual void wait(unsigned numreplicas, czint timeout) = 0;
};

namespace lists
{
command BLPOP       = "BLPOP";
command BRPOP       = "BRPOP";
command BRPOPLPUSH  = "BRPOPLPUSH";
command LINDEX      = "LINDEX";
command LINSERT     = "LINSERT";
command LLEN        = "LLEN";
command LPOP        = "LPOP";
command LPUSH       = "LPUSH";
command LPUSHX      = "LPUSHX";
command LRANGE      = "LRANGE";
command LREM        = "LREM";
command LSET        = "LSET";
command LTRIM       = "LTRIM";
command RPOP        = "RPOP";
command RPOPLPUSH   = "RPOPLPUSH";
command RPUSH       = "RPUSH";
command RPUSHX      = "RPUSHX";
}

struct interface_lists
{
    virtual void blpop(cref_string_array keys, czint timeout) = 0;
    virtual void brpop(cref_string_array keys, czint timeout) = 0;
    virtual void brpoplpush(cref_string source, cref_string destination, czint timeout) = 0;
    virtual void lindex(cref_string key, czint index) = 0;
    virtual void linsert(cref_string key, insert_place place,
        cref_string pivot, cref_string value) = 0;
    virtual void llen(cref_string key) = 0;
    virtual void lpop(cref_string key) = 0;
    virtual void lpush(cref_string key, cref_string_array elements) = 0;
    virtual void lpushx(cref_string key, cref_string_array elements) = 0;
    virtual void lrange(cref_string key, czint start, czint stop) = 0;
    virtual void lrem(cref_string key, czint count, cref_string element) = 0;
    virtual void lset(cref_string key, czint index, cref_string element) = 0;
    virtual void ltrim(cref_string key, czint start, czint stop) = 0;
    virtual void rpop(cref_string key) = 0;
    virtual void rpoplpush(cref_string source, cref_string destination) = 0;
    virtual void rpush(cref_string key, cref_string_array elements) = 0;
    virtual void rpushx(cref_string key, cref_string_array elements) = 0;
};

namespace scripting
{
command EVAL        = "EVAL";
command EVALSHA     = "EVALSHA";
command SCRIPT      = "SCRIPT";
}

struct interface_scripting
{
    virtual void eval(cref_string script,
        cref_string_array keys, cref_string_array args) = 0;
    virtual void evalsha(cref_string sha1,
        cref_string_array keys, cref_string_array args) = 0;
    virtual void script_exists(cref_string_array sha1s) = 0;
    virtual void script_flush() = 0;
    virtual void script_kill() = 0;
    virtual void script_load(cref_string script) = 0;
};

namespace sets
{
command SADD        = "SADD";
command SCARD       = "SCARD";
command SDIFF       = "SDIFF";
command SDIFFSTORE  = "SDIFFSTORE";
command SINTER      = "SINTER";
command SINTERSTORE = "SINTERSTORE";
command SISMEMBER   = "SISMEMBER";
command SMEMBERS    = "SMEMBERS";
command SMOVE       = "SMOVE";
command SPOP        = "SPOP";
command SRANDMEMBER = "SRANDMEMBER";
command SREM        = "SREM";
command SSCAN       = "SSCAN";
command SUNION      = "SUNION";
command SUNIONSTORE = "SUNIONSTORE";
}

struct interface_sets
{
    virtual void sadd(cref_string key, cref_string_array members) = 0;
    virtual void scard(cref_string key) = 0;
    virtual void sdiff(cref_string_array keys) = 0;
    virtual void sdiffstore(cref_string destination, cref_string_array keys) = 0;
    virtual void sinter(cref_string_array keys) = 0;
    virtual void sinterstore(cref_string destination, cref_string_array keys) = 0;
    virtual void sismember(cref_string key, cref_string member) = 0;
    virtual void smembers(cref_string key) = 0;
    virtual void smove(cref_string source, cref_string destination,
        cref_string member) = 0;
    virtual void spop(cref_string key) = 0;
    virtual void spop(cref_string key, czint count) = 0;
    virtual void srandmember(cref_string key) = 0;
    virtual void srandmember(cref_string key, czint count) = 0;
    virtual void srem(cref_string key, cref_string_array members) = 0;
    virtual void sscan(cref_string key, cref_string cursor,
        const scan_param& param) = 0;
    virtual void sunion(cref_string_array keys) = 0;
    virtual void sunionstore(cref_string destination, cref_string_array keys) = 0;
};

namespace sorted_sets
{
command BZPOPMAX            = "BZPOPMAX";
command BZPOPMIN            = "BZPOPMIN";
command ZADD                = "ZADD";
command ZCARD               = "ZCARD";
command ZCOUNT              = "ZCOUNT";
command ZINCRBY             = "ZINCRBY";
command ZINTERSTORE         = "ZINTERSTORE";
command ZLEXCOUNT           = "ZLEXCOUNT";
command ZPOPMAX             = "ZPOPMAX";
command ZPOPMIN             = "ZPOPMIN";
command ZRANGE              = "ZRANGE";
command ZRANGEBYLEX         = "ZRANGEBYLEX";
command ZRANGEBYSCORE       = "ZRANGEBYSCORE";
command ZRANK               = "ZRANK";
command ZREM                = "ZREM";
command ZREMRANGEBYLEX      = "ZREMRANGEBYLEX";
command ZREMRANGEBYRANK     = "ZREMRANGEBYRANK";
command ZREMRANGEBYSCORE    = "ZREMRANGEBYSCORE";
command ZREVRANGE           = "ZREVRANGE";
command ZREVRANGEBYLEX      = "ZREVRANGEBYLEX";
command ZREVRANGEBYSCORE    = "ZREVRANGEBYSCORE";
command ZREVRANK            = "ZREVRANK";
command ZSCORE              = "ZSCORE";
command ZUNIONSTORE         = "ZUNIONSTORE";
command ZSCAN               = "ZSCAN";
}

struct interface_sorted_sets
{
    virtual void bzpopmax(cref_string_array keys, czint timeout) = 0;
    virtual void bzpopmin(cref_string_array keys, czint timeout) = 0;
    virtual void zadd(cref_string key, const zadd_param& param,
        cref_string_map member_score_map) = 0;
    virtual void zcard(cref_string key) = 0;
    virtual void zcount(cref_string key, cref_string min, cref_string max) = 0;
    virtual void zincrby(cref_string key, cref_string increment, cref_string member) = 0;
    virtual void zinterstore(cref_string destination, cref_string_array keys,
        const z_param& param) = 0;
    virtual void zlexcount(cref_string key, cref_string min, cref_string max) = 0;
    virtual void zpopmax(cref_string key) = 0;
    virtual void zpopmax(cref_string key, czint count) = 0;
    virtual void zpopmin(cref_string key) = 0;
    virtual void zpopmin(cref_string key, czint count) = 0;
    virtual void zrange(cref_string key, czint start, czint stop, bool withscores) = 0;
    virtual void zrangebylex(cref_string key, cref_string max, cref_string min) = 0;
    virtual void zrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) = 0;
    virtual void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) = 0;
    virtual void zrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) = 0;
    virtual void zrank(cref_string key, cref_string member) = 0;
    virtual void zrem(cref_string key, cref_string_array members) = 0;
    virtual void zremrangebylex(cref_string key, cref_string min, cref_string max) = 0;
    virtual void zremrangebyrank(cref_string key, czint start, czint stop) = 0;
    virtual void zremrangebyscore(cref_string key, cref_string min, cref_string max) = 0;
    virtual void zrevrange(cref_string key, czint start, czint stop, bool withscores) = 0;
    virtual void zrevrangebylex(cref_string key, cref_string max, cref_string min) = 0;
    virtual void zrevrangebylex(cref_string key, cref_string max, cref_string min,
        czint offset, czint count) = 0;
    virtual void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores) = 0;
    virtual void zrevrangebyscore(cref_string key, cref_string min, cref_string max,
        bool withscores, czint offset, czint count) = 0;
    virtual void zrevrank(cref_string key, cref_string member) = 0;
    virtual void zscan(cref_string key, cref_string cursor, const scan_param& param) = 0;
    virtual void zscore(cref_string key, cref_string member) = 0;
    virtual void zunionstore(cref_string destination, cref_string_array keys,
        const z_param& param) = 0;
};

namespace streams
{
command XACK        = "XACK";
command XADD        = "XADD";
command XCLAIM      = "XCLAIM";
command XDEL        = "XDEL";
command XGROUP      = "XGROUP";
command XINFO       = "XINFO";
command XLEN        = "XLEN";
command XPENDING    = "XPENDING";
command XRANGE      = "XRANGE";
command XREAD       = "XREAD";
command XREADGROUP  = "XREADGROUP";
command XREVRANGE   = "XREVRANGE";
command XTRIM       = "XTRIM";
}

struct interface_streams
{
    virtual void xack(cref_string key, cref_string group,
        cref_stream_id_array ids) = 0;
    virtual void xadd(cref_string key, const xadd_param param,
        cref_string id, cref_string_map field_value_map) = 0;
    virtual void xclaim(cref_string key, cref_string group, cref_string consumer,
        czint min_idle_time, cref_stream_id_array ids,
        const xclaim_param& param) = 0;
    virtual void xdel(cref_string key, cref_stream_id_array ids) = 0;
    virtual void xgroup_create(cref_string key, cref_string groupname,
        cref_string id, bool mkstream) = 0;
    virtual void xgroup_delconsumer(cref_string key, cref_string groupname,
        cref_string consumername) = 0;
    virtual void xgroup_destroy(cref_string key, cref_string groupname) = 0;
    virtual void xgroup_setid(cref_string key, cref_string groupname,
        cref_string id) = 0;
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
        cref_string start, cref_string end, czint count,
        cref_string consumer) = 0;
    virtual void xrange(cref_string key,
        cref_string start, cref_string end) = 0;
    virtual void xrange(cref_string key,
        cref_string start, cref_string end, czint count) = 0;
    virtual void xread(const xread_param& param, cref_string_array keys,
        cref_stream_id_array ids) = 0;
    virtual void xreadgroup(cref_string group, cref_string consumer,
        const xread_param& param, bool noack, cref_string_array keys,
        cref_stream_id_array ids) = 0;
    virtual void xrevrange(cref_string key,
        cref_string end, cref_string start) = 0;
    virtual void xrevrange(cref_string key,
        cref_string end, cref_string start, czint count) = 0;
    virtual void xtrim(cref_string key, czint threshold,
        bool almost_exact = false) = 0;
};

namespace strings
{
command APPEND      = "APPEND";
command BITCOUNT    = "BITCOUNT";
command BITOP       = "BITOP";
command DECR        = "DECR";
command DECRBY      = "DECRBY";
command GET         = "GET";
command GETBIT      = "GETBIT";
command GETRANGE    = "GETRANGE";
command GETSET      = "GETSET";
command INCR        = "INCR";
command INCRBY      = "INCRBY";
command INCRBYFLOAT = "INCRBYFLOAT";
command MGET        = "MGET";
command MSET        = "MSET";
command MSETNX      = "MSETNX";
command PSETEX      = "PSETEX";
command SET         = "SET";
command SETBIT      = "SETBIT";
command SETEX       = "SETEX";
command SETNX       = "SETNX";
command SETRANGE    = "SETRANGE";
command STRLEN      = "STRLEN";
}

struct interface_strings
{
    virtual void append(cref_string key, cref_string value) = 0;
    virtual void bitcount(cref_string key, czint start, czint end) = 0;
    virtual void bitop(bit_operation op, cref_string dest_key, cref_string_array keys) = 0;
    virtual void decr(cref_string key) = 0;
    virtual void decrby(cref_string key, czint decrement) = 0;
    virtual void get(cref_string key) = 0;
    virtual void getbit(cref_string key, czint offset) = 0;
    virtual void getrange(cref_string key, czint start, czint end) = 0;
    virtual void getset(cref_string key, cref_string value) = 0;
    virtual void incr(cref_string key) = 0;
    virtual void incrby(cref_string key, czint increment) = 0;
    virtual void incrbyfloat(cref_string key, double increment) = 0;
    virtual void mget(cref_string_array keys) = 0;
    virtual void mset(cref_string_array key_value_pairs) = 0;
    virtual void msetnx(cref_string_array key_value_pairs) = 0;
    virtual void psetex(cref_string key, czint milliseconds, cref_string value) = 0;
    virtual void set(cref_string key, cref_string value, cref_string_array params) = 0;
    virtual void setbit(cref_string key, czint offset, czbit bit) = 0;
    virtual void setex(cref_string key, czint seconds, cref_string value) = 0;
    virtual void setnx(cref_string key, cref_string value) = 0;
    virtual void setrange(cref_string key, czint offset, cref_string value) = 0;
    virtual void strlen(cref_string key) = 0;
};

namespace transactions
{
command DISCARD     = "DISCARD";
command EXEC        = "EXEC";
command MULTI       = "MULTI";
command UNWATCH     = "UNWATCH";
command WATCH       = "WATCH";
}

struct interface_transactions
{
    virtual void discard() = 0;
    virtual void exec() = 0;
    virtual void multi() = 0;
    virtual void unwatch() = 0;
    virtual void watch(cref_string_array keys) = 0;
};

} // namespace cmd

struct interface_commands :
    public cmd::interface_connection,
    public cmd::interface_geo,
    public cmd::interface_hashes,
    public cmd::interface_hyper_log_log,
    public cmd::interface_keys,
    public cmd::interface_lists,
    public cmd::interface_scripting,
    public cmd::interface_sets,
    public cmd::interface_sorted_sets,
    public cmd::interface_streams,
    public cmd::interface_strings,
    public cmd::interface_transactions
{};

namespace kwd
{

using keyword = const czstring;

keyword KEYS        = "KEYS";
keyword REFCOUNT    = "REFCOUNT";
keyword ENCODING    = "ENCODING";
keyword IDLETIME    = "IDLETIME";
keyword FREQ        = "FREQ";
keyword HELP        = "HELP";
keyword TYPE        = "TYPE";
keyword EXISTS      = "EXISTS";
keyword FLUSH       = "FLUSH";
keyword KILL        = "KILL";
keyword LOAD        = "LOAD";
keyword COUNT       = "COUNT";
keyword WITHSCORES  = "WITHSCORES";
keyword LIMIT       = "LIMIT";
keyword CREATE      = "CREATE ";
keyword MKSTREAM    = "MKSTREAM";
keyword SETID       = "SETID";
keyword DESTROY     = "DESTROY";
keyword DELCONSUMER = "DELCONSUMER";
keyword CONSUMERS   = "CONSUMERS";
keyword GROUPS      = "GROUPS";
keyword STREAM      = "STREAM";
keyword STREAMS     = "STREAMS";
keyword NOACK       = "NOACK";
keyword MAXLEN      = "MAXLEN";
keyword ALMOST_EXACT = "~";

} // namespace kwd

} // namespace detail
} // namespace czredis