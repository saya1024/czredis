#pragma once

#include "detail/data_cast.h"

namespace czredis
{
namespace detail
{

struct delay_slot : private detail::move_only
{
    reply r;
    bool set = false;
    bool multi = false;
    bool multi_discard = false;
    bool multi_error = false;
};

class delay_queue;

} // namespace detail

template<typename T>
class delay : private detail::move_only
{
    friend class detail::delay_queue;
    using slot_pointer = std::shared_ptr<detail::delay_slot>;

    slot_pointer pslot_;
    T data_;

public:
    explicit delay(slot_pointer ptr) :
        pslot_(ptr),
        data_{}
    {}

    T& get()
    {
        if (pslot_ != nullptr)
        {
            if (!pslot_->set)
            {
                if (pslot_->multi)
                {
                    if (pslot_->multi_discard)
                        throw redis_data_error("transaction is discarded");
                    else if (pslot_->multi_error)
                        throw redis_data_error("transaction discarded because of previous errors");
                }
                throw redis_data_error("call sync() or exec() first");
            }
            if (pslot_->r.is_error())
                throw redis_commmand_error(pslot_->r.as_error());
            data_ = detail::reply_cast<T>(std::move(pslot_->r));
            pslot_ = nullptr;
            return data_;
        }
        else
        {
            return data_;
        }
    }
};

} // namespace czredis