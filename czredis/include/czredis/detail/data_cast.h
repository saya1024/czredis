#pragma once

#include "../data.h"

namespace czredis
{
namespace detail
{

template<typename T>
T reply_cast(reply&& raw)
{
    throw redis_data_error("no convert function");
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
    auto length = rarr.size();
    sarr.reserve(length);
    for (size_t i = 0; i < length; i++)
    {
        sarr.emplace_back(std::move(rarr[i].as_string()));
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
        smap[rarr[i].as_string()] = rarr[i + 1].as_string();
        i += 2;
    }
    return smap;
}

template<>
std::vector<czint> reply_cast(reply&& raw)
{
    std::vector<czint> iarr;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    iarr.reserve(length);
    for (size_t i = 0; i < length; i++)
    {
        iarr.emplace_back(rarr[i].as_integer());
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
        rmap[rarr[i].as_string()] = std::move(rarr[i + 1]);
        i += 2;
    }
    return rmap;
}

template<>
scan_result reply_cast(reply&& raw)
{
    scan_result sr = { std::move(raw.as_array()[0].as_string()),
        reply_cast<string_array>(std::move(raw.as_array()[1])) };
    return sr;
}

template<>
stream_id reply_cast(reply&& raw)
{
    return stream_id(raw.as_string());
}

template<>
stream_entry reply_cast(reply&& raw)
{
    return stream_entry(std::move(raw.as_array()));
}

template<>
stream_entries reply_cast(reply&& raw)
{
    return stream_entries(std::move(raw.as_array()));
}

template<>
std::pair<czstring, stream_entries> reply_cast(reply&& raw)
{
    auto& rarr = raw.as_array()[0].as_array();
    return std::pair<czstring, stream_entries>(
        std::move(rarr[0].as_string()),
        std::move(rarr[1].as_array()));
}

template<>
hmap<czstring, stream_entries> reply_cast(reply&& raw)
{
    hmap<czstring, stream_entries> keys_entries;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    for (size_t i = 0; i < length; i++)
    {
        auto& rarr2 = rarr[i].as_array();
        keys_entries.emplace(rarr2[0].as_string(),
            std::move(rarr2[1].as_array()));
    }
    return keys_entries;
}

template<>
stream_info reply_cast(reply&& raw)
{
    return stream_info(reply_cast<reply_hmap>(std::move(raw)));
}

template<>
std::vector<stream_group_info> reply_cast(reply&& raw)
{
    std::vector<stream_group_info> arr;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    arr.reserve(length);
    for (size_t i = 0; i < length; i++)
    {
        arr.emplace_back(reply_cast<reply_hmap>(std::move(rarr[i])));
    }
    return arr;
}

template<>
std::vector<stream_consumer_info> reply_cast(reply&& raw)
{
    std::vector<stream_consumer_info> arr;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    arr.reserve(length);
    for (size_t i = 0; i < length; i++)
    {
        arr.emplace_back(reply_cast<reply_hmap>(std::move(rarr[i])));
    }
    return arr;
}

template<>
xpending_overall_result reply_cast(reply&& raw)
{
    return xpending_overall_result(
        reply_cast<reply_array>(std::move(raw)));
}

template<>
std::vector<xpending_result> reply_cast(reply&& raw)
{
    std::vector<xpending_result> xarr;
    auto& rarr = raw.as_array();
    auto length = rarr.size();
    xarr.reserve(length);
    for (size_t i = 0; i < length; i++)
    {
        xarr.emplace_back(rarr[i].as_array());
    }
    return xarr;
}

inline string_array
to_string_array(cref_stream_id_array ids)
{
    string_array sarr;
    auto length = ids.size();
    sarr.reserve(length);
    for (size_t i = 0; i < length; i++)
    {
        sarr.emplace_back(ids[i].to_string());
    }
    return sarr;
}

} // namespace detail
} // namespace czredis