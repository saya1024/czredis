#pragma once

#include "resp.h"
#include "comand.h"
#include "../config.h"

namespace czredis
{
namespace detail
{

class client : public socket, public command_interface
{
    using my_base = socket;
public:
    client(const std::string& host, const std::string& port, const redis_config& config) :
        host_(host),
        port_(port),
        password_(config.password),
        database_(config.database)
    {
        set_connect_timeout(config.connect_timeout);
        set_read_timeout(config.socket_read_timeout);
        set_write_timeout(config.socket_write_timeout);
    }

    virtual ~client() override
    {
    }

    void do_connect()
    {
        if (!is_connected())
        {
            my_base::connect(host_, port_);
            if (password_ != "")
                auth(password_);
            if (database_ > 0)
                select(database_);
            for (auto& r : read_all_reply())
            {
                if (r.is_error())
                    throw redis_commmand_error(r.as_string());
            }
        }
    }

    virtual void disconnect() noexcept override
    {
        if (is_connected())
        {
            my_base::disconnect();
            send_count_ = 0;
            is_in_multi_ = false;
            is_in_watch_ = false;
        }
    }

    void send_command(cref_string command, init_string_list params1 = {}, init_string_list params2 = {})
    {
        if (!is_connected())
            throw redis_connection_error("not connected");
        resp_.send_command(command, params1, params2);
        ++send_count_;
    }

    reply read_reply()
    {
        --send_count_;
        return resp_.read_reply();
    }

    reply_array read_all_reply()
    {
        reply_array arr;
        while (send_count_ > 0)
        {
            arr.emplace_back(read_reply());
        }
        return arr;
    }

    size_t send_count() const noexcept
    {
        return send_count_;
    }

    czstring password() const noexcept
    {
        return password_;
    }

    unsigned database() const noexcept
    {
        return database_;
    }

    void set_password(cref_string pwd) noexcept
    {
        password_ = pwd;
    }

    void set_database(unsigned db) noexcept
    {
        database_ = db;
    }

    bool is_in_multi() const noexcept
    {
        return is_in_multi_;
    }

    bool is_in_watch() const noexcept
    {
        return is_in_watch_;
    }


    virtual void auth(cref_string password) override
    {
        send_command(cmd::connection::AUTH, { password });
        set_password(password);
    }

    virtual void echo(cref_string message) override
    {
        send_command(cmd::connection::ECHO, { message });
    }

    virtual void ping() override
    {
        send_command(cmd::connection::PING);
    }

    virtual void quit() override
    {
        send_command(cmd::connection::QUIT);
    }

    virtual void select(unsigned db) override
    {
        send_command(cmd::connection::SELECT, { std::to_string(db) });
        set_database(db);
    }


    virtual void append(cref_string key, cref_string value) override
    {
        send_command(cmd::string::APPEND, { value });
    }

    virtual void bitcount(cref_string key, czint start, czint end) override
    {
        send_command(cmd::string::BITCOUNT, { key, std::to_string(start), std::to_string(end) });
    }

