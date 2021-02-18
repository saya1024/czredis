#pragma once

#include <mutex>
#include <list>
#include "allocated_queue.h"

namespace czredis
{
namespace detail
{

template<class OBJ>
class pool : private asio::noncopyable
{
public:
    using unique_ptr_obj = std::unique_ptr<OBJ, std::function<void(OBJ*)>>;
    using unique_lock = std::unique_lock<std::mutex>;

    pool(size_t max_size, size_t max_idle) :
        max_size_(max_size),
        max_idle_(max_idle),
        pool_(max_size)
    {}

    virtual ~pool() noexcept
    {
        unique_lock lock(mtx_);
        cv_.wait(lock, [this] { return used_count_ == 0; });
        while (!pool_.empty())
        {
            delete_object(pool_.pop_front());
        }
    }

    size_t used_count() const noexcept
    {
        return used_count_;
    }

    size_t idle_count() const noexcept
    {
        return pool_.size();
    }

protected:
    unique_ptr_obj borrow_object()
    {
        unique_lock lock(mtx_);
        OBJ* obj = nullptr;
        if (used_count_ + pool_.size() < max_size_)
        {
            ++used_count_;
            if (pool_.empty())
            {
                obj = new_object();
            }
            else
            {
                obj = pool_.pop_front();
            }
        }
        return unique_ptr_obj(obj, [this](OBJ* obj) { return_object(obj); });
    }

    virtual void return_object(OBJ* obj) noexcept
    {
        when_return(obj);
        unique_lock lock(mtx_);
        --used_count_;
        if (pool_.size() < max_idle_)
        {
            pool_.push_back(std::move(obj));
        }
        else
        {
            delete_object(obj);
        }
        if (used_count_ == 0)
        {
            cv_.notify_one();
        }
    }

    virtual void when_return(OBJ*) noexcept = 0;

    virtual OBJ* new_object() = 0;

    virtual void delete_object(OBJ*) noexcept = 0;

private:
    size_t          max_size_;
    size_t          max_idle_;
    size_t          used_count_ = 0;
    std::mutex      mtx_;
    std::condition_variable cv_;
    allocated_queue<OBJ*> pool_;
};

} // namespace detail
} // namespace czredis

