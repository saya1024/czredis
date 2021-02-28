#pragma once

#include "common.h"
#include "detail/param_templete.h"

namespace czredis
{

class georadius_param : public detail::param_templete
{
    detail::param0 WITHCOORD;
    detail::param0 WITHDIST;
    detail::param0 WITHHASH;
    detail::param1<czint> COUNT;
    detail::param0 ANY;
    detail::param0 ASC;
    detail::param0 DESC;

public:
    georadius_param() :
        WITHCOORD("WITHCOORD"),
        WITHDIST("WITHDIST"),
        WITHHASH("WITHHASH"),
        COUNT("COUNT"),
        ANY("ANY"),
        ASC("ASC"),
        DESC("DESC")
    {}

    void set_WITHCOORD() noexcept { WITHCOORD.use = true; }

    void set_WITHDIST() noexcept { WITHDIST.use = true; }

    void set_WITHHASH() noexcept { WITHHASH.use = true; }

    void set_COUNT(czint value, bool any = false) noexcept
    {
        COUNT.use = true;
        COUNT.value1 = value;
        ANY.use = any;
    }

    void set_ASC() noexcept
    {
        ASC.use = true;
        DESC.use = false;
    }

    void set_DESC() noexcept
    {
        DESC.use = true;
        ASC.use = false;
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            WITHCOORD,
            WITHDIST,
            WITHHASH,
            COUNT,
            ANY,
            ASC,
            DESC
        );
    }
};

class georadius_store_param : public detail::param_templete
{
    detail::param1<czstring> STORE;
    detail::param1<czstring> STOREDIST;

public:
    georadius_store_param() :
        STORE("STORE"),
        STOREDIST("STOREDIST")
    {}

    void set_STORE(cref_string key)
    {
        STORE.use = true;
        STORE.value1 = key;
    }

    void set_STOREDIST(cref_string key)
    {
        STOREDIST.use = true;
        STOREDIST.value1 = key;
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            STORE,
            STOREDIST
        );
    }
};

class flush_param : public detail::param_templete
{
    detail::param0 ASYNC;
    detail::param0 SYNC;

public:
    flush_param() :
        ASYNC("ASYNC"),
        SYNC("SYNC")
    {}

    void set_ASYNC()
    {
        ASYNC.use = true;
        SYNC.use = false;
    }

    void set_SYNC()
    {
        SYNC.use = true;
        ASYNC.use = false;
    }

    void append_params(string_array& cmd_params)
    {
        fill_up(cmd_params,
            ASYNC,
            SYNC
        );
    }
};

class scan_param : public detail::param_templete
{
    detail::param1<czstring> MATCH;
    detail::param1<unsigned> COUNT;

public:
    scan_param() :
        MATCH("MATCH"),
        COUNT("COUNT")
    {}

    void set_MATCH(cref_string pattern)
    {
        MATCH.use = true;
        MATCH.value1 = pattern;
    }

    void set_COUNT(unsigned value) noexcept
    {
        COUNT.use = true;
        COUNT.value1 = value;
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            MATCH,
            COUNT
        );
    }
};

class migrate_param : public detail::param_templete
{
    detail::param0 COPY;
    detail::param0 REPLACE;
    detail::param1<czstring> AUTH;
    detail::param2<czstring, czstring> AUTH2;

public:
    migrate_param() :
        COPY("COPY"),
        REPLACE("REPLACE"),
        AUTH("AUTH"),
        AUTH2("AUTH2")
    {}

    void set_copy() noexcept { COPY.use = true; }

    void set_REPLACE() noexcept { REPLACE.use = true; }

    void set_AUTH(cref_string password)
    {
        AUTH.use = true;
        AUTH.value1 = password;
        AUTH2.use = false;
    }

    void set_AUTH2(cref_string username, cref_string password)
    {
        AUTH2.use = true;
        AUTH2.value1 = username;
        AUTH2.value2 = password;
        AUTH.use = false;
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            COPY,
            REPLACE,
            AUTH,
            AUTH2
        );
    }
};

