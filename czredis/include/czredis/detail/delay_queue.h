#pragma once

#include "../delay.h"

namespace czredis
{
namespace detail
{

class delay_queue : private move_only
{
    using slot_pointer = std::shared_ptr<delay_slot>;
    std::deque<slot_pointer> pslots_;
    std::deque<slot_pointer> pslots_multi_;

    bool multi_mode = false;

protected:
    void delay_queue_clean_state() noexcept
    {
        pslots_.clear();
        pslots_multi_.clear();
        multi_mode = false;
    }

    template<typename T>
    delay<T> make_delay(bool multi)
    {
        delay<T> d;
        d.pslot_->multi = multi;
        pslots_.emplace_back(d.pslot_);
        return d;
    }

    void build_slot(slot_pointer& pslot, reply& r)
    {
        pslot->r = std::move(r);
        pslot->set = true;
    }

    void build_multi(slot_pointer& pslot, reply& r)
    {
        if (r.is_string())
        {
            if (r.as_string() == keyword::QUEUED)
            {
                pslots_multi_.emplace_back(pslot);
            }
            else if (r.as_string() == keyword::OK) // discard
            {
                while (!pslots_multi_.empty())
                {
                    pslots_multi_.front()->multi_discard = true;
                    pslots_multi_.pop_front();
                }
                build_slot(pslot, r);
            }
            else
            {
                delay_queue_clean_state();
                throw redis_data_error("build delay failed");
            }
        }
        else if (r.is_array()) // exec result
        {
            auto& rarr = r.as_array();
            size_t i = 0;
            while (!pslots_multi_.empty())
            {
                pslots_multi_.front()->r = rarr[i]; // copy reply
                pslots_multi_.front()->set = true;
                pslots_multi_.pop_front();
                i++;
            }
            build_slot(pslot, r);
            multi_mode = false;
        }
        else if (r.is_error())
        {
            if (r.as_error().find(keyword::EXECABORT) != std::string::npos) // exec abort
            {
                while (!pslots_multi_.empty())
                {
                    pslots_multi_.front()->multi_error = true;
                    pslots_multi_.pop_front();
                }
                build_slot(pslot, r);
                multi_mode = false;
            }
            else
            {
                pslots_multi_.emplace_back(pslot);
                build_slot(pslot, r);
            }
        }
        else
        {
            delay_queue_clean_state();
            throw redis_data_error("build delay failed");
        }
    }

    void build_all_delay(reply_array&& rarr)
    {
        auto length = rarr.size();
        for (size_t i = 0; i < length; i++)
        {
            auto& pslot = pslots_.front();
            auto& r = rarr[i];
            if (multi_mode)
            {
                build_multi(pslot, rarr[i]);
            }
            else
            {
                if (pslot->multi)   // multi command
                    multi_mode = true;
                build_slot(pslot, rarr[i]);
            }
            pslots_.pop_front();
        }
    }
};

} // namespace detail
} // namespace czredis