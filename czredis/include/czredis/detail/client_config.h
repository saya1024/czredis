#pragma once

#include "../common.h"

namespace czredis
{

namespace detail
{

class client_config
{
    czstring username_;
    czstring password_;
    unsigned database_;
    unsigned connect_timeout_;
    unsigned socket_read_timeout_;
    unsigned socket_write_timeout_;

public:
    client_config() = default;

    cref_string username() const noexcept
    {
        return username_;
    }

    void set_username(cref_string name)
    {
        username_ = name;
    }

    cref_string password() const noexcept
    {
        return password_;
    }

    void set_password(cref_string pwd)
    {
        password_ = pwd;
    }

    unsigned database() const noexcept
    {
        return database_;
    }

    void set_database(unsigned db) noexcept
    {
        database_ = db;
    }

    unsigned connect_timeout() const noexcept
    {
        return connect_timeout_;
    }

    void set_connect_timeout(unsigned millis) noexcept
    {
        connect_timeout_ = millis;
    }

    unsigned socket_read_timeout() const noexcept
    {
        return socket_read_timeout_;
    }

    void set_socket_read_timeout(unsigned millis) noexcept
    {
        socket_read_timeout_ = millis;
    }

    unsigned socket_write_timeout() const noexcept
    {
        return socket_write_timeout_;
    }

    void set_socket_write_timeout(unsigned millis) noexcept
    {
        socket_write_timeout_ = millis;
    }
};

} // namespace detail
} // namespace czredis