class restore_param : public detail::param_templete
{
    detail::param0 REPLACE;
    detail::param0 ABSTTL;
    detail::param1<czint> IDLETIME;
    detail::param1<czint> FREQ;

public:
    restore_param():
        REPLACE("REPLACE"),
        ABSTTL("ABSTTL"),
        IDLETIME("IDLETIME"),
        FREQ("FREQ")
    {}

    void set_REPLACE() noexcept { REPLACE.use = true; }
    
    void set_ABSTTL() noexcept { ABSTTL.use = true; }

    void set_IDLETIME(czint seconds) noexcept
    {
        IDLETIME.use = true;
        IDLETIME.value1 = seconds;
    }

    void set_FREQ(czint frequency) noexcept
    {
        FREQ.use = true;
        FREQ.value1 = frequency;
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            REPLACE,
            ABSTTL,
            IDLETIME,
            FREQ
        );
    }
};

class sort_param : public detail::param_templete
{
    detail::param1<czstring> BY;
    detail::param2<czint, czint> LIMIT;
    detail::param_repeat<czstring> GET;
    detail::param0 ASC;
    detail::param0 DESC;
    detail::param0 ALPHA;

public:
    sort_param() :
        BY("BY"),
        LIMIT("LIMIT"),
        GET("GET"),
        ASC("ASC"),
        DESC("DESC"),
        ALPHA("ALPHA")
    {}

    void set_BY(cref_string pattern)
    {
        BY.use = true;
        BY.value1 = pattern;
    }

    void set_LIMIT(czint offset, czint count) noexcept
    {
        LIMIT.use = true;
        LIMIT.value1 = offset;
        LIMIT.value2 = count;
    }

    void set_GET(cref_string_array patterns)
    {
        GET.use = true;
        GET.values = patterns;
    }

    void set_ASC() noexcept
    {
        ASC.use = true;
        DESC.use = false;
    }

    void set_DESC() noexcept
    {
        DESC.use = true;
        ASC.use = false;
    }

    void set_ALPHA() noexcept { ALPHA.use = true; }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            BY,
            LIMIT,
            GET,
            ASC,
            DESC,
            ALPHA
        );
    }
};

class zadd_param : public detail::param_templete
{
    detail::param0 NX;
    detail::param0 XX;
    detail::param0 CH;
    detail::param0 INCR;

public:
    zadd_param() :
        NX("NX"),
        XX("XX"),
        CH("CH"),
        INCR("INCR")
    {}

    void set_NX() noexcept
    {
        NX.use = true;
        XX.use = false;
    }

    void set_XX() noexcept
    {
        XX.use = true;
        NX.use = false;
    }

    void set_CH() noexcept { CH.use = true; }

    void set_INCR() noexcept { INCR.use = true; }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            NX,
            XX,
            CH,
            INCR
        );
    }
};

class zstore_param : public detail::param_templete
{
    detail::param_array<double> WEIGHTS;
    detail::param1<czstring> AGGREGATE;

public:
    zstore_param() :
        WEIGHTS(""),
        AGGREGATE("")
    {}

    void set_WEIGHTS(const std::vector<double> weights)
    {
        WEIGHTS.use = true;
        WEIGHTS.values = weights;
    }

    void set_AGGREGATE(aggregate value)
    {
        AGGREGATE.use = true;
        AGGREGATE.value1 = detail::aggregate_dict.at(value);
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            WEIGHTS,
            AGGREGATE
        );
    }
};

class xadd_param : public detail::param_templete
{
    detail::param1<czint> MAXLEN;
    detail::param0 ALMOST_EXACT;

public:
    xadd_param() :
        MAXLEN("MAXLEN"),
        ALMOST_EXACT("~")
    {}

    void set_MAXLEN(czint threshold, bool almost_exact = false) noexcept
    {
        MAXLEN.use = true;
        MAXLEN.value1 = threshold;
        ALMOST_EXACT.use = almost_exact;
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            MAXLEN,
            ALMOST_EXACT
        );
    }
};

class xclaim_param : public detail::param_templete
{
    detail::param1<czint> IDLE;
    detail::param1<czint> TIME;
    detail::param1<czint> RETRYCOUNT;
    detail::param0 FORCE;
    detail::param0 JUSTID;

public:
    xclaim_param() :
        IDLE("IDLE"),
        TIME("TIME"),
        RETRYCOUNT("RETRYCOUNT"),
        FORCE("FORCE"),
        JUSTID("JUSTID")
    {}

