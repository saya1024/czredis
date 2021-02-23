#pragma once

namespace czredis
{
namespace detail
{

class move_only
{
protected:
    move_only() = default;
    ~move_only() = default;

    move_only(move_only&&) = default;
    move_only& operator=(move_only&&) = default;

private:
    move_only(const move_only&) = delete;
    move_only& operator=(const move_only&) = delete;
};

} // namespace detail
} // namespace czredis