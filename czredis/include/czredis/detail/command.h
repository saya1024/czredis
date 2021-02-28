#pragma once

#include "../common.h"

namespace czredis
{
namespace detail
{

namespace command
{
using cstr = const char[];

//connection
constexpr cstr AUTH                 = "AUTH";
constexpr cstr ECHO                 = "ECHO";
constexpr cstr PING                 = "PING";
constexpr cstr QUIT                 = "QUIT";
constexpr cstr SELECT               = "SELECT";

//geo
constexpr cstr GEOADD               = "GEOADD";
constexpr cstr GEODIST              = "GEODIST";
constexpr cstr GEOHASH              = "GEOHASH";
constexpr cstr GEOPOS               = "GEOPOS";
constexpr cstr GEORADIUS            = "GEORADIUS";
constexpr cstr GEORADIUS_RO         = "GEORADIUS_RO";
constexpr cstr GEORADIUSBYMEMBER    = "GEORADIUSBYMEMBER";
constexpr cstr GEORADIUSBYMEMBER_RO = "GEORADIUSBYMEMBER_RO";

//hashes
constexpr cstr HDEL                 = "HDEL";
constexpr cstr HEXISTS              = "HEXISTS";
constexpr cstr HGET                 = "HGET";
constexpr cstr HGETALL              = "HGETALL";
constexpr cstr HINCRBY              = "HINCRBY";
constexpr cstr HINCRBYFLOAT         = "HINCRBYFLOAT";
constexpr cstr HKEYS                = "HKEYS";
constexpr cstr HLEN                 = "HLEN";
constexpr cstr HMGET                = "HMGET";
constexpr cstr HMSET                = "HMSET";
constexpr cstr HSCAN                = "HSCAN";
constexpr cstr HSET                 = "HSET";
constexpr cstr HSETNX               = "HSETNX";
constexpr cstr HSTRLEN              = "HSTRLEN";
constexpr cstr HVALS                = "HVALS";

//hyper_log_log
constexpr cstr PFADD                = "PFADD";
constexpr cstr PFCOUNT              = "PFCOUNT";
constexpr cstr PFMERGE              = "PFMERGE";

//keys
constexpr cstr DEL                  = "DEL";
constexpr cstr DUMP                 = "DUMP";
constexpr cstr EXISTS               = "EXISTS";
constexpr cstr EXPIRE               = "EXPIRE";
constexpr cstr EXPIREAT             = "EXPIREAT";
constexpr cstr KEYS                 = "KEYS";
constexpr cstr MIGRATE              = "MIGRATE";
constexpr cstr MOVE                 = "MOVE";
constexpr cstr OBJECT               = "OBJECT";
constexpr cstr PERSIST              = "PERSIST";
constexpr cstr PEXPIRE              = "PEXPIRE";
constexpr cstr PEXPIREAT            = "PEXPIREAT";
constexpr cstr PTTL                 = "PTTL";
constexpr cstr RANDOMKEY            = "RANDOMKEY";
constexpr cstr RENAME               = "RENAME";
constexpr cstr RENAMENX             = "RENAMENX";
constexpr cstr RESTORE              = "RESTORE";
constexpr cstr SCAN                 = "SCAN";
constexpr cstr SORT                 = "SORT";
constexpr cstr TOUCH                = "TOUCH";
constexpr cstr TTL                  = "TTL";
constexpr cstr TYPE                 = "TYPE";
constexpr cstr UNLINK               = "UNLINK";
constexpr cstr WAIT                 = "WAIT";

//lists
constexpr cstr BLPOP                = "BLPOP";
constexpr cstr BRPOP                = "BRPOP";
constexpr cstr BRPOPLPUSH           = "BRPOPLPUSH";
constexpr cstr LINDEX               = "LINDEX";
constexpr cstr LINSERT              = "LINSERT";
constexpr cstr LLEN                 = "LLEN";
constexpr cstr LPOP                 = "LPOP";
constexpr cstr LPUSH                = "LPUSH";
constexpr cstr LPUSHX               = "LPUSHX";
constexpr cstr LRANGE               = "LRANGE";
constexpr cstr LREM                 = "LREM";
constexpr cstr LSET                 = "LSET";
constexpr cstr LTRIM                = "LTRIM";
constexpr cstr RPOP                 = "RPOP";
constexpr cstr RPOPLPUSH            = "RPOPLPUSH";
constexpr cstr RPUSH                = "RPUSH";
constexpr cstr RPUSHX               = "RPUSHX";

//scripting
constexpr cstr EVAL                 = "EVAL";
constexpr cstr EVALSHA              = "EVALSHA";
constexpr cstr SCRIPT               = "SCRIPT";

//server
constexpr cstr BGREWRITEAOF         = "BGREWRITEAOF";
constexpr cstr BGSAVE               = "BGSAVE";
constexpr cstr CONFIG               = "CONFIG";
constexpr cstr DBSIZE               = "DBSIZE";
constexpr cstr FLUSHALL             = "FLUSHALL";
constexpr cstr FLUSHDB              = "FLUSHDB";
constexpr cstr INFO                 = "INFO";
constexpr cstr LASTSAVE             = "LASTSAVE";
constexpr cstr MEMORY               = "MEMORY";
constexpr cstr MODULE               = "MODULE";
constexpr cstr REPLICAOF            = "REPLICAOF";
constexpr cstr SAVE                 = "SAVE";
constexpr cstr SHUTDOWN             = "SHUTDOWN";
constexpr cstr SLAVEOF              = "SLAVEOF";
constexpr cstr SLOWLOG              = "SLOWLOG";
constexpr cstr SWAPDB               = "SWAPDB";
constexpr cstr TIME                 = "TIME";

//sets
constexpr cstr SADD                 = "SADD";
constexpr cstr SCARD                = "SCARD";
constexpr cstr SDIFF                = "SDIFF";
constexpr cstr SDIFFSTORE           = "SDIFFSTORE";
constexpr cstr SINTER               = "SINTER";
constexpr cstr SINTERSTORE          = "SINTERSTORE";
constexpr cstr SISMEMBER            = "SISMEMBER";
constexpr cstr SMEMBERS             = "SMEMBERS";
constexpr cstr SMOVE                = "SMOVE";
constexpr cstr SPOP                 = "SPOP";
constexpr cstr SRANDMEMBER          = "SRANDMEMBER";
constexpr cstr SREM                 = "SREM";
constexpr cstr SSCAN                = "SSCAN";
constexpr cstr SUNION               = "SUNION";
constexpr cstr SUNIONSTORE          = "SUNIONSTORE";

//sorted_sets
constexpr cstr BZPOPMAX             = "BZPOPMAX";
constexpr cstr BZPOPMIN             = "BZPOPMIN";
constexpr cstr ZADD                 = "ZADD";
constexpr cstr ZCARD                = "ZCARD";
constexpr cstr ZCOUNT               = "ZCOUNT";
constexpr cstr ZINCRBY              = "ZINCRBY";
constexpr cstr ZINTERSTORE          = "ZINTERSTORE";
constexpr cstr ZLEXCOUNT            = "ZLEXCOUNT";
constexpr cstr ZPOPMAX              = "ZPOPMAX";
constexpr cstr ZPOPMIN              = "ZPOPMIN";
constexpr cstr ZRANGE               = "ZRANGE";
constexpr cstr ZRANGEBYLEX          = "ZRANGEBYLEX";
constexpr cstr ZRANGEBYSCORE        = "ZRANGEBYSCORE";
constexpr cstr ZRANK                = "ZRANK";
constexpr cstr ZREM                 = "ZREM";
constexpr cstr ZREMRANGEBYLEX       = "ZREMRANGEBYLEX";
constexpr cstr ZREMRANGEBYRANK      = "ZREMRANGEBYRANK";
constexpr cstr ZREMRANGEBYSCORE     = "ZREMRANGEBYSCORE";
constexpr cstr ZREVRANGE            = "ZREVRANGE";
constexpr cstr ZREVRANGEBYLEX       = "ZREVRANGEBYLEX";
constexpr cstr ZREVRANGEBYSCORE     = "ZREVRANGEBYSCORE";
constexpr cstr ZREVRANK             = "ZREVRANK";
constexpr cstr ZSCORE               = "ZSCORE";
constexpr cstr ZUNIONSTORE          = "ZUNIONSTORE";
constexpr cstr ZSCAN                = "ZSCAN";

//streams
constexpr cstr XACK                 = "XACK";
constexpr cstr XADD                 = "XADD";
constexpr cstr XCLAIM               = "XCLAIM";
constexpr cstr XDEL                 = "XDEL";
constexpr cstr XGROUP               = "XGROUP";
constexpr cstr XINFO                = "XINFO";
constexpr cstr XLEN                 = "XLEN";
constexpr cstr XPENDING             = "XPENDING";
constexpr cstr XRANGE               = "XRANGE";
constexpr cstr XREAD                = "XREAD";
constexpr cstr XREADGROUP           = "XREADGROUP";
constexpr cstr XREVRANGE            = "XREVRANGE";
constexpr cstr XTRIM                = "XTRIM";

//strings
constexpr cstr APPEND               = "APPEND";
constexpr cstr BITCOUNT             = "BITCOUNT";
constexpr cstr BITFIELD             = "BITFIELD";
constexpr cstr BITFIELD_RO          = "BITFIELD_RO";
constexpr cstr BITOP                = "BITOP";
constexpr cstr BITPOS               = "BITPOS";
constexpr cstr DECR                 = "DECR";
constexpr cstr DECRBY               = "DECRBY";
constexpr cstr GET                  = "GET";
constexpr cstr GETBIT               = "GETBIT";
constexpr cstr GETRANGE             = "GETRANGE";
constexpr cstr GETSET               = "GETSET";
constexpr cstr INCR                 = "INCR";
constexpr cstr INCRBY               = "INCRBY";
constexpr cstr INCRBYFLOAT          = "INCRBYFLOAT";
constexpr cstr MGET                 = "MGET";
constexpr cstr MSET                 = "MSET";
constexpr cstr MSETNX               = "MSETNX";
constexpr cstr PSETEX               = "PSETEX";
constexpr cstr SET                  = "SET";
constexpr cstr SETBIT               = "SETBIT";
constexpr cstr SETEX                = "SETEX";
constexpr cstr SETNX                = "SETNX";
constexpr cstr SETRANGE             = "SETRANGE";
constexpr cstr STRLEN               = "STRLEN";

//transactions
constexpr cstr DISCARD              = "DISCARD";
constexpr cstr EXEC                 = "EXEC";
constexpr cstr MULTI                = "MULTI";
constexpr cstr UNWATCH              = "UNWATCH";
constexpr cstr WATCH                = "WATCH";
} // namespace command


namespace keyword
{
using cstr = const char[];

constexpr cstr ALMOST_EXACT         = "~";
constexpr cstr CONSUMERS            = "CONSUMERS";
constexpr cstr COUNT                = "COUNT";
constexpr cstr CREATE               = "CREATE ";
constexpr cstr DELCONSUMER          = "DELCONSUMER";
constexpr cstr DESTROY              = "DESTROY";
constexpr cstr DOCTOR               = "DOCTOR";
constexpr cstr ENCODING             = "ENCODING";
constexpr cstr EXECABORT            = "EXECABORT";
constexpr cstr EXISTS               = "EXISTS";
constexpr cstr FLUSH                = "FLUSH";
constexpr cstr FREQ                 = "FREQ";
constexpr cstr GET                  = "GET";
constexpr cstr GROUPS               = "GROUPS";
constexpr cstr HELP                 = "HELP";
constexpr cstr IDLETIME             = "IDLETIME";
constexpr cstr KEYS                 = "KEYS";
constexpr cstr KILL                 = "KILL";
constexpr cstr LEN                  = "LEN";
constexpr cstr LIMIT                = "LIMIT";
constexpr cstr LIST                 = "LIST";
constexpr cstr LOAD                 = "LOAD";
constexpr cstr MAXLEN               = "MAXLEN";
constexpr cstr MKSTREAM             = "MKSTREAM";
constexpr cstr NO                   = "NO";
constexpr cstr NOACK                = "NOACK";
constexpr cstr OK                   = "OK";
constexpr cstr ONE                  = "ONE";
constexpr cstr PONG                 = "PONG";
constexpr cstr QUEUED               = "QUEUED";
constexpr cstr REFCOUNT             = "REFCOUNT";
constexpr cstr RESET                = "RESET";
constexpr cstr RESETSTAT            = "RESETSTAT";
constexpr cstr SAMPLES              = "SAMPLES";
constexpr cstr SCHEDULE             = "SCHEDULE";
constexpr cstr SET                  = "SET";
constexpr cstr SETID                = "SETID";
constexpr cstr STORE                = "STORE";
constexpr cstr STREAM               = "STREAM";
constexpr cstr STREAMS              = "STREAMS";
constexpr cstr TYPE                 = "TYPE";
constexpr cstr UNLOAD               = "UNLOAD";
constexpr cstr USAGE                = "USAGE";
constexpr cstr WITHSCORES           = "WITHSCORES";
} // namespace keyword

} // namespace detail
} // namespace czredis