    void set_IDLE(czint ms) noexcept
    {
        IDLE.use = true;
        IDLE.value1 = ms;
    }

    void set_TIME(czint ms_unix_time) noexcept
    {
        IDLE.use = true;
        IDLE.value1 = ms_unix_time;
    }

    void set_RETRYCOUNT(czint count) noexcept
    {
        RETRYCOUNT.use = true;
        RETRYCOUNT.value1 = count;
    }

    void set_FORCE() noexcept { FORCE.use = true; }

    void set_JUSTID() noexcept { JUSTID.use = true; }

    bool is_justid() const noexcept { return JUSTID.use; }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            IDLE,
            TIME,
            RETRYCOUNT,
            FORCE,
            JUSTID
        );
    }
};

class xread_param : public detail::param_templete
{
    detail::param1<czint> COUNT;
    detail::param1<czint> BLOCK;

public:
    xread_param() :
        COUNT("COUNT"),
        BLOCK("BLOCK")
    {}

    void set_COUNT(czint count) noexcept
    {
        COUNT.use = true;
        COUNT.value1 = count;
    }

    void set_BLOCK(czint milliseconds) noexcept
    {
        BLOCK.use = true;
        BLOCK.value1 = milliseconds;
    }

    bool is_block() const noexcept { return BLOCK.use; }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            COUNT,
            BLOCK
        );
    }
};

class bitpos_param : public detail::param_templete
{
    string_array params_;
    detail::param1<czint> start_;
    detail::param1<czint> end_;

public:
    bitpos_param() :
        start_(""),
        end_("")
    {}

    void set_start(czint value) noexcept
    {
        start_.use = true;
        start_.value1 = value;
    }

    void set_end(czint value) noexcept
    {
        end_.use = true;
        end_.value1 = value;
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            start_,
            end_
        );
    }
};

class set_param : public detail::param_templete
{
    detail::param1<czint> EX;
    detail::param1<czint> PX;
    detail::param1<czint> EXAT;
    detail::param1<czint> PXAT;
    detail::param0 KEEPTTL;
    detail::param0 NX;
    detail::param0 XX;
    detail::param0 GET;

    void reset_EX_PX_EXAT_PXAT_KEEPTTL() noexcept
    {
        EX.use = false;
        PX.use = false;
        EXAT.use = false;
        PXAT.use = false;
        KEEPTTL.use = false;
    }

public:
    set_param():
        EX("EX"),
        PX("PX"),
        EXAT("EXAT"),
        PXAT("PXAT"),
        KEEPTTL("KEEPTTL"),
        NX("NX"),
        XX("XX"),
        GET("GET")
    {}

    void set_EX(czint seconds) noexcept
    {
        reset_EX_PX_EXAT_PXAT_KEEPTTL();
        EX.use = true;
        EX.value1 = seconds;
    }

    void set_PX(czint milliseconds) noexcept
    {
        reset_EX_PX_EXAT_PXAT_KEEPTTL();
        PX.use = true;
        PX.value1 = milliseconds;
    }

    void set_EXAT(czint timestamp) noexcept
    {
        reset_EX_PX_EXAT_PXAT_KEEPTTL();
        EXAT.use = true;
        EXAT.value1 = timestamp;
    }

    void set_PXAT(czint milliseconds_timestamp) noexcept
    {
        reset_EX_PX_EXAT_PXAT_KEEPTTL();
        PXAT.use = true;
        PXAT.value1 = milliseconds_timestamp;
    }

    void set_KEEPTTL() noexcept
    {
        reset_EX_PX_EXAT_PXAT_KEEPTTL();
        KEEPTTL.use = true;
    }

    void set_NX() noexcept
    {
        NX.use = true;
        XX.use = false;
    }

    void set_XX() noexcept
    {
        XX.use = true;
        NX.use = false;
    }

    void set_GET() noexcept
    {
        GET.use = true;
    }

    void append_params(string_array& cmd_params) const override
    {
        fill_up(cmd_params,
            EX,
            PX,
            EXAT,
            PXAT,
            KEEPTTL,
            NX,
            XX,
            GET
        );
    }
};

} // namespace czredis