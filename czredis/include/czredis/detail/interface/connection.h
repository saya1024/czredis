#pragma once

namespace czredis
{
namespace detail
{

struct i_connection
{
    virtual void auth(cref_string password) = 0;
    virtual void auth(cref_string username, cref_string password) = 0;
    virtual void echo(cref_string message) = 0;
    virtual void ping() = 0;
    virtual void quit() = 0;
    virtual void select(unsigned index) = 0;
};

struct i_direct_connection
{
    virtual czstring auth(cref_string password) = 0;
    virtual czstring auth(cref_string username, cref_string password) = 0;
    virtual czstring echo(cref_string message) = 0;
    virtual czstring ping() = 0;
    virtual czstring quit() = 0;
    virtual czstring select(unsigned index) = 0;
};

} // namespace detail
} // namespace czredis

