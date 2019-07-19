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
type kAuth      = "AUTH\r\n";
type kEcho      = "ECHO\r\n";
type kPing      = "PING\r\n";
type kQuit      = "QUIT\r\n";
type kSelect    = "SELECT\r\n";
}

}

} // namespace detail
} // namespace czredis