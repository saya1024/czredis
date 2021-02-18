#pragma once

#include <exception>

namespace czredis
{
namespace detail
{

template<class VAL>
class allocated_queue : private asio::noncopyable
{
public:
    using value_type = VAL;
    using size_type = std::size_t;

    allocated_queue(size_type capacity) :
        capacity_(capacity),
        size_(0),
        allocated_((VAL*)malloc(sizeof(VAL) * capacity_)),
        begin_(allocated_),
        end_(allocated_)
    {}

    ~allocated_queue() noexcept
    {
        while (!empty())
        {
            pop_back();
        }
        free(allocated_);
    }

    size_type size() const noexcept
    {
        return size_;
    }

    bool empty() const noexcept
    {
        return size_ == 0;
    }

    void push_back(VAL value)
    {
        if (size_ == capacity_)
            return;

        ++size_;
        *end_ = value;
        end_ = next(end_);
    }

    void push_front(VAL value)
    {
        if (size_ == capacity_)
            return;

        ++size_;
        begin_ = before(begin_);
        *begin_ = value;
    }

    VAL pop_back()
    {
        if (empty())
            throw std::out_of_range("allocated_queue empty before pop");

        --size_;
        end_ = before(end_);
        return *end_;
    }

    VAL pop_front()
    {
        if (empty())
            throw std::out_of_range("allocated_queue empty before pop");

        --size_;
        auto it = begin_;
        begin_ = next(begin_);
        return *it;
    }

protected:
    VAL* next(VAL* iter) const noexcept
    {
        if (++iter == allocated_ + capacity_)
        {
            iter = allocated_;
        }
        return iter;
    }

    VAL* before(VAL* iter) const noexcept
    {
        if (iter == allocated_)
        {
            iter = allocated_ + capacity_;
        }
        return --iter;
    }

private:
    size_type capacity_;
    size_type size_;
    VAL* allocated_;
    VAL* begin_;
    VAL* end_;
};

} // namespace detail
} // namespace czredis