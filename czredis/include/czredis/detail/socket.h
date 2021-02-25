#pragma once

#include "pool_object.h"
#include "../error.h"

namespace czredis
{
namespace detail
{

class socket : public pool_object
{
    asio::io_context io_context_;
    std::unique_ptr<tcp::socket> socket_;
    long long connect_timeout_ = 0;
    long long read_timeout_ = 0;
    long long write_timeout_ = 0;
    bool is_connected_ = false;

public:
    socket() : io_context_(1)
    {}

    ~socket() noexcept override
    {
        disconnect();
    }

    void connect(const std::string& host, const std::string& service)
    {
        if (!is_connected_)
        {
            auto endpoints = tcp::resolver(io_context_).resolve(host, service);
            socket_ = std::make_unique<tcp::socket>(io_context_);
            if (connect_timeout_ > 0)
            {
                asio::error_code ec;
                asio::async_connect(*socket_, endpoints,
                    [&ec](const asio::error_code& result_error,
                          const tcp::endpoint& /*result_endpoint*/)
                {
                    ec = result_error;
                });
                if (!run(connect_timeout_))
                {
                    disconnect();
                    throw redis_connection_error("connect timeout");
                }
                throw_error(ec);
            }
            else
            {
                asio::connect(*socket_, endpoints);
            }
            is_connected_ = true;
            update_response_time();
        }
    }

    virtual void disconnect() noexcept
    {
        if (is_connected_)
        {
            asio::error_code ignore_ec;
            socket_->shutdown(tcp::socket::shutdown_both, ignore_ec);
            socket_->close(ignore_ec);
            socket_ = nullptr;
            is_connected_ = false;
        }
    }

    size_t write(const czstring& buf)
    {
        return write(buf.c_str(), buf.size());
    }

    size_t write(const char* buf, size_t buf_size)
    {
        if (!is_connected_)
            throw redis_connection_error("not connected");

        size_t ret = 0;
        if (write_timeout_ > 0)
        {
            asio::error_code ec;
            asio::async_write(*socket_, asio::buffer(buf, buf_size),
                [&ec, &ret](const asio::error_code& result_error,
                            size_t result_size)
            {
                ec = result_error;
                ret = result_size;
            });
            if (!run(write_timeout_))
                throw redis_connection_error("write timeout");
            throw_error(ec);
        }
        else
        {
            ret = asio::write(*socket_, asio::buffer(buf, buf_size));
        }
        return ret;
    }

    size_t read(czstring& buf, size_t read_size)
    {
        if (!is_connected_)
            throw redis_connection_error("not connected");

        size_t ret = 0;
        if (read_timeout_ > 0)
        {
            asio::error_code ec;
            asio::async_read(*socket_, asio::dynamic_buffer(buf),
                asio::transfer_exactly(read_size),
                [&ec, &ret](const asio::error_code& result_error,
                            size_t result_size)
            {
                ec = result_error;
                ret = result_size;
            });
            if (!run(read_timeout_))
                throw redis_connection_error("read timeout");
            throw_error(ec);
        } 
        else
        {
            ret = asio::read(*socket_, asio::dynamic_buffer(buf),
                asio::transfer_exactly(read_size));
        }
        update_response_time();
        return ret;
    }

    size_t read_some(byte* buf, size_t buf_size)
    {
        if (!is_connected_)
            throw redis_connection_error("not connected");

        size_t ret = 0;
        if (read_timeout_ > 0)
        {
            asio::error_code ec;
            socket_->async_read_some(asio::buffer(buf, buf_size),
                [&ec, &ret](const asio::error_code& result_error,
                            size_t result_size)
            {
                ec = result_error;
                ret = result_size;
            });
            if (!run(read_timeout_))
                throw redis_connection_error("read timeout");
            throw_error(ec);
        }
        else
        {
            ret = socket_->read_some(asio::buffer(buf, buf_size));
        }
        update_response_time();
        return ret;
    }

    bool is_connected() const noexcept
    {
        return is_connected_;
    }

    long long connect_timeout() const noexcept
    {
        return connect_timeout_;
    }

    void set_connect_timeout(long long millis) noexcept
    {
        connect_timeout_ = millis;
    }

    long long read_timeout() const noexcept
    {
        return read_timeout_;
    }

    void set_read_timeout(long long millis) noexcept
    {
        read_timeout_ = millis;
    }

    long long write_timeout() const noexcept
    {
        return write_timeout_;
    }

    void set_write_timeout(long long millis) noexcept
    {
        write_timeout_ = millis;
    }

private:
    bool run(long long millis)
    {
        io_context_.restart();
        io_context_.run_for(std::chrono::milliseconds(millis));
        if (!io_context_.stopped())
        {
            return false;
        }
        return true;
    }

    void throw_error(const asio::error_code& ec)
    {
        if (ec)
        {
            throw redis_connection_error(ec);
        }
    }
};

}  // namespace detail
}  // namespace czredis
