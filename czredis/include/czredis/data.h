#pragma once

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

    /*scan_result(reply_array&& rarr) :
        cursor(std::move(rarr.front().as_string())),
        results(detail::reply_array_to_string_array(std::move(rarr.back().as_array())))
    {
    }*/
};

class stream_id
{
public:
    static constexpr char kNew[] = "*";
    static constexpr char kLast[] = "$";
    static constexpr char kUnreceived[] = ">";
    static constexpr char kSmallest[] = "-";
    static constexpr char kGreatest[] = "-";

    stream_id() :
        time_(0), sequence_(0)
    {}

    stream_id(czint time, czint sequence) :
        time_(time), sequence_(sequence)
    {}

    stream_id(cref_string id)
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

private:
    czint time_;
    czint sequence_;
};

using cref_stream_id = const stream_id&;
using stream_id_array = std::vector<stream_id>;
using cref_stream_id_array = const stream_id_array&;

struct stream_entry 
{
    stream_id id;
    string_map field_value_map;

    stream_entry()
    {}

    stream_entry(const reply_array& rarr) :
        id(rarr.front().as_string())
    {
        auto& fields=rarr.back().as_array();
        for (auto it = fields.begin(); it != fields.end();)
        {
            field_value_map[it->as_string()] = (it + 1)->as_string();
            it += 2;
        }
    }

    stream_entry(const stream_entry& that) :
        id(that.id),
        field_value_map(that.field_value_map)
    {}

    stream_entry(stream_entry&& that) noexcept :
        id(std::move(that.id)),
        field_value_map(std::move(that.field_value_map))
    {}

    stream_entry& operator=(const stream_entry& that)
    {
        id = that.id;
        field_value_map = that.field_value_map;
        return *this;
    }

    stream_entry& operator=(stream_entry&& that) noexcept
    {
        id = std::move(that.id);
        field_value_map = std::move(that.field_value_map);
        return *this;
    }
};

class stream_entries
{
public:
    using iterator = detail::v2_iterator<stream_id, string_map>;

    stream_entries()
    {}

    stream_entries(reply_array&& rarr)
    {
        for (auto& r : rarr)
        {
            if (r.is_string())
            {
                ids_.emplace_back(r.as_string());
                messages_.emplace_back(string_map());
            }
            else if (r.is_array())
            {
                ids_.emplace_back(r.as_array().front().as_string());
                auto& fields = r.as_array().back().as_array();
                string_map msg;
                for (auto it = fields.begin(); it != fields.end();)
                {
                    msg[std::move(it->as_string())] =
                        std::move((it + 1)->as_string());
                    it += 2;
                }
                messages_.emplace_back(std::move(msg));
            }
        }
    }

    stream_entries(const stream_entries& sm) :
        ids_(sm.ids_),
        messages_(sm.messages_)
    {}

    stream_entries(stream_entries&& sm) noexcept :
        ids_(std::move(sm.ids_)),
        messages_(std::move(sm.messages_))
    {}

    stream_entries& operator=(const stream_entries& sm)
    {
        ids_ = sm.ids_;
        messages_ = sm.messages_;
        return *this;
    }

    stream_entries& operator=(stream_entries&& sm) noexcept
    {
        ids_ = std::move(sm.ids_);
        messages_ = std::move(sm.messages_);
        return *this;
    }

    void push_back(cref_stream_id id, cref_string_map message)
    {
        ids_.emplace_back(id);
        messages_.emplace_back(message);
    }

    void push_back(cref_stream_id id, string_map&& message)
    {
        ids_.emplace_back(id);
        messages_.emplace_back(message);
    }

    size_t size() const noexcept { return ids_.size(); }

    stream_id_array& get_ids() noexcept { return ids_; }

    std::vector<string_map> get_messages() noexcept { return messages_; }

    std::pair<stream_id&, string_map&> operator[](size_t i) noexcept
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

private:
    stream_id_array ids_;
    std::vector<string_map> messages_;
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
    reply_map raw_info;

    stream_info(reply_map&& rmap) :
        length(rmap[kLength].as_integer()),
        redix_tree_keys(rmap[kRedixTreeKeys].as_integer()),
        redix_tree_nodes(rmap[kRedixTreeNodes].as_integer()),
        last_generated_id(rmap[kLastGeneratedID].as_string()),
        groups(rmap[kGroups].as_integer()),
        first_entry(rmap[kFirstEntry].as_array()),
        last_entry(rmap[kLastEntry].as_array())
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
    reply_map raw_info;

    stream_group_info(reply_map&& rmap) :
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
    reply_map raw_info;

    stream_consumer_info(reply_map&& rmap) :
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
    std::map<czstring, czint> consumer_pending;

    xpending_overall_result(reply_array&& rarr) :
        total_pending_message(rarr[0].as_integer()),
        smallest_id(rarr[1].as_string()),
        greatest_id(rarr[2].as_string())
    {
        for (auto& r : rarr[3].as_array())
        {
            auto& consumer = r.as_array();
            consumer_pending[consumer.front().as_string()] =
                consumer.back().as_integer();
        }
    }
};

struct xpending_result
{
    stream_id id;
    czstring consumer;
    czint idle_time;
    czint delivered_times;

    xpending_result(const reply_array& rarr) :
        id(rarr[0].as_string()),
        consumer(rarr[1].as_string()),
        idle_time(rarr[2].as_integer()),
        delivered_times(rarr[3].as_integer())
    {}
};

} // namespace czredis