#pragma once

namespace czredis
{
namespace detail
{

struct i_scripting
{
    virtual void eval(cref_string script, cref_string_array keys, cref_string_array args) = 0;
    virtual void evalsha(cref_string sha1, cref_string_array keys, cref_string_array args) = 0;
    virtual void script_exists(cref_string sha1) = 0;
    virtual void script_exists(cref_string_array sha1s) = 0;
    virtual void script_flush() = 0;
    virtual void script_kill() = 0;
    virtual void script_load(cref_string script) = 0;
};

struct i_direct_scripting
{
    virtual reply eval(cref_string script, cref_string_array keys, cref_string_array args) = 0;
    virtual reply evalsha(cref_string sha1, cref_string_array keys, cref_string_array args) = 0;
    virtual czint script_exists(cref_string sha1) = 0;
    virtual std::vector<czint> script_exists(cref_string_array sha1s) = 0;
    virtual czstring script_flush() = 0;
    virtual czstring script_kill() = 0;
    virtual czstring script_load(cref_string script) = 0;
};

struct i_delay_scripting
{
    virtual delay<reply> eval(cref_string script, cref_string_array keys, cref_string_array args) = 0;
    virtual delay<reply> evalsha(cref_string sha1, cref_string_array keys, cref_string_array args) = 0;
    virtual delay<czint> script_exists(cref_string sha1) = 0;
    virtual delay<std::vector<czint>> script_exists(cref_string_array sha1s) = 0;
    virtual delay<czstring> script_flush() = 0;
    virtual delay<czstring> script_kill() = 0;
    virtual delay<czstring> script_load(cref_string script) = 0;
};

} // namespace detail
} // namespace czredis

