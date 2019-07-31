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

using czstring = std::string;
using czint = std::int64_t;
using czbit = std::uint8_t;

using string_array = std::vector<czstring>;
using string_map = std::map<czstring, czstring>;
using size_t = std::size_t;

enum class reply_type { kNull, kString, kInteger, kArray, kError };

namespace detail {

using asio::ip::tcp;
using byte = std::uint8_t;
using cref_string = const czstring&;
using init_string_list = std::initializer_list<czstring>;

} // namespace detail
} // namespace czredis

#include "error.h"
#include "reply.h"

namespace czredis
{

using reply_array = std::vector<reply>;

} // namespace czredis