#pragma once

#include "resp.h"
#include "comand.h"
#include "../config.h"

namespace czredis
{
namespace detail
{

class client : public socket
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

    void connect()
    {
        if (!is_connected())
        {
            my_base::connect(host_, port_);
            if (password_ != "")
            {
                send_command(cmd::connection::kAuth, { password_ });
                get_reply();
                //todo
            }
            if (database_ > 0)
            {
                send_command(cmd::connection::kSelect, { std::to_string(database_) });
                get_reply();
                //todo
            }
        }
    }

    void send_command(const rds_string& command, const string_array& args)
    {
        check_connect();
        resp_.send_command(command, args);
    }

    reply get_reply()
    {
        check_connect();
        return resp_.get_reply();
    }

    void            set_password(const std::string& password) { password_ = password; }

    void            set_database(unsigned database) { database_ = database; }

    bool            is_in_multi() const { return is_in_multi_; }

    bool            is_in_watch() const { return is_in_watch_; }

private:
    std::string     host_;
    std::string     port_;
    std::string     password_;
    unsigned        database_;
    bool            is_in_multi_ = false;
    bool            is_in_watch_ = false;

    resp            resp_{ *this };

    void check_connect()
    {
        if (!is_connected())
            throw redis_connection_error("client is not connected");
    }
};

} // namespace detail
} // namespace czredis
