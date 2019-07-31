#pragma once

#include "stream.h"

namespace czredis
{
namespace detail
{

class resp
{
public:
    static constexpr char kSymbolOfSimpleString = '+';
    static constexpr char kSymbolOfError = '-';
    static constexpr char kSymbolOfInteger = ':';
    static constexpr char kSymbolOfBulkString = '$';
    static constexpr char kSymbolOfArray = '*';

    resp(socket& s) noexcept :
        stream_(s)
    {
    }

    ~resp() noexcept
    {
    }

    void send_command(cref_string command, init_string_list params1, init_string_list params2)
    {
        czstring char_num_crlf = kSymbolOfArray + std::to_string(params1.size() + params2.size() + 1) + "\r\n";
        stream_.write_string(char_num_crlf);

        char_num_crlf = kSymbolOfBulkString + std::to_string(command.size()) + "\r\n";
        stream_.write_string(char_num_crlf);
        stream_.write_string(command);
        stream_.write_crlf();

        for (auto& param : params1)
        {
            char_num_crlf = kSymbolOfBulkString + std::to_string(param.size()) + "\r\n";
            stream_.write_string(char_num_crlf);
            stream_.write_string(param);
            stream_.write_crlf();
        }
        for (auto& param : params2)
        {
            char_num_crlf = kSymbolOfBulkString + std::to_string(param.size()) + "\r\n";
            stream_.write_string(char_num_crlf);
            stream_.write_string(param);
            stream_.write_crlf();
        }
    }

    reply read_reply()
    {
        return parse();
    }

private:
    stream stream_;

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
        return stream_.read_string_crlf();
    }

    reply parse_error()
    {
        return { stream_.read_string_crlf(), true };
    }

    reply parse_integer()
    {
        return stream_.read_integer_crlf();
    }

    reply parse_bulk_string()
    {
        auto num = stream_.read_integer_crlf();
        if (num < 0)
            return reply();
        if (num == 0)
            return czstring("");

        auto size = integer_to_size(num);
        return stream_.read_string_crlf(size);
    }

    reply parse_array()
    {
        auto num = stream_.read_integer_crlf();
        reply_array arr;
        if (num < 0)
            return reply();
        if (num == 0)
            return arr;

        auto size = integer_to_size(num);
        if (arr.capacity() < size)
        {
            arr.reserve(size);
        }
        for (size_t i = 0; i < size; i++)
        {
            arr.emplace_back(parse());
        }
        return arr;
    }

    size_t integer_to_size(czint num)
    {
        auto size = static_cast<size_t>(num);
        if (static_cast<czint>(size) != num)
            throw std::overflow_error("resp::integer_to_size overflow");
        return size;
    }
};

}  // namespace detail
}  // namespace czredis