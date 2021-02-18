#pragma once

#include <functional>

namespace czredis
{
namespace detail
{

class call_finally
{
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
        catch (const std::exception&)
        {
        }
    }

    call_finally(const call_finally&) = delete;
    const call_finally operator=(const call_finally&) = delete;

private:
    std::function<void()> func_;
};

} // namespace detail
} // namespace czredis