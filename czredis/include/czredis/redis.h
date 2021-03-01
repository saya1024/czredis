#pragma once

#include "pipeline.h"
#include "redis_config.h"
#include "transaction.h"
#include "detail/direct_commands.h"
#include "detail/one_key_direct_commands.h"

namespace czredis
{

class redis :
    public detail::direct_commands,
    public detail::one_key_direct_commands
{
    using client = detail::client;

    std::shared_ptr<client> pclient_;

private:

    client& use_client() override final
    {
        if (pclient_->is_in_multi())
            throw redis_commmand_error("transaction is in use");
        if (pclient_->send_count() > 0)
            throw redis_commmand_error("pipeline is in use");
        return *pclient_;
    }

    client& use_client(cref_string key) override final
    {
        return use_client();
    }

public:
    redis(cref_string host = "localhost",
          cref_string port = "6379",
          redis_config config = redis_config()) :
        pclient_(std::make_shared<client>(host, port, config))
    {}

    explicit redis(std::shared_ptr<client>&& ptr) :
        pclient_(ptr)
    {}

    void connect()
    {
        pclient_->disconnect();
        pclient_->do_connect();
    }

    void disconnect() noexcept
    {
        pclient_->disconnect();
    }

    czstring username() const noexcept
    {
        return pclient_->username();
    }

    czstring password() const noexcept
    {
        return pclient_->password();
    }

    unsigned database() const noexcept
    {
        return pclient_->database();
    }

    pipeline get_pipline()
    {
        return pclient_;
    }

    transaction get_transaction()
    {
        return pclient_;
    }

    reply call_command(cref_string cmd, cref_string_array args, bool block = false)
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        if (block)
            c.set_read_timeout(0);
        c.send_command({ cmd }, args);
        return c.get_reply_as<reply>();
    }
};

} // namespace czredis

