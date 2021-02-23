#pragma once

namespace czredis
{
namespace detail
{

struct i_hyper_log_log
{
    virtual void pfadd(cref_string key, cref_string_array elements) = 0;
    virtual void pfcount(cref_string key) = 0;
    virtual void pfcount(cref_string_array keys) = 0;
    virtual void pfmerge(cref_string destkey, cref_string_array sourcekeys) = 0;
};

struct i_one_key_direct_hyper_log_log
{
    virtual czint pfadd(cref_string key, cref_string_array elements) = 0;
    virtual czint pfcount(cref_string key) = 0;
};

struct i_direct_hyper_log_log
{
    virtual czint pfcount(cref_string_array keys) = 0;
    virtual czstring pfmerge(cref_string destkey, cref_string_array sourcekeys) = 0;
};

struct i_one_key_delay_hyper_log_log
{
    virtual delay<czint> pfadd(cref_string key, cref_string_array elements) = 0;
    virtual delay<czint> pfcount(cref_string key) = 0;
};

struct i_delay_hyper_log_log
{
    virtual delay<czint> pfcount(cref_string_array keys) = 0;
    virtual delay<czstring> pfmerge(cref_string destkey, cref_string_array sourcekeys) = 0;
};

} // namespace detail
} // namespace czredis

