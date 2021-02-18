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
    static constexpr char kSymbolOfError        = '-';
    static constexpr char kSymbolOfInteger      = ':';
    static constexpr char kSymbolOfBulkString   = '$';
    static constexpr char kSymbolOfArray        = '*';

    resp(socket& s) :
        stream_(s)
    {}

    ~resp() noexcept
    {}

    void send_command(cref_string_array params)
    {
        czstring symbol_num_crlf = kSymbolOfArray +
            std::to_string(params.size()) + "\r\n";
        stream_.write_string(symbol_num_crlf);

        for (auto& param : params)
        {
            symbol_num_crlf = kSymbolOfBulkString +
                std::to_string(param.size()) + "\r\n";
            stream_.write_string(symbol_num_crlf);
            stream_.write_string(param);
            stream_.write_crlf();
        }
    }

    void send_command(cref_string_array params1, cref_string_array params2)
    {
        czstring symbol_num_crlf = kSymbolOfArray +
            std::to_string(params1.size() + params2.size()) + "\r\n";
        stream_.write_string(symbol_num_crlf);

        for (auto& param : params1)
        {
            symbol_num_crlf = kSymbolOfBulkString +
                std::to_string(param.size()) + "\r\n";
            stream_.write_string(symbol_num_crlf);
            stream_.write_string(param);
            stream_.write_crlf();
        }
        for (auto& param : params2)
        {
            symbol_num_crlf = kSymbolOfBulkString +
                std::to_string(param.size()) + "\r\n";
            stream_.write_string(symbol_num_crlf);
            stream_.write_string(param);
            stream_.write_crlf();
        }
    }

    void send_command(std::initializer_list<string_array> params_array)
    {
        size_t num = 0;
        for (auto& params : params_array)
        {
            num += params.size();
        }
        czstring symbol_num_crlf = kSymbolOfArray +
            std::to_string(num) + "\r\n";
        stream_.write_string(symbol_num_crlf);

        for (auto& params : params_array)
        {
            for (auto& param : params)
            {
                symbol_num_crlf = kSymbolOfBulkString +
                    std::to_string(param.size()) + "\r\n";
                stream_.write_string(symbol_num_crlf);
                stream_.write_string(param);
                stream_.write_crlf();
            }
        }
    }

    void send_command(std::initializer_list<czstring> params)
    {
        czstring symbol_num_crlf = kSymbolOfArray +
            std::to_string(params.size()) + "\r\n";
        stream_.write_string(symbol_num_crlf);

        for (auto& param : params)
        {
            symbol_num_crlf = kSymbolOfBulkString +
                std::to_string(param.size()) + "\r\n";
            stream_.write_string(symbol_num_crlf);
            stream_.write_string(param);
            stream_.write_crlf();
        }
    }

    reply get_reply()
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