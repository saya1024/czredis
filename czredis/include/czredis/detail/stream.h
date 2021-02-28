#pragma once

#include "socket.h"

namespace czredis
{
namespace detail
{

class stream final : private asio::noncopyable
{
    static constexpr size_t kBufSize = 4096;

    socket& socket_;
    byte* buf_;
    byte* begin_;
    byte* end_;

public:
    stream(socket& s) :
        socket_(s),
        buf_(new byte[kBufSize]),
        begin_(buf_),
        end_(buf_)
    {}

    ~stream() noexcept
    {
        delete[] buf_;
        buf_ = nullptr;
    }

    void reset() noexcept
    {
        begin_ = buf_;
        end_ = buf_;
    }

    byte read_byte()
    {
        ensure_fill();
        return *(begin_++);
    }

    czint read_integer_crlf()
    {
        auto s = read_string_crlf();
        try
        {
            return std::stoll(s);
        }
        catch (const std::exception&)
        {
            throw redis_connection_error("read integer error");
        }
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
        size_t buf_size = end_ - begin_;
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
            throw redis_connection_error("read crlf error");
        if (read_byte() != '\n')
            throw redis_connection_error("read crlf error");
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