    virtual void bitop(cref_string operation, cref_string dest_key, init_string_list keys) override
    {
        czstring temp = operation;
        std::transform(temp.cbegin(), temp.cend(), temp.begin(), [](char c) {
            return static_cast<char>(std::toupper(static_cast<char>(c)));
        });
        if (temp != "AND" && temp != "OR" && temp != "XOR" && temp != "NOT")
            throw redis_commmand_error("ERR syntax error");
        if (keys.size() == 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'bitop' command");
        if (temp == "NOT" && keys.size() > 1)
            throw redis_commmand_error("ERR BITOP NOT must be called with a single source key");
        send_command(cmd::string::BITOP, { temp, dest_key }, keys);
    }

    virtual void decr(cref_string key) override
    {
        send_command(cmd::string::DECR, { key });
    }

    virtual void decrby(cref_string key, czint decrement) override
    {
        send_command(cmd::string::DECRBY, { key, std::to_string(decrement) });
    }

    virtual void get(cref_string key) override
    {
        send_command(cmd::string::GET, { key });
    }

    virtual void getbit(cref_string key, czint offset) override
    {
        if (offset < 0)
            throw redis_commmand_error("ERR bit offset is not an integer or out of range");
        send_command(cmd::string::GETBIT, { key, std::to_string(offset) });
    }

    virtual void getrange(cref_string key, czint start, czint end) override
    {
        send_command(cmd::string::GETRANGE, { key, std::to_string(start), std::to_string(end) });
    }

    virtual void getset(cref_string key, cref_string value) override
    {
        send_command(cmd::string::GETSET, { key, value });
    }

    virtual void incr(cref_string key) override
    {
        send_command(cmd::string::INCR, { key });
    }

    virtual void incrby(cref_string key, czint increment)
    {
        send_command(cmd::string::INCRBY, { key, std::to_string(increment) });
    }

    virtual void incrbyfloat(cref_string key, double increment) override
    {
        send_command(cmd::string::INCRBYFLOAT, { key, std::to_string(increment) });
    }

    virtual void mget(init_string_list keys) override
    {
        if (keys.size() == 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'mget' command");
        send_command(cmd::string::MGET, keys);
    }

    virtual void mset(init_string_list key_value_pairs) override
    {
        if (key_value_pairs.size() == 0 || key_value_pairs.size() % 2 != 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'mset' command");
        send_command(cmd::string::MSET, key_value_pairs);
    }

    virtual void msetnx(init_string_list key_value_pairs) override
    {
        if (key_value_pairs.size() == 0 || key_value_pairs.size() % 2 != 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'msetnx' command");
        send_command(cmd::string::MSETNX, key_value_pairs);
    }

    virtual void psetex(cref_string key, czint milliseconds, cref_string value) override
    {
        if (milliseconds <= 0)
            throw redis_commmand_error("ERR invalid expire time in psetex");
        send_command(cmd::string::PSETEX, { key, std::to_string(milliseconds), value });
    }

    virtual void set(cref_string key, cref_string value, init_string_list params = {}) override
    {
        if (params.size() == 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'set' command");
        send_command(cmd::string::SET, { key, value }, params);
    }

    virtual void setbit(cref_string key, czint offset, czbit bit) override
    {
        send_command(cmd::string::SETBIT, { key, std::to_string(offset), (bit ? "1" : "0") });
    }

    virtual void setex(cref_string key, czint seconds, cref_string value) override
    {
        if (seconds <= 0)
            throw redis_commmand_error("ERR invalid expire time in setex");
        send_command(cmd::string::SETEX, { key, std::to_string(seconds), value });
    }

    virtual void setnx(cref_string key, cref_string value)
    {
        send_command(cmd::string::SETNX, { key, value });
    }

    virtual void setrange(cref_string key, czint offset, cref_string value) override
    {
        if (offset < 0)
            throw redis_commmand_error("ERR offset is out of range");
        send_command(cmd::string::SETRANGE, { key, std::to_string(offset), value });
    }

    virtual void strlen(cref_string key) override
    {
        send_command(cmd::string::STRLEN, { key });
    }


    virtual void discard() override
    {
        if (!is_in_multi())
            throw redis_commmand_error("ERR DISCARD without MULTI");

        send_command(cmd::transaction::DISCARD);
        is_in_multi_ = false;
        is_in_watch_ = false;
    }

    virtual void exec() override
    {
        if (!is_in_multi())
            throw redis_commmand_error("ERR EXEC without MULTI");

        send_command(cmd::transaction::EXEC);
        is_in_multi_ = false;
        is_in_watch_ = false;
    }

    virtual void multi() override
    {
        if (is_in_multi())
            throw redis_commmand_error("ERR MULTI calls can not be nested");

        send_command(cmd::transaction::MULTI);
        is_in_multi_ = true;
    }

    virtual void unwatch() override
    {
        send_command(cmd::transaction::UNWATCH);
        is_in_watch_ = false;
    }

    virtual void watch(init_string_list keys) override
    {
        if (keys.size() == 0)
            throw redis_commmand_error("ERR wrong number of arguments for 'watch' command");
        send_command(cmd::transaction::WATCH, keys);
        is_in_watch_ = true;
    }

private:
    std::string     host_;
    std::string     port_;
    czstring        password_;
    unsigned        database_;
    bool            is_in_multi_ = false;
    bool            is_in_watch_ = false;
    size_t          send_count_ = 0;

    resp            resp_{ *this };
};

} // namespace detail
} // namespace czredis
