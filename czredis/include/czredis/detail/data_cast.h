#pragma once

#include "../data.h"

namespace czredis
{
namespace detail
{
namespace
{

template<>
scan_result reply_cast(reply&& raw)
{
    return { std::move(raw.as_array()[0].as_string()),
        reply_cast<string_array>(std::move(raw.as_array()[1])) };
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
    for (auto& r : rarr)
    {
        auto& rarr2 = r.as_array();
        keys_entries.emplace(
            std::move(rarr2[0].as_string()),
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
    arr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        arr.emplace_back(reply_cast<reply_hmap>(std::move(r)));
    }
    return arr;
}

template<>
std::vector<stream_consumer_info> reply_cast(reply&& raw)
{
    std::vector<stream_consumer_info> arr;
    auto& rarr = raw.as_array();
    arr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        arr.emplace_back(reply_cast<reply_hmap>(std::move(r)));
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
    xarr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        xarr.emplace_back(std::move(r.as_array()));
    }
    return xarr;
}

template<>
std::vector<slowlog_reslut> reply_cast(reply&& raw)
{
    std::vector<slowlog_reslut> sarr;
    auto& rarr = raw.as_array();
    sarr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        sarr.emplace_back(std::move(r.as_array()));
    }
    return sarr;
}

template<>
std::vector<module_result> reply_cast(reply&& raw)
{
    std::vector<module_result> marr;
    auto& rarr = raw.as_array();
    marr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        marr.emplace_back(std::move(r.as_array()));
    }
    return marr;
}

template<>
unix_time_result reply_cast(reply&& raw)
{
    return unix_time_result(std::move(raw.as_array()));
}

string_array to_string_array(cref_stream_id_array ids)
{
    string_array sarr;
    sarr.reserve(ids.size());
    for (auto& id : ids)
    {
        sarr.emplace_back(id.to_string());
    }
    return sarr;
}

} // namespace anonymous
} // namespace detail
} // namespace czredis