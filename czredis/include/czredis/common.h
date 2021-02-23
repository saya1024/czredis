#pragma once

#define ASIO_STANDALONE

#include <cassert>
#include <deque>
#include <exception>
#include <functional>
#include <list>
#include <map>
#include <mutex>
#include <regex>
#include <string>
#include <system_error>
#include <vector>
#include "../asio.hpp"

namespace czredis
{

using czstring = std::string;
using czint = std::int64_t;
using czbit = bool;

using string_array = std::vector<czstring>;
using string_map = std::map<czstring, czstring>;
using size_t = std::size_t;
using cref_string = const czstring&;
using cref_string_array = const string_array&;
using cref_string_map = const string_map&;

enum class reply_type { kNull, kInteger, kString, kArray, kError };
enum class redis_key_type { kNone, kString, kList, kSet, kZSet, kHash, kStream };
enum class geo_unit { kMeter, kKilometer, kMile, kFoot };
enum class insert_place { kBefore, kAfter };
enum class bit_operation { kAND, kOR, kNOT, kXOR };
enum class aggregate { kSUM, kMIN, kMAX };

namespace detail {

using asio::ip::tcp;

using byte = std::uint8_t;
using std::chrono::steady_clock;
using time_point = steady_clock::time_point;

const std::map<redis_key_type, czstring> redis_key_type_dict =
{
    {redis_key_type::kNone, "none"},
    {redis_key_type::kString, "string"},
    {redis_key_type::kList, "list"},
    {redis_key_type::kSet, "set"},
    {redis_key_type::kZSet, "zset"},
    {redis_key_type::kHash, "hash"},
    {redis_key_type::kStream, "stream"}
};

const std::map<geo_unit, czstring> geo_unit_dict =
{
    {geo_unit::kMeter, "m"},
    {geo_unit::kKilometer, "km"},
    {geo_unit::kMile, "mi"},
    {geo_unit::kFoot, "ft"}
};

const std::map<insert_place, czstring> insert_place_dict =
{
    {insert_place::kBefore, "BEFORE" },
    {insert_place::kAfter, "AFTER" }
};

const std::map<bit_operation, czstring> bit_operation_dict =
{
    {bit_operation::kAND, "AND"},
    {bit_operation::kOR, "OR"},
    {bit_operation::kNOT, "NOT"},
    {bit_operation::kXOR, "XOR"}
};

const std::map<aggregate, czstring> aggregate_dict =
{
    {aggregate::kSUM, "SUM"},
    {aggregate::kMAX, "MAX"},
    {aggregate::kMIN, "MIN"}
};

} // namespace detail
} // namespace czredis