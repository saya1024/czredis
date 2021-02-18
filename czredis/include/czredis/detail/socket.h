#pragma once

#include "../common.h"

namespace czredis
{
namespace detail
{
class socket : private asio::noncopyable
{
public:
    socket() : io_context_(1)
    {}

    virtual ~socket() noexcept
    {
        disconnect();
    }

    void connect(const std::string& host, const std::string& service)
    {
        if (!is_connected_)
        {
            auto endpoints = tcp::resolver(io_context_).resolve(host, service);
            socket_.reset(new tcp::socket(io_context_));
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
                    throw redis_connection_error("connect timeout");
                throw_error(ec);
            }
            else
            {
                asio::connect(*socket_, endpoints);
            }
            is_connected_ = true;
        }
    }

    virtual void disconnect() noexcept
    {
        if (is_connected_)
        {
            asio::error_code ignore_ec;
            socket_->shutdown(tcp::socket::shutdown_both, ignore_ec);
            socket_->close(ignore_ec);
            is_connected_ = false;
        }
    }

    size_t write(const czstring& buf)
    {
        return write(buf.c_str(), buf.size());
    }

    size_t write(const char* buf, size_t buf_size)
    {
        size_t ret = 0;
        if (write_timeout_ > 0 && !blocking_)
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
        size_t ret = 0;
        if (read_timeout_ > 0 && !blocking_)
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
        return ret;
    }

    size_t read_some(byte* buf, size_t buf_size)
    {
        size_t ret = 0;
        if (read_timeout_ > 0 && !blocking_)
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
        return ret;
    }

    bool is_connected() const noexcept
    {
        return is_connected_;
    }

    void set_connect_timeout(unsigned millis) noexcept
    {
        connect_timeout_ = millis;
    }

    void set_read_timeout(unsigned millis) noexcept
    {
        read_timeout_ = millis;
    }

    void set_write_timeout(unsigned millis) noexcept
    {
        write_timeout_ = millis;
    }

    void set_block(bool blocking) noexcept
    {
        blocking_ = blocking;
    }

private:
    asio::io_context io_context_;
    std::unique_ptr<tcp::socket> socket_;
    bool is_connected_ = false;
    unsigned connect_timeout_ = 0;
    unsigned read_timeout_ = 0;
    unsigned write_timeout_ = 0;
    bool blocking_ = false;

    bool run(unsigned timeout_ms)
    {
        io_context_.restart();
        io_context_.run_for(std::chrono::milliseconds(timeout_ms));
        if (!io_context_.stopped())
        {
            disconnect();
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
