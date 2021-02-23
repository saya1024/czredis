#pragma once

#include "../delay.h"

namespace czredis
{
namespace detail
{

class delay_queue : private move_only
{
    std::deque<std::shared_ptr<delay_slot>> pslots_;

protected:
    void delay_queue_clear() noexcept
    {
        pslots_.clear();
    }

    bool delay_queue_empty() const noexcept
    {
        return pslots_.empty();
    }

    size_t delay_queue_size() const noexcept
    {
        return pslots_.size();
    }

    template<typename T>
    delay<T> make_delay()
    {
        delay<T> d;
        pslots_.emplace_back(d.pslot_);
        return d;
    }

    void build_delay(reply&& r)
    {
        auto& pslot = pslots_.front();
        pslot->r = std::move(r);
        pslot->set = true;
        pslots_.pop_front();
    }

    void build_all_delay(reply_array&& rarr)
    {
        auto length = rarr.size();
        for (size_t i = 0; i < length; i++)
        {
            build_delay(std::move(rarr[i]));
        }
    }
};

} // namespace detail
} // namespace czredis