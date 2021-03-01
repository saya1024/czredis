#pragma once

#include <functional>

namespace czredis
{
namespace detail
{

class call_finally
{
    std::function<void()> func_;

public:
    call_finally(std::function<void()> func) :
        func_(func)
    {}

    ~call_finally()
    {
        try
        {
            func_();
        }
        catch (...)
        {}
    }

    call_finally(const call_finally&) = delete;
    const call_finally operator=(const call_finally&) = delete;
};

} // namespace detail
} // namespace czredis