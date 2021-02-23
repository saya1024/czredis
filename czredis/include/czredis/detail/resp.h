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

    void send_command(cref_string_array params)
    {
        czstring symbol_num_crlf = kSymbolOfArray +
            std::to_string(params.size()) + "\r\n";
        stream_.write_string(symbol_num_crlf);

        auto length = params.size();
        for (size_t i = 0; i < length; i++)
        {
            symbol_num_crlf = kSymbolOfBulkString +
                std::to_string(params[i].size()) + "\r\n";
            stream_.write_string(symbol_num_crlf);
            stream_.write_string(params[i]);
            stream_.write_crlf();
        }
    }

    void send_command(cref_string_array params1, cref_string_array params2)
    {
        czstring symbol_num_crlf = kSymbolOfArray +
            std::to_string(params1.size() + params2.size()) + "\r\n";
        stream_.write_string(symbol_num_crlf);

        auto length = params1.size();
        for (size_t i = 0; i < length; i++)
        {
            symbol_num_crlf = kSymbolOfBulkString +
                std::to_string(params1[i].size()) + "\r\n";
            stream_.write_string(symbol_num_crlf);
            stream_.write_string(params1[i]);
            stream_.write_crlf();
        }
        length = params2.size();
        for (size_t i = 0; i < length; i++)
        {
            symbol_num_crlf = kSymbolOfBulkString +
                std::to_string(params2[i].size()) + "\r\n";
            stream_.write_string(symbol_num_crlf);
            stream_.write_string(params2[i]);
            stream_.write_crlf();
        }
    }

    void send_command(std::initializer_list<string_array> params_init_list)
    {
        size_t num = 0;
        for (auto& params : params_init_list)
        {
            num += params.size();
        }
        czstring symbol_num_crlf = kSymbolOfArray +
            std::to_string(num) + "\r\n";
        stream_.write_string(symbol_num_crlf);

        for (auto& params : params_init_list)
        {
            auto length = params.size();
            for (size_t i = 0; i < length; i++)
            {
                symbol_num_crlf = kSymbolOfBulkString +
                    std::to_string(params[i].size()) + "\r\n";
                stream_.write_string(symbol_num_crlf);
                stream_.write_string(params[i]);
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