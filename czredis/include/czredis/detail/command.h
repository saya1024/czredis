#pragma once

#include "../common.h"

namespace czredis
{
namespace detail
{
namespace command
{

//connection
cref_string AUTH        = "AUTH";
cref_string ECHO        = "ECHO";
cref_string PING        = "PING";
cref_string QUIT        = "QUIT";
cref_string SELECT      = "SELECT";

//geo
cref_string GEOADD      = "GEOADD";
cref_string GEODIST     = "GEODIST";
cref_string GEOHASH     = "GEOHASH";
cref_string GEOPOS      = "GEOPOS";
cref_string GEORADIUS   = "GEORADIUS";
cref_string GEORADIUS_RO = "GEORADIUS_RO";
cref_string GEORADIUSBYMEMBER = "GEORADIUSBYMEMBER";
cref_string GEORADIUSBYMEMBER_RO = "GEORADIUSBYMEMBER_RO";

//hashes
cref_string HDEL        = "HDEL";
cref_string HEXISTS     = "HEXISTS";
cref_string HGET        = "HGET";
cref_string HGETALL     = "HGETALL";
cref_string HINCRBY     = "HINCRBY";
cref_string HINCRBYFLOAT = "HINCRBYFLOAT";
cref_string HKEYS       = "HKEYS";
cref_string HLEN        = "HLEN";
cref_string HMGET       = "HMGET";
cref_string HMSET       = "HMSET";
cref_string HSCAN       = "HSCAN";
cref_string HSET        = "HSET";
cref_string HSETNX      = "HSETNX";
cref_string HSTRLEN     = "HSTRLEN";
cref_string HVALS       = "HVALS";

//hyper_log_log
cref_string PFADD       = "PFADD";
cref_string PFCOUNT     = "PFCOUNT";
cref_string PFMERGE     = "PFMERGE";

//keys
cref_string DEL         = "DEL";
cref_string DUMP        = "DUMP";
cref_string EXISTS      = "EXISTS";
cref_string EXPIRE      = "EXPIRE";
cref_string EXPIREAT    = "EXPIREAT";
cref_string KEYS        = "KEYS";
cref_string MIGRATE     = "MIGRATE";
cref_string MOVE        = "MOVE";
cref_string OBJECT      = "OBJECT";
cref_string PERSIST     = "PERSIST";
cref_string PEXPIRE     = "PEXPIRE";
cref_string PEXPIREAT   = "PEXPIREAT";
cref_string PTTL        = "PTTL";
cref_string RANDOMKEY   = "RANDOMKEY";
cref_string RENAME      = "RENAME";
cref_string RENAMENX    = "RENAMENX";
cref_string RESTORE     = "RESTORE";
cref_string SCAN        = "SCAN";
cref_string SORT        = "SORT";
cref_string TOUCH       = "TOUCH";
cref_string TTL         = "TTL";
cref_string TYPE        = "TYPE";
cref_string UNLINK      = "UNLINK";
cref_string WAIT        = "WAIT";

//lists
cref_string BLPOP       = "BLPOP";
cref_string BRPOP       = "BRPOP";
cref_string BRPOPLPUSH  = "BRPOPLPUSH";
cref_string LINDEX      = "LINDEX";
cref_string LINSERT     = "LINSERT";
cref_string LLEN        = "LLEN";
cref_string LPOP        = "LPOP";
cref_string LPUSH       = "LPUSH";
cref_string LPUSHX      = "LPUSHX";
cref_string LRANGE      = "LRANGE";
cref_string LREM        = "LREM";
cref_string LSET        = "LSET";
cref_string LTRIM       = "LTRIM";
cref_string RPOP        = "RPOP";
cref_string RPOPLPUSH   = "RPOPLPUSH";
cref_string RPUSH       = "RPUSH";
cref_string RPUSHX      = "RPUSHX";

//scripting
cref_string EVAL        = "EVAL";
cref_string EVALSHA     = "EVALSHA";
cref_string SCRIPT      = "SCRIPT";

//sets
cref_string SADD        = "SADD";
cref_string SCARD       = "SCARD";
cref_string SDIFF       = "SDIFF";
cref_string SDIFFSTORE  = "SDIFFSTORE";
cref_string SINTER      = "SINTER";
cref_string SINTERSTORE = "SINTERSTORE";
cref_string SISMEMBER   = "SISMEMBER";
cref_string SMEMBERS    = "SMEMBERS";
cref_string SMOVE       = "SMOVE";
cref_string SPOP        = "SPOP";
cref_string SRANDMEMBER = "SRANDMEMBER";
cref_string SREM        = "SREM";
cref_string SSCAN       = "SSCAN";
cref_string SUNION      = "SUNION";
cref_string SUNIONSTORE = "SUNIONSTORE";

//sorted_sets
cref_string BZPOPMAX            = "BZPOPMAX";
cref_string BZPOPMIN            = "BZPOPMIN";
cref_string ZADD                = "ZADD";
cref_string ZCARD               = "ZCARD";
cref_string ZCOUNT              = "ZCOUNT";
cref_string ZINCRBY             = "ZINCRBY";
cref_string ZINTERSTORE         = "ZINTERSTORE";
cref_string ZLEXCOUNT           = "ZLEXCOUNT";
cref_string ZPOPMAX             = "ZPOPMAX";
cref_string ZPOPMIN             = "ZPOPMIN";
cref_string ZRANGE              = "ZRANGE";
cref_string ZRANGEBYLEX         = "ZRANGEBYLEX";
cref_string ZRANGEBYSCORE       = "ZRANGEBYSCORE";
cref_string ZRANK               = "ZRANK";
cref_string ZREM                = "ZREM";
cref_string ZREMRANGEBYLEX      = "ZREMRANGEBYLEX";
cref_string ZREMRANGEBYRANK     = "ZREMRANGEBYRANK";
cref_string ZREMRANGEBYSCORE    = "ZREMRANGEBYSCORE";
cref_string ZREVRANGE           = "ZREVRANGE";
cref_string ZREVRANGEBYLEX      = "ZREVRANGEBYLEX";
cref_string ZREVRANGEBYSCORE    = "ZREVRANGEBYSCORE";
cref_string ZREVRANK            = "ZREVRANK";
cref_string ZSCORE              = "ZSCORE";
cref_string ZUNIONSTORE         = "ZUNIONSTORE";
cref_string ZSCAN               = "ZSCAN";

//streams
cref_string XACK        = "XACK";
cref_string XADD        = "XADD";
cref_string XCLAIM      = "XCLAIM";
cref_string XDEL        = "XDEL";
cref_string XGROUP      = "XGROUP";
cref_string XINFO       = "XINFO";
cref_string XLEN        = "XLEN";
cref_string XPENDING    = "XPENDING";
cref_string XRANGE      = "XRANGE";
cref_string XREAD       = "XREAD";
cref_string XREADGROUP  = "XREADGROUP";
cref_string XREVRANGE   = "XREVRANGE";
cref_string XTRIM       = "XTRIM";

//strings
cref_string APPEND      = "APPEND";
cref_string BITCOUNT    = "BITCOUNT";
cref_string BITFIELD    = "BITFIELD";
cref_string BITFIELD_RO = "BITFIELD_RO";
cref_string BITOP       = "BITOP";
cref_string BITPOS      = "BITPOS";
cref_string DECR        = "DECR";
cref_string DECRBY      = "DECRBY";
cref_string GET         = "GET";
cref_string GETBIT      = "GETBIT";
cref_string GETRANGE    = "GETRANGE";
cref_string GETSET      = "GETSET";
cref_string INCR        = "INCR";
cref_string INCRBY      = "INCRBY";
cref_string INCRBYFLOAT = "INCRBYFLOAT";
cref_string MGET        = "MGET";
cref_string MSET        = "MSET";
cref_string MSETNX      = "MSETNX";
cref_string PSETEX      = "PSETEX";
cref_string SET         = "SET";
cref_string SETBIT      = "SETBIT";
cref_string SETEX       = "SETEX";
cref_string SETNX       = "SETNX";
cref_string SETRANGE    = "SETRANGE";
cref_string STRLEN      = "STRLEN";

//transactions
cref_string DISCARD     = "DISCARD";
cref_string EXEC        = "EXEC";
cref_string MULTI       = "MULTI";
cref_string UNWATCH     = "UNWATCH";
cref_string WATCH       = "WATCH";

} // namespace command


namespace keyword
{
cref_string PONG        = "PONG";
cref_string KEYS        = "KEYS";
cref_string REFCOUNT    = "REFCOUNT";
cref_string ENCODING    = "ENCODING";
cref_string IDLETIME    = "IDLETIME";
cref_string FREQ        = "FREQ";
cref_string HELP        = "HELP";
cref_string STORE       = "STORE";
cref_string TYPE        = "TYPE";
cref_string EXISTS      = "EXISTS";
cref_string FLUSH       = "FLUSH";
cref_string KILL        = "KILL";
cref_string LOAD        = "LOAD";
cref_string COUNT       = "COUNT";
cref_string WITHSCORES  = "WITHSCORES";
cref_string LIMIT       = "LIMIT";
cref_string CREATE      = "CREATE ";
cref_string MKSTREAM    = "MKSTREAM";
cref_string SETID       = "SETID";
cref_string DESTROY     = "DESTROY";
cref_string DELCONSUMER = "DELCONSUMER";
cref_string CONSUMERS   = "CONSUMERS";
cref_string GROUPS      = "GROUPS";
cref_string STREAM      = "STREAM";
cref_string STREAMS     = "STREAMS";
cref_string NOACK       = "NOACK";
cref_string MAXLEN      = "MAXLEN";
cref_string ALMOST_EXACT = "~";
} // namespace keyword

} // namespace detail
} // namespace czredis