#pragma once

#include "socket.h"

namespace czredis
{
namespace detail
{

class stream : private asio::noncopyable
{
    constexpr static size_t kBufSize = 4096;
public:
    stream(socket& s) :
        socket_(s),
        buf_(new byte[kBufSize]),
        begin_(buf_),
        end_(buf_)
    {
    }

    ~stream() noexcept
    {
        delete[] buf_;
    }

    byte read_byte()
    {
        ensure_fill();
        return *(begin_++);
    }

    czint read_integer_crlf()
    {
        czint value = 0;
        bool minus = false;
        while (true)
        {
            auto b = read_byte();
            if (b == '\r')
            {
                if (read_byte() != '\n')
                    throw redis_connection_error("unexpected end of stream");
                break;
            }
            else if (b == '-')
            {
                minus = true;
            }
            else if (b >= '0' && b <= '9')
            {
                value = value * 10 + b - '0';
            }
            else
            {
                throw redis_connection_error("unexpected end of stream");
            }
        }

        return minus ? -value : value;
    }

    czstring read_string_crlf()
    {
        czstring s;
        while (true)
        {
            ensure_fill();
            for (auto it = begin_; it != end_; it++)
            {
                if (*it == '\r')
                {
                    s.append(begin_, it);
                    begin_ = it;
                    read_crlf();
                    return s;
                }
            }
            s.append(begin_, end_);
            begin_ = end_;
        }
    }

    czstring read_string_crlf(size_t read_size)
    {
        czstring s;
        if (read_size > s.capacity())
        {
            s.reserve(read_size);
        }
        auto buf_size = end_ - begin_;
        if (read_size > buf_size)
        {
            s.append(begin_, end_);
            begin_ = end_;
            socket_.read(s, read_size - buf_size);
        }
        else
        {
            s.append(begin_, begin_ + read_size);
            begin_ += read_size;
        }
        read_crlf();
        return s;
    }

    void read_crlf()
    {
        if (read_byte() != '\r')
            throw redis_connection_error("unexpected end of stream");
        if (read_byte() != '\n')
            throw redis_connection_error("unexpected end of stream");
    }

    void write_string(const czstring& s)
    {
        socket_.write(s);
    }

    void write_crlf()
    {
        socket_.write("\r\n", 2);
    }

private:
    socket& socket_;
    byte* buf_;
    byte* begin_;
    byte* end_;

    void ensure_fill()
    {
        if (begin_ == end_)
        {
            begin_ = buf_;
            end_ = begin_ + socket_.read_some(buf_, kBufSize);
        }
    }
};

} // namespace detail
} // namespace czredis