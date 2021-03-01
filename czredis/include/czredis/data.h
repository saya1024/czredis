#pragma once

#include "detail/data_cast_basic.h"
#include "detail/iterator.h"

namespace czredis
{

struct geo_coordinate
{
    double longitude;
    double latitude;

    constexpr bool equal(const geo_coordinate& that) noexcept
    {
        return (longitude == that.longitude) &&
            (latitude == that.latitude);
    }
};

struct scan_result
{
    czstring cursor;
    string_array results;
};

class stream_id
{
    czint time_;
    czint sequence_;

public:
    static constexpr char kNew[] = "*";
    static constexpr char kLast[] = "$";
    static constexpr char kUnreceived[] = ">";
    static constexpr char kSmallest[] = "-";
    static constexpr char kGreatest[] = "-";

    explicit stream_id() :
        time_(0), sequence_(0)
    {}

    explicit stream_id(czint time, czint sequence) :
        time_(time), sequence_(sequence)
    {}

    explicit stream_id(cref_string id)
    {
        time_ = std::stoll(id);
        auto pos = id.find('-');
        if (pos == id.npos)
            sequence_ = 0;
        else
            sequence_= std::stoll(id.c_str() + pos + 1);
    }

    czstring to_string() const
    {
        return std::to_string(time_) + "-" + std::to_string(sequence_);
    }

    int compare(stream_id that) const noexcept
    {
        if (time_ > that.time_)
            return 1;
        if (time_ < that.time_)
            return -1;
        if (sequence_ > that.sequence_)
            return 1;
        if (sequence_ < that.sequence_)
            return -1;
        return 0;
    }

    bool equal(stream_id that) { return compare(that) == 0; }

    czint get_time() const noexcept { return time_; }

    czint get_sequence()const noexcept { return sequence_; }
};

using cref_stream_id = const stream_id&;
using stream_id_array = std::vector<stream_id>;
using cref_stream_id_array = const stream_id_array&;

struct stream_entry 
{
    stream_id id;
    string_tmap fields_values;

    explicit stream_entry()
    {}

    explicit stream_entry(reply_array&& rarr) :
        id(rarr[0].as_string()),
        fields_values(detail::reply_cast<string_tmap>(std::move(rarr[1])))
    {}
};

class stream_entries
{
    stream_id_array ids_;
    std::vector<string_tmap> messages_;

public:
    using iterator = detail::v2_iterator<stream_id, string_tmap>;

    explicit stream_entries()
    {}

    explicit stream_entries(reply_array&& rarr)
    {
        for (auto& r : rarr)
        {
            if (r.is_string())
            {
                ids_.emplace_back(std::move(r.as_string()));
                messages_.emplace_back(string_tmap());
            }
            else if (r.is_array())
            {
                auto& rarr2 = r.as_array();
                ids_.emplace_back(rarr2[0].as_string());
                messages_.emplace_back(
                    detail::reply_cast<string_tmap>(std::move(rarr2[1])));
            }
        }
    }

    size_t size() const noexcept { return ids_.size(); }

    stream_id_array& get_ids() noexcept { return ids_; }

    std::vector<string_tmap> get_messages() noexcept { return messages_; }

    std::pair<stream_id&, string_tmap&> operator[](size_t i)
    {
        return { ids_[i], messages_[i] };
    }

    iterator begin() noexcept
    {
        return iterator(ids_.begin(), messages_.begin());
    }

    iterator end() noexcept
    {
        return iterator(ids_.end(), messages_.end());
    }
};

struct stream_info 
{
    static constexpr char kLength[] = "length";
    static constexpr char kRedixTreeKeys[] = "radix-tree-keys";
    static constexpr char kRedixTreeNodes[] = "radix-tree-nodes";
    static constexpr char kLastGeneratedID[] = "last-generated-id";
    static constexpr char kGroups[] = "groups";
    static constexpr char kFirstEntry[] = "first-entry";
    static constexpr char kLastEntry[] = "last-entry";

    czint length;
    czint redix_tree_keys;
    czint redix_tree_nodes;
    stream_id last_generated_id;
    czint groups;
    stream_entry first_entry;
    stream_entry last_entry;
    reply_tmap raw_info;

    explicit stream_info() :
        length(0),
        redix_tree_keys(0),
        redix_tree_nodes(0),
        groups(0)
    {}

