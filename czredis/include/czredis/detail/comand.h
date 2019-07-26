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
type kAuth      = "AUTH";
type kEcho      = "ECHO";
type kPing      = "PING";
type kQuit      = "QUIT";
type kSelect    = "SELECT";
}

namespace transaction
{
type kDiscard   = "DISCARD";
type kExec      = "EXEC";
type kMulti     = "MULTI";
type kUnwatch   = "UNWATCH";
type kWatch     = "WATCH";
}

} // namespace cmd

struct command_interface
{
    virtual void auth(cref_string password) = 0;
    virtual void echo(cref_string message) = 0;
    virtual void ping() = 0;
    virtual void quit() = 0;
    virtual void select(unsigned db) = 0;


    virtual void discard() = 0;
    virtual void exec() = 0;
    virtual void multi() = 0;
    virtual void unwatch() = 0;
    virtual void watch(init_strings keys) = 0;
};

} // namespace detail
} // namespace czredis