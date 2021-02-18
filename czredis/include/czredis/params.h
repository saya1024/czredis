#pragma once

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

    void set_ASC() noexcept { ASC.use = true; }

    void set_DESC() noexcept { DESC.use = true; }

    virtual void append_params(string_array& params) const override
    {
        only_one_of_params(ASC, DESC);
        WITHCOORD.append_param(params);
        WITHDIST.append_param(params);
        WITHHASH.append_param(params);
        COUNT.append_param(params);
        ANY.append_param(params);
        ASC.append_param(params);
        DESC.append_param(params);
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

    virtual void append_params(string_array& params) const override
    {
        STORE.append_param(params);
        STOREDIST.append_param(params);
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

    virtual void append_params(string_array& params) const override
    {
        MATCH.append_param(params);
        COUNT.append_param(params);
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
    }

    void set_AUTH2(cref_string username, cref_string password)
    {
        AUTH2.use = true;
        AUTH2.value1 = username;
        AUTH2.value2 = password;
    }

    virtual void append_params(string_array& params) const override
    {
        detail::only_one_of_params(AUTH, AUTH2);
        COPY.append_param(params);
        REPLACE.append_param(params);
        AUTH.append_param(params);
        AUTH2.append_param(params);
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

    virtual void append_params(string_array& params) const override
    {
        REPLACE.append_param(params);
        ABSTTL.append_param(params);
        IDLETIME.append_param(params);
        FREQ.append_param(params);
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
    detail::param1<czstring> STORE;

public:
    sort_param() :
        BY("BY"),
        LIMIT("LIMIT"),
        GET("GET"),
        ASC("ASC"),
        DESC("DESC"),
        ALPHA("ALPHA"),
        STORE("STORE")
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

    void set_ASC() noexcept { ASC.use = true; }

    void set_DESC() noexcept { DESC.use = true; }

    void set_ALPHA() noexcept { ALPHA.use = true; }

    void set_STORE(cref_string destination)
    {
        STORE.use = true;
        STORE.value1 = destination;
    }

    virtual void append_params(string_array& params) const override
    {
        detail::only_one_of_params(ASC, DESC);
        BY.append_param(params);
        LIMIT.append_param(params);
        GET.append_param(params);
        ASC.append_param(params);
        DESC.append_param(params);
        ALPHA.append_param(params);
        STORE.append_param(params);
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

    void set_NX() noexcept { NX.use = true; }
    void set_XX() noexcept { XX.use = true; }
    void set_CH() noexcept { CH.use = true; }
    void set_INCR() noexcept { INCR.use = true; }

    virtual void append_params(string_array& params) const override
    {
        only_one_of_params(NX, XX);
        NX.append_param(params);
        XX.append_param(params);
        CH.append_param(params);
        INCR.append_param(params);
    }
};

class z_param : public detail::param_templete
{
    detail::param_array<double> WEIGHTS;
    detail::param1<czstring> AGGREGATE;

public:
    z_param() :
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

    virtual void append_params(string_array& params) const override
    {
        WEIGHTS.append_param(params);
        AGGREGATE.append_param(params);
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

    virtual void append_params(string_array& params) const override
    {
        MAXLEN.append_param(params);
        ALMOST_EXACT.append_param(params);
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

    virtual void append_params(string_array& params) const override
    {
        IDLE.append_param(params);
        TIME.append_param(params);
        RETRYCOUNT.append_param(params);
        FORCE.append_param(params);
        JUSTID.append_param(params);
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

    virtual void append_params(string_array& params) const override
    {
        COUNT.append_param(params);
        BLOCK.append_param(params);
    }
};

} // namespace czredis