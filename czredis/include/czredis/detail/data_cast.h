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
    if (raw.is_null())
        return stream_entries();
    return stream_entries(std::move(raw.as_array()));
}

template<>
tmap<czstring, stream_entries> reply_cast(reply&& raw)
{
    tmap<czstring, stream_entries> result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    for (auto& r : rarr)
    {
        auto& rarr2 = r.as_array();
        result.emplace(
            std::move(rarr2[0].as_string()),
            std::move(rarr2[1].as_array()));
    }
    return result;
}

template<>
stream_info reply_cast(reply&& raw)
{
    return stream_info(reply_cast<reply_tmap>(std::move(raw)));
}

template<>
std::vector<stream_group_info> reply_cast(reply&& raw)
{
    std::vector<stream_group_info> result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    result.reserve(rarr.size());
    for (auto& r : rarr)
    {
        result.emplace_back(reply_cast<reply_tmap>(std::move(r)));
    }
    return result;
}

template<>
std::vector<stream_consumer_info> reply_cast(reply&& raw)
{
    std::vector<stream_consumer_info> result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    result.reserve(rarr.size());
    for (auto& r : rarr)
    {
        result.emplace_back(reply_cast<reply_tmap>(std::move(r)));
    }
    return result;
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
    std::vector<xpending_result> result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    result.reserve(rarr.size());
    for (auto& r : rarr)
    {
        result.emplace_back(std::move(r.as_array()));
    }
    return result;
}

template<>
std::vector<slowlog_reslut> reply_cast(reply&& raw)
{
    std::vector<slowlog_reslut> result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    result.reserve(rarr.size());
    for (auto& r : rarr)
    {
        result.emplace_back(std::move(r.as_array()));
    }
    return result;
}

template<>
std::vector<module_result> reply_cast(reply&& raw)
{
    std::vector<module_result> result;
    if (raw.is_null())
        return result;
    auto& rarr = raw.as_array();
    result.reserve(rarr.size());
    for (auto& r : rarr)
    {
        result.emplace_back(std::move(r.as_array()));
    }
    return result;
}

template<>
unix_time_result reply_cast(reply&& raw)
{
    return unix_time_result(std::move(raw.as_array()));
}

string_array to_string_array(cref_stream_id_array ids)
{
    string_array result;
    result.reserve(ids.size());
    for (auto& id : ids)
    {
        result.emplace_back(id.to_string());
    }
    return result;
}

} // namespace anonymous
} // namespace detail
} // namespace czredis