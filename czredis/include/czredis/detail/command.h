#pragma once

#include "../common.h"

namespace czredis
{
namespace detail
{

namespace command
{
using cstr = const czstring;

//connection
cstr AUTH                 = "AUTH";
cstr ECHO                 = "ECHO";
cstr PING                 = "PING";
cstr QUIT                 = "QUIT";
cstr SELECT               = "SELECT";

//geo
cstr GEOADD               = "GEOADD";
cstr GEODIST              = "GEODIST";
cstr GEOHASH              = "GEOHASH";
cstr GEOPOS               = "GEOPOS";
cstr GEORADIUS            = "GEORADIUS";
cstr GEORADIUS_RO         = "GEORADIUS_RO";
cstr GEORADIUSBYMEMBER    = "GEORADIUSBYMEMBER";
cstr GEORADIUSBYMEMBER_RO = "GEORADIUSBYMEMBER_RO";

//hashes
cstr HDEL                 = "HDEL";
cstr HEXISTS              = "HEXISTS";
cstr HGET                 = "HGET";
cstr HGETALL              = "HGETALL";
cstr HINCRBY              = "HINCRBY";
cstr HINCRBYFLOAT         = "HINCRBYFLOAT";
cstr HKEYS                = "HKEYS";
cstr HLEN                 = "HLEN";
cstr HMGET                = "HMGET";
cstr HMSET                = "HMSET";
cstr HSCAN                = "HSCAN";
cstr HSET                 = "HSET";
cstr HSETNX               = "HSETNX";
cstr HSTRLEN              = "HSTRLEN";
cstr HVALS                = "HVALS";

//hyper_log_log
cstr PFADD                = "PFADD";
cstr PFCOUNT              = "PFCOUNT";
cstr PFMERGE              = "PFMERGE";

//keys
cstr DEL                  = "DEL";
cstr DUMP                 = "DUMP";
cstr EXISTS               = "EXISTS";
cstr EXPIRE               = "EXPIRE";
cstr EXPIREAT             = "EXPIREAT";
cstr KEYS                 = "KEYS";
cstr MIGRATE              = "MIGRATE";
cstr MOVE                 = "MOVE";
cstr OBJECT               = "OBJECT";
cstr PERSIST              = "PERSIST";
cstr PEXPIRE              = "PEXPIRE";
cstr PEXPIREAT            = "PEXPIREAT";
cstr PTTL                 = "PTTL";
cstr RANDOMKEY            = "RANDOMKEY";
cstr RENAME               = "RENAME";
cstr RENAMENX             = "RENAMENX";
cstr RESTORE              = "RESTORE";
cstr SCAN                 = "SCAN";
cstr SORT                 = "SORT";
cstr TOUCH                = "TOUCH";
cstr TTL                  = "TTL";
cstr TYPE                 = "TYPE";
cstr UNLINK               = "UNLINK";
cstr WAIT                 = "WAIT";

//lists
cstr BLPOP                = "BLPOP";
cstr BRPOP                = "BRPOP";
cstr BRPOPLPUSH           = "BRPOPLPUSH";
cstr LINDEX               = "LINDEX";
cstr LINSERT              = "LINSERT";
cstr LLEN                 = "LLEN";
cstr LPOP                 = "LPOP";
cstr LPUSH                = "LPUSH";
cstr LPUSHX               = "LPUSHX";
cstr LRANGE               = "LRANGE";
cstr LREM                 = "LREM";
cstr LSET                 = "LSET";
cstr LTRIM                = "LTRIM";
cstr RPOP                 = "RPOP";
cstr RPOPLPUSH            = "RPOPLPUSH";
cstr RPUSH                = "RPUSH";
cstr RPUSHX               = "RPUSHX";

//scripting
cstr EVAL                 = "EVAL";
cstr EVALSHA              = "EVALSHA";
cstr SCRIPT               = "SCRIPT";

//server
cstr BGREWRITEAOF         = "BGREWRITEAOF";
cstr BGSAVE               = "BGSAVE";
cstr CONFIG               = "CONFIG";
cstr DBSIZE               = "DBSIZE";
cstr FLUSHALL             = "FLUSHALL";
cstr FLUSHDB              = "FLUSHDB";
cstr INFO                 = "INFO";
cstr LASTSAVE             = "LASTSAVE";
cstr MEMORY               = "MEMORY";
cstr MODULE               = "MODULE";
cstr REPLICAOF            = "REPLICAOF";
cstr SAVE                 = "SAVE";
cstr SHUTDOWN             = "SHUTDOWN";
cstr SLAVEOF              = "SLAVEOF";
cstr SLOWLOG              = "SLOWLOG";
cstr SWAPDB               = "SWAPDB";
cstr TIME                 = "TIME";

//sets
cstr SADD                 = "SADD";
cstr SCARD                = "SCARD";
cstr SDIFF                = "SDIFF";
cstr SDIFFSTORE           = "SDIFFSTORE";
cstr SINTER               = "SINTER";
cstr SINTERSTORE          = "SINTERSTORE";
cstr SISMEMBER            = "SISMEMBER";
cstr SMEMBERS             = "SMEMBERS";
cstr SMOVE                = "SMOVE";
cstr SPOP                 = "SPOP";
cstr SRANDMEMBER          = "SRANDMEMBER";
cstr SREM                 = "SREM";
cstr SSCAN                = "SSCAN";
cstr SUNION               = "SUNION";
cstr SUNIONSTORE          = "SUNIONSTORE";

//sorted_sets
cstr BZPOPMAX             = "BZPOPMAX";
cstr BZPOPMIN             = "BZPOPMIN";
cstr ZADD                 = "ZADD";
cstr ZCARD                = "ZCARD";
cstr ZCOUNT               = "ZCOUNT";
cstr ZINCRBY              = "ZINCRBY";
cstr ZINTERSTORE          = "ZINTERSTORE";
cstr ZLEXCOUNT            = "ZLEXCOUNT";
cstr ZPOPMAX              = "ZPOPMAX";
cstr ZPOPMIN              = "ZPOPMIN";
cstr ZRANGE               = "ZRANGE";
cstr ZRANGEBYLEX          = "ZRANGEBYLEX";
cstr ZRANGEBYSCORE        = "ZRANGEBYSCORE";
cstr ZRANK                = "ZRANK";
cstr ZREM                 = "ZREM";
cstr ZREMRANGEBYLEX       = "ZREMRANGEBYLEX";
cstr ZREMRANGEBYRANK      = "ZREMRANGEBYRANK";
cstr ZREMRANGEBYSCORE     = "ZREMRANGEBYSCORE";
cstr ZREVRANGE            = "ZREVRANGE";
cstr ZREVRANGEBYLEX       = "ZREVRANGEBYLEX";
cstr ZREVRANGEBYSCORE     = "ZREVRANGEBYSCORE";
cstr ZREVRANK             = "ZREVRANK";
cstr ZSCORE               = "ZSCORE";
cstr ZUNIONSTORE          = "ZUNIONSTORE";
cstr ZSCAN                = "ZSCAN";

//streams
cstr XACK                 = "XACK";
cstr XADD                 = "XADD";
cstr XCLAIM               = "XCLAIM";
cstr XDEL                 = "XDEL";
cstr XGROUP               = "XGROUP";
cstr XINFO                = "XINFO";
cstr XLEN                 = "XLEN";
cstr XPENDING             = "XPENDING";
cstr XRANGE               = "XRANGE";
cstr XREAD                = "XREAD";
cstr XREADGROUP           = "XREADGROUP";
cstr XREVRANGE            = "XREVRANGE";
cstr XTRIM                = "XTRIM";

//strings
cstr APPEND               = "APPEND";
cstr BITCOUNT             = "BITCOUNT";
cstr BITFIELD             = "BITFIELD";
cstr BITFIELD_RO          = "BITFIELD_RO";
cstr BITOP                = "BITOP";
cstr BITPOS               = "BITPOS";
cstr DECR                 = "DECR";
cstr DECRBY               = "DECRBY";
cstr GET                  = "GET";
cstr GETBIT               = "GETBIT";
cstr GETRANGE             = "GETRANGE";
cstr GETSET               = "GETSET";
cstr INCR                 = "INCR";
cstr INCRBY               = "INCRBY";
cstr INCRBYFLOAT          = "INCRBYFLOAT";
cstr MGET                 = "MGET";
cstr MSET                 = "MSET";
cstr MSETNX               = "MSETNX";
cstr PSETEX               = "PSETEX";
cstr SET                  = "SET";
cstr SETBIT               = "SETBIT";
cstr SETEX                = "SETEX";
cstr SETNX                = "SETNX";
cstr SETRANGE             = "SETRANGE";
cstr STRLEN               = "STRLEN";

//transactions
cstr DISCARD              = "DISCARD";
cstr EXEC                 = "EXEC";
cstr MULTI                = "MULTI";
cstr UNWATCH              = "UNWATCH";
cstr WATCH                = "WATCH";
} // namespace command


namespace keyword
{
using cstr = const czstring;

cstr ALMOST_EXACT         = "~";
cstr CONSUMERS            = "CONSUMERS";
cstr COUNT                = "COUNT";
cstr CREATE               = "CREATE ";
cstr DELCONSUMER          = "DELCONSUMER";
cstr DESTROY              = "DESTROY";
cstr DOCTOR               = "DOCTOR";
cstr ENCODING             = "ENCODING";
cstr EXECABORT            = "EXECABORT";
cstr EXISTS               = "EXISTS";
cstr FLUSH                = "FLUSH";
cstr FREQ                 = "FREQ";
cstr GET                  = "GET";
cstr GROUPS               = "GROUPS";
cstr HELP                 = "HELP";
cstr IDLETIME             = "IDLETIME";
cstr KEYS                 = "KEYS";
cstr KILL                 = "KILL";
cstr LEN                  = "LEN";
cstr LIMIT                = "LIMIT";
cstr LIST                 = "LIST";
cstr LOAD                 = "LOAD";
cstr MAXLEN               = "MAXLEN";
cstr MKSTREAM             = "MKSTREAM";
cstr NO                   = "NO";
cstr NOACK                = "NOACK";
cstr OK                   = "OK";
cstr ONE                  = "ONE";
cstr PONG                 = "PONG";
cstr QUEUED               = "QUEUED";
cstr REFCOUNT             = "REFCOUNT";
cstr RESET                = "RESET";
cstr RESETSTAT            = "RESETSTAT";
cstr SAMPLES              = "SAMPLES";
cstr SCHEDULE             = "SCHEDULE";
cstr SET                  = "SET";
cstr SETID                = "SETID";
cstr STORE                = "STORE";
cstr STREAM               = "STREAM";
cstr STREAMS              = "STREAMS";
cstr TYPE                 = "TYPE";
cstr UNLOAD               = "UNLOAD";
cstr USAGE                = "USAGE";
cstr WITHSCORES           = "WITHSCORES";
} // namespace keyword

} // namespace detail
} // namespace czredis