    explicit stream_info(reply_tmap&& rmap) :
        length(rmap[kLength].as_integer()),
        redix_tree_keys(rmap[kRedixTreeKeys].as_integer()),
        redix_tree_nodes(rmap[kRedixTreeNodes].as_integer()),
        last_generated_id(rmap[kLastGeneratedID].as_string()),
        groups(rmap[kGroups].as_integer()),
        first_entry(std::move(rmap[kFirstEntry].as_array())),
        last_entry(std::move(rmap[kLastEntry].as_array()))
    {
        raw_info = std::move(rmap);
    }
};

struct stream_group_info 
{
    static constexpr char kName[] = "name";
    static constexpr char kConsumers[] = "consumers";
    static constexpr char kPending[] = "pending";
    static constexpr char kLastDeliveredID[] = "last-delivered-id";

    czstring name;
    czstring consumers;
    czstring pending;
    czstring last_delivered_id;
    reply_tmap raw_info;

    explicit stream_group_info()
    {}

    explicit stream_group_info(reply_tmap&& rmap) :
        name(rmap[kName].as_string()),
        consumers(rmap[kConsumers].as_string()),
        pending(rmap[kPending].as_string()),
        last_delivered_id(rmap[kPending].as_string())
    {
        raw_info = std::move(rmap);
    }
};

struct stream_consumer_info 
{
    static constexpr char kName[] = "name";
    static constexpr char kIdle[] = "idle";
    static constexpr char kPending[] = "pending";

    czstring name;
    czstring idle;
    czstring pending;
    reply_tmap raw_info;

    explicit stream_consumer_info()
    {}

    explicit stream_consumer_info(reply_tmap&& rmap) :
        name(rmap[kName].as_string()),
        idle(rmap[kIdle].as_string()),
        pending(rmap[kPending].as_string())
    {
        raw_info = std::move(rmap);
    }
};

struct xpending_overall_result
{
    czint total_pending_message;
    stream_id smallest_id;
    stream_id greatest_id;
    tmap<czstring, czint> consumer_pending;

    explicit xpending_overall_result() :
        total_pending_message(0)
    {}

    explicit xpending_overall_result(reply_array&& rarr) :
        total_pending_message(rarr[0].as_integer()),
        smallest_id(rarr[1].as_string()),
        greatest_id(rarr[2].as_string())
    {
        auto& consumer_arr = rarr[3].as_array();
        auto length = consumer_arr.size();
        for (size_t i = 0; i < length; i++)
        {
            auto& consumer = consumer_arr[i].as_array();
            consumer_pending[consumer[0].as_string()] =
                consumer[1].as_integer();
        }
    }
};

struct xpending_result
{
    stream_id id;
    czstring consumer;
    czint idle_time;
    czint delivered_times;

    explicit xpending_result() :
        idle_time(0),
        delivered_times(0)
    {}

    explicit xpending_result(reply_array&& rarr) :
        id(rarr[0].as_string()),
        consumer(rarr[1].as_string()),
        idle_time(rarr[2].as_integer()),
        delivered_times(rarr[3].as_integer())
    {}
};

struct slowlog_reslut
{
    czint id;
    czint timestamp;
    czint execution_time;
    string_array args;
    czstring client_ip_port;
    czstring client_name;

    explicit slowlog_reslut() :
        id(0),
        timestamp(0),
        execution_time(0)
    {}

    explicit slowlog_reslut(reply_array&& rarr) :
        id(rarr[0].as_integer()),
        timestamp(rarr[1].as_integer()),
        execution_time(rarr[2].as_integer()),
        args(detail::reply_cast<string_array>(std::move(rarr[3])))
    {
        if (rarr.size() > 4)
        {
            client_ip_port = rarr[4].as_string();
            client_name = rarr[5].as_string();
        }
    }
};

struct module_result
{
    czstring name;
    czint version;

    explicit module_result() :
        version(0)
    {}

    explicit module_result(reply_array&& rarr) :
        name(rarr[0].as_string()),
        version(rarr[1].as_integer())
    {}
};

struct unix_time_result
{
    czint seconds;
    czint microseconds;

    explicit unix_time_result() :
        seconds(0),
        microseconds(0)
    {}

    explicit unix_time_result(reply_array&& rarr) :
        seconds(std::stoll(rarr[0].as_string())),
        microseconds(std::stoll(rarr[0].as_string()))
    {}
};

} // namespace czredis