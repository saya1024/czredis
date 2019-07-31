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
    stream(socket& s) noexcept:
        socket_(s)
    {
    }

    ~stream() noexcept
    {
    }

    byte read_byte()
    {
        ensure_fill();
        return buf_[begin_++];
    }

    czint read_integer_crlf()
    {
        ensure_fill();
        bool is_neg = buf_[begin_] == '-';
        if (is_neg)
            ++begin_;

        czint value = 0;
        while (true)
        {
            ensure_fill();
            auto b = buf_[begin_++];
            if (b == '\r')
            {
                ensure_fill();
                if (buf_[begin_++] != '\n')
                    throw redis_connection_error("unexpected end of stream");
                break;
            }
            else
            {
                value = value * 10 + b - '0';
            }
        }

        return is_neg ? -value : value;
    }

    czstring read_string_crlf()
    {
        czstring s;
        while (true)
        {
            ensure_fill();
            for (auto i = begin_; i < end_; i++)
            {
                if (buf_[i] == '\r')
                {
                    s.append(buf_ + begin_, buf_ + i);
                    begin_ = i;
                    read_crlf();
                    return s;
                }
            }
            s.append(buf_ + begin_, buf_ + end_);
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
            s.append(buf_ + begin_, buf_ + end_);
            begin_ = end_;
            socket_.read(s, read_size - buf_size);
        }
        else
        {
            s.append(buf_ + begin_, buf_ + begin_ + read_size);
            begin_ += read_size;
        }
        read_crlf();
        return s;
    }

    void read_crlf()
    {
        ensure_fill();
        if (buf_[begin_++] != '\r')
            throw redis_connection_error("unexpected end of stream");
        ensure_fill();
        if (buf_[begin_++] != '\n')
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
    byte buf_[kBufSize];
    size_t begin_ = 0;
    size_t end_ = 0;

    void ensure_fill()
    {
        if (begin_ == end_)
        {
            begin_ = 0;
            end_ = socket_.read_some(buf_, kBufSize);
        }
    }
};

} // namespace detail
} // namespace czredis