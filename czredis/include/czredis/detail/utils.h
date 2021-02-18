#pragma once

namespace czredis
{
namespace detail
{

inline string_array
reply_array_to_string_array(reply_array&& rarr)
{
    string_array sarr;
    sarr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        sarr.emplace_back(std::move(r.as_string()));
    }
    return sarr;
}

inline std::vector<czint>
reply_array_to_integer_array(reply_array&& rarr)
{
    std::vector<czint> iarr;
    iarr.reserve(rarr.size());
    for (auto& r : rarr)
    {
        iarr.emplace_back(r.as_integer());
    }
    return iarr;
}

inline string_map
reply_array_to_string_map(reply_array&& rarr)
{
    string_map smap;
    for (auto it = rarr.begin(); it != rarr.end();)
    {
        smap[it->as_string()] = (it + 1)->as_string();
        it += 2;
    }
    return smap;
}

inline reply_map
reply_array_to_reply_map(reply_array&& rarr)
{
    reply_map rmap;
    for (auto it = rarr.begin(); it != rarr.end();)
    {
        rmap[it->as_string()] = *(it + 1);
        it += 2;
    }
    return rmap;
}

inline scan_result
reply_array_to_scan_result(reply_array&& rarr)
{
    scan_result sr = { std::move(rarr.front().as_string()),
        reply_array_to_string_array(std::move(rarr.back().as_array())) };
    return sr;
}

inline string_array
stream_id_array_to_string_array(cref_stream_id_array idarr)
{
    string_array sarr;
    sarr.reserve(idarr.size());
    for (auto& id : idarr)
    {
        sarr.emplace_back(id.to_string());
    }
    return sarr;
}

inline std::map<czstring, stream_entries>
reply_array_to_stream_entries_map(reply_array&& rarr)
{
    std::map<czstring, stream_entries> key_entries;
    for (auto& r : rarr)
    {
        auto& key = r.as_array().front().as_string();
        auto& entries = r.as_array().back().as_array();
        key_entries[key] = std::move(entries);
    }
    return key_entries;
}

} // namespace detail
} // namespace czredis