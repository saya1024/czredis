#pragma once

#include <mutex>
#include <list>
//#include "error.h"

namespace czredis
{
namespace detail
{

template<typename T>
class pool : private asio::noncopyable
{
    using unique_ptr = std::unique_ptr<T, std::function<void(T*)>>;
    using unique_lock = std::unique_lock<std::mutex>;

public:
    pool(size_t max_size, size_t max_idle) :
        max_size_(max_size),
        max_idle_(max_idle)
    {
    }

    virtual ~pool()
    {
        unique_lock lock(mtx_);
        cv_.wait(lock, [this] { return used_count_ == 0; });
        for (auto obj : pool_)
        {
            delete obj;
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
    unique_ptr borrow_object()
    {
        unique_lock lock(mtx_);
        T* obj = nullptr;
        if (used_count_ + pool_.size() < max_size_)
        {
            ++used_count_;
            if (pool_.empty())
            {
                obj = new_object();
            }
            else
            {
                obj = pool_.front();
                pool_.pop_front();
            }
        }
        return unique_ptr(obj, [this](T* obj) { return_object(obj); });
    }

    void return_object(T* obj)
    {
        unique_lock lock(mtx_);
        --used_count_;
        if (pool_.size() < max_idle_)
        {
            pool_.emplace_back(obj);
        }
        if (used_count_ == 0)
        {
            cv_.notify_one();
        }
    }

    virtual T* new_object() = 0;

private:
    size_t          max_size_;
    size_t          max_idle_;
    size_t          used_count_ = 0;
    std::mutex      mtx_;
    std::condition_variable cv_;
    std::list<T*>   pool_;
};

} // namespace detail
} // namespace czredis

