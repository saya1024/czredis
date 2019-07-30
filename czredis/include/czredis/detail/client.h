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
            {
                auth(password_);
                read_reply();
            }
            if (database_ > 0)
            {
                select(database_);
                read_reply();
            }
        }
    }

    virtual void disconnect() noexcept override
    {
        if (is_connected())
        {
            my_base::disconnect();
            response_count_ = 0;
            is_in_multi_ = false;
            is_in_watch_ = false;
        }
    }

    void send_command(cref_string command, init_strings params1 = {}, init_strings params2 = {})
    {
        check_connect();
        resp_.send_command(command, params1, params2);
        ++response_count_;
    }

    reply read_reply()
    {
        check_connect();
        --response_count_;
        return resp_.read_reply();
    }

    reply_array read_all_reply()
    {
        reply_array arr;
        while (response_count_ > 0)
        {
            arr.emplace_back(read_reply());
        }
        return arr;
    }

    void set_password(const std::string& password) noexcept
    {
        password_ = password;
    }

    void set_database(unsigned database) noexcept
    {
        database_ = database;
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

    virtual void bitcount(cref_string key, rds_integer start, rds_integer end) override
    {
        send_command(cmd::string::BITCOUNT, { key, std::to_string(start), std::to_string(end) });
    }

    virtual void bitop(cref_string operation, cref_string dest_key, init_strings keys) override
    {
        send_command(cmd::string::BITOP, { operation, dest_key }, keys);
    }

    virtual void decr(cref_string key) override
    {
        send_command(cmd::string::DECR, { key });
    }

    virtual void decrby(cref_string key, rds_integer decrement) override
    {
        send_command(cmd::string::DECRBY, { key, std::to_string(decrement) });
    }

    virtual void get(cref_string key) override
    {
        send_command(cmd::string::GET, { key });
    }

    virtual void getbit(cref_string key, rds_integer offset) override
    {
        send_command(cmd::string::GETBIT, { key, std::to_string(offset) });
    }

    virtual void getrange(cref_string key, rds_integer start, rds_integer end) override
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

    virtual void incrby(cref_string key, rds_integer increment)
    {
        send_command(cmd::string::INCRBY, { key, std::to_string(increment) });
    }

    virtual void incrbyfloat(cref_string key, double increment) override
    {
        send_command(cmd::string::INCRBYFLOAT, { key, std::to_string(increment) });
    }

    virtual void mget(init_strings keys) override
    {
        send_command(cmd::string::MGET, keys);
    }

    virtual void mset(init_strings key_value_pairs) override
    {
        send_command(cmd::string::MSET, key_value_pairs);
    }

    virtual void msetnx(init_strings key_value_pairs) override
    {
        send_command(cmd::string::MSETNX, key_value_pairs);
    }

    virtual void psetex(cref_string key, rds_integer milliseconds, cref_string value) override
    {
        send_command(cmd::string::PSETEX, { key, std::to_string(milliseconds), value });
    }

    virtual void set(cref_string key, cref_string value, init_strings params = {}) override
    {
        send_command(cmd::string::SET, { key, value }, params);
    }

    virtual void setbit(cref_string key, rds_integer offset, bool value) override
    {
        send_command(cmd::string::SETBIT, { key, std::to_string(offset), (value ? "1" : "0") });
    }

    virtual void setex(cref_string key, rds_integer seconds, cref_string value) override
    {
        send_command(cmd::string::SETEX, { key, std::to_string(seconds), value });
    }

    virtual void setnx(cref_string key, cref_string value)
    {
        send_command(cmd::string::SETNX, { key, value });
    }

    virtual void setrange(cref_string key, rds_integer offset, cref_string value) override
    {
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

    virtual void watch(init_strings keys) override
    {
        send_command(cmd::transaction::WATCH, keys);
        is_in_watch_ = true;
    }

private:
    std::string     host_;
    std::string     port_;
    rds_string      password_;
    unsigned        database_;
    bool            is_in_multi_ = false;
    bool            is_in_watch_ = false;
    size_t          response_count_ = 0;

    resp            resp_{ *this };

    void check_connect()
    {
        if (!is_connected())
            throw redis_connection_error("client is not connected");
    }
};

} // namespace detail
} // namespace czredis
