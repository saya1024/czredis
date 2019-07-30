#pragma once

#include "../common.h"

namespace czredis
{
namespace detail
{

namespace cmd
{

using type = const std::string;

namespace connection
{
type AUTH       = "AUTH";
type ECHO       = "ECHO";
type PING       = "PING";
type QUIT       = "QUIT";
type SELECT     = "SELECT";
}

namespace string
{
type APPEND     = "APPEND";
type BITCOUNT   = "BITCOUNT";
type BITOP      = "BITOP";
type DECR       = "DECR";
type DECRBY     = "DECRBY";
type GET        = "GET";
type GETBIT     = "GETBIT";
type GETRANGE   = "GETRANGE";
type GETSET     = "GETSET";
type INCR       = "INCR";
type INCRBY     = "INCRBY";
type INCRBYFLOAT = "INCRBYFLOAT";
type MGET       = "MGET";
type MSET       = "MSET";
type MSETNX     = "MSETNX";
type PSETEX     = "PSETEX";
type SET        = "SET";
type SETBIT     = "SETBIT";
type SETEX      = "SETEX";
type SETNX      = "SETNX";
type SETRANGE   = "SETRANGE";
type STRLEN     = "STRLEN";
}

namespace transaction
{
type DISCARD    = "DISCARD";
type EXEC       = "EXEC";
type MULTI      = "MULTI";
type UNWATCH    = "UNWATCH";
type WATCH      = "WATCH";
}

} // namespace cmd

struct command_interface
{
    virtual void auth(cref_string password) = 0;
    virtual void echo(cref_string message) = 0;
    virtual void ping() = 0;
    virtual void quit() = 0;
    virtual void select(unsigned db) = 0;

    virtual void append(cref_string key, cref_string value) = 0;
    virtual void bitcount(cref_string key, rds_integer start, rds_integer end) = 0;
    virtual void bitop(cref_string operation, cref_string dest_key, init_strings keys) = 0;
    virtual void decr(cref_string key) = 0;
    virtual void decrby(cref_string key, rds_integer decrement) = 0;
    virtual void get(cref_string key) = 0;
    virtual void getbit(cref_string key, rds_integer offset) = 0;
    virtual void getrange(cref_string key, rds_integer start, rds_integer end) = 0;
    virtual void getset(cref_string key, cref_string value) = 0;
    virtual void incr(cref_string key) = 0;
    virtual void incrby(cref_string key, rds_integer increment) = 0;
    virtual void incrbyfloat(cref_string key, double increment) = 0;
    virtual void mget(init_strings keys) = 0;
    virtual void mset(init_strings key_value_pairs) = 0;
    virtual void msetnx(init_strings key_value_pairs) = 0;
    virtual void psetex(cref_string key, rds_integer milliseconds, cref_string value) = 0;
    virtual void set(cref_string key, cref_string value, init_strings params) = 0;
    virtual void setbit(cref_string key, rds_integer offset, bool value) = 0;
    virtual void setex(cref_string key, rds_integer seconds, cref_string value) = 0;
    virtual void setnx(cref_string key, cref_string value) = 0;
    virtual void setrange(cref_string key, rds_integer offset, cref_string value) = 0;
    virtual void strlen(cref_string key) = 0;


    virtual void discard() = 0;
    virtual void exec() = 0;
    virtual void multi() = 0;
    virtual void unwatch() = 0;
    virtual void watch(init_strings keys) = 0;
};

} // namespace detail
} // namespace czredis