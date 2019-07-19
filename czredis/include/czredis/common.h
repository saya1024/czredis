#pragma once

#define ASIO_STANDALONE

#include <cassert>
#include <exception>
#include <functional>
#include <map>
#include <mutex>
#include <list>
#include <string>
#include <vector>
#include "../asio.hpp"

namespace czredis
{

using rds_string = std::string;
using rds_integer = std::int64_t;
using string_array = std::vector<std::string>;
using string_map = std::map<std::string, std::string>;
using size_t = std::size_t;

enum class reply_type { kNull, kString, kInteger, kArray, kError };

namespace detail {

using asio::ip::tcp;
using byte = std::uint8_t;

} // namespace detail
} // namespace czredis

#include "error.h"
#include "reply.h"

namespace czredis
{

using reply_array = std::vector<reply>;

} // namespace czredis