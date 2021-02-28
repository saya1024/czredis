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
    return std::move(raw.as_array());
}

template<>
string_array reply_cast(reply&& raw)
{
    string_array sarr;
    auto& rarr = raw.as_array();
    sarr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        sarr.emplace_back(std::move(r.as_string()));
    }
    return sarr;
}

template<>
string_hmap reply_cast(reply&& raw)
{
    string_hmap smap;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    for (size_t i = 0; i < length;)
    {
        smap.emplace(
            std::move(rarr[i].as_string()),
            std::move(rarr[i + 1].as_string()));
        i += 2;
    }
    return smap;
}

template<>
std::vector<czint> reply_cast(reply&& raw)
{
    std::vector<czint> iarr;
    auto& rarr = raw.as_array();
    iarr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        iarr.emplace_back(r.as_integer());
    }
    return iarr;
}

template<>
reply_hmap reply_cast(reply&& raw)
{
    reply_hmap rmap;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    for (size_t i = 0; i < length;)
    {
        rmap.emplace(
            std::move(rarr[i].as_string()),
            std::move(rarr[i + 1]));
        i += 2;
    }
    return rmap;
}

} // namespace anonymous
} // namespace detail
} // namespace czredis