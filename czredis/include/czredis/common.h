#pragma once

#define ASIO_STANDALONE

#include <cassert>
#include <exception>
#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <string>
#include <system_error>
#include <vector>
#include "../asio.hpp"

namespace czredis
{

using rds_string = std::string;
using rds_integer = std::int64_t;
using string_array = std::vector<rds_string>;
using string_map = std::map<rds_string, rds_string>;
using size_t = std::size_t;

enum class reply_type { kNull, kString, kInteger, kArray, kError };

namespace detail {

using asio::ip::tcp;
using byte = std::uint8_t;
using cref_string = const rds_string&;
using init_strings = std::initializer_list<rds_string>;

} // namespace detail
} // namespace czredis

#include "error.h"
#include "reply.h"

namespace czredis
{

using reply_array = std::vector<reply>;

} // namespace czredis