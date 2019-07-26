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
        }
    }

    void send_command(cref_string command, init_strings args = {})
    {
        check_connect();
        resp_.send_command(command, args);
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
        send_command(cmd::connection::kAuth, { password });
        set_password(password);
    }

    virtual void echo(cref_string message) override
    {
        send_command(cmd::connection::kEcho, { message });
    }

    virtual void ping() override
    {
        send_command(cmd::connection::kPing);
    }

    virtual void quit() override
    {
        send_command(cmd::connection::kQuit);
    }

    virtual void select(unsigned db) override
    {
        send_command(cmd::connection::kSelect, { std::to_string(db) });
        set_database(db);
    }


    virtual void discard() override
    {
        if (!is_in_multi())
            throw redis_commmand_error("ERR DISCARD without MULTI");

        send_command(cmd::transaction::kDiscard);
        is_in_multi_ = false;
        is_in_watch_ = false;
    }

    virtual void exec() override
    {
        if (!is_in_multi())
            throw redis_commmand_error("ERR EXEC without MULTI");

        send_command(cmd::transaction::kExec);
        is_in_multi_ = false;
        is_in_watch_ = false;
    }

    virtual void multi() override
    {
        if (is_in_multi())
            throw redis_commmand_error("ERR MULTI calls can not be nested");

        send_command(cmd::transaction::kMulti);
        is_in_multi_ = true;
    }

    virtual void unwatch() override
    {
        send_command(cmd::transaction::kUnwatch);
        is_in_watch_ = false;
    }

    virtual void watch(init_strings keys) override
    {
        send_command(cmd::transaction::kWatch, keys);
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
