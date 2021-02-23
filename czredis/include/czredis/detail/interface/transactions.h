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

} // namespace detail
} // namespace czredis

