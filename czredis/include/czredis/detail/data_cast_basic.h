#pragma once

#include "../reply.h"

namespace czredis
{
namespace detail
{
namespace
{

template<typename T>
T reply_cast(reply&& raw)
{
    throw redis_data_error("no cast function");
}

template<>
reply reply_cast(reply&& raw)
{
    if (raw.is_error())
        throw redis_commmand_error(raw.as_error());
    return std::move(raw);
}

template<>
czint reply_cast(reply&& raw)
{
    return raw.as_integer();
}

template<>
double reply_cast(reply&& raw)
{
    return std::stod(raw.as_string());
}

template<>
czstring reply_cast(reply&& raw)
{
    return std::move(raw.as_string());
}

template<>
reply_array reply_cast(reply&& raw)
{
    if (raw.is_null())
        return reply_array();
    return std::move(raw.as_array());
}

template<>
string_array reply_cast(reply&& raw)
{
    string_array result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    result.reserve(rarr.size());
    for (auto& r : rarr)
    {
        result.emplace_back(std::move(r.as_string()));
    }
    return result;
}

template<>
string_tmap reply_cast(reply&& raw)
{
    string_tmap result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    for (size_t i = 0; i < length;)
    {
        result.emplace(
            std::move(rarr[i].as_string()),
            std::move(rarr[i + 1].as_string()));
        i += 2;
    }
    return result;
}

template<>
std::vector<czint> reply_cast(reply&& raw)
{
    std::vector<czint> result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    result.reserve(rarr.size());
    for (auto& r : rarr)
    {
        result.emplace_back(r.as_integer());
    }
    return result;
}

template<>
reply_tmap reply_cast(reply&& raw)
{
    reply_tmap result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    for (size_t i = 0; i < length;)
    {
        result.emplace(
            std::move(rarr[i].as_string()),
            std::move(rarr[i + 1]));
        i += 2;
    }
    return result;
}

} // namespace anonymous
} // namespace detail
} // namespace czredis