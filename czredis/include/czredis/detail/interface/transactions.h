#pragma once

namespace czredis
{
namespace detail
{

struct i_transactions
{
    virtual void discard() = 0;
    virtual void exec() = 0;
    virtual void multi() = 0;
    virtual void unwatch() = 0;
    virtual void watch(cref_string_array keys) = 0;
};

struct i_delay_transactions
{
    virtual delay<czstring> discard() = 0;
    virtual delay<reply> exec() = 0;
    virtual delay<czstring> multi() = 0;
    virtual delay<czstring> unwatch() = 0;
    virtual delay<czstring> watch(cref_string_array keys) = 0;
};

} // namespace detail
} // namespace czredis

