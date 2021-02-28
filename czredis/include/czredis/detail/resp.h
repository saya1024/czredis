#pragma once

#include "stream.h"
#include "../reply.h"

namespace czredis
{
namespace detail
{

class resp final
{
    stream stream_;

public:
    static constexpr char kSymbolOfSimpleString = '+';
    static constexpr char kSymbolOfError        = '-';
    static constexpr char kSymbolOfInteger      = ':';
    static constexpr char kSymbolOfBulkString   = '$';
    static constexpr char kSymbolOfArray        = '*';

    resp(socket& s) :
        stream_(s)
    {}

    void reset_stream() noexcept
    {
        stream_.reset();
    }

    void write_params_count(size_t count)
    {
        stream_.write_string(kSymbolOfArray +
            std::to_string(count) + "\r\n");
    }

    template<typename T>
    void write_params(T&& params)
    {
        for (auto& param : params)
        {
            stream_.write_string(kSymbolOfBulkString +
                std::to_string(param.size()) + "\r\n");
            stream_.write_string(param);
            stream_.write_crlf();
        }
    }

    void send_command(cref_string_array params)
    {
        write_params_count(params.size());
        write_params(params);
    }

    void send_command(cref_string_array params1, cref_string_array params2)
    {
        write_params_count(params1.size() + params2.size());
        write_params(params1);
        write_params(params2);
    }

    void send_command(std::initializer_list<string_array> params_init_list)
    {
        size_t count = 0;
        for (auto& params : params_init_list)
        {
            count += params.size();
        }

        write_params_count(count);
        for (auto& params : params_init_list)
        {
            write_params(params);
        }
    }

    void send_command(std::initializer_list<czstring> params)
    {
        write_params_count(params.size());
        write_params(params);
    }

    reply get_reply()
    {
        return parse();
    }

private:
    reply parse()
    {
        auto b = stream_.read_byte();
        switch (b)
        {
        case kSymbolOfSimpleString:
            return parse_simple_string();
        case kSymbolOfError:
            return parse_error();
        case kSymbolOfInteger:
            return parse_integer();
        case kSymbolOfBulkString:
            return parse_bulk_string();
        case kSymbolOfArray:
            return parse_array();
        default:
            throw redis_connection_error("unknown reply");
        }
    }

    reply parse_simple_string()
    {
        return reply(stream_.read_string_crlf());
    }

    reply parse_error()
    {
        return reply(stream_.read_string_crlf(), true);
    }

    reply parse_integer()
    {
        return reply(stream_.read_integer_crlf());
    }

    reply parse_bulk_string()
    {
        auto num = stream_.read_integer_crlf();
        if (num < 0)
            return reply();
        if (num == 0)
            return reply(czstring());

        auto size = integer_to_size(num);
        return reply(stream_.read_string_crlf(size));
    }

    reply parse_array()
    {
        auto num = stream_.read_integer_crlf();
        if (num < 0)
            return reply();
        if (num == 0)
            return reply(reply_array());

        reply_array arr;
        auto size = integer_to_size(num);
        if (arr.capacity() < size)
        {
            arr.reserve(size);
        }
        for (size_t i = 0; i < size; i++)
        {
            arr.emplace_back(parse());
        }
        return reply(std::move(arr));
    }

    size_t integer_to_size(czint num) const
    {
        auto size = static_cast<size_t>(num);
        if (static_cast<czint>(size) != num)
            throw std::overflow_error("size of data is bigger zhan size_t");
        return size;
    }
};

}  // namespace detail
}  // namespace czredis