#pragma once

#include "detail/call_finally.h"
#include "detail/delay_commands.h"
#include "detail/one_key_delay_commands.h"

namespace czredis
{

class pipeline :
    public detail::delay_commands,
    public detail::one_key_delay_commands,
    public detail::i_delay_transactions
{
    using client = detail::client;

    std::shared_ptr<client> pclient_;
    client& client_;

private:
    client& use_client() override final
    {
        return client_;
    }

    client& use_client(cref_string key) override final
    {
        return use_client();
    }

public:
    pipeline(std::shared_ptr<client> ptr) :
        pclient_(ptr),
        client_(*pclient_)
    {}

    void sync(bool block = false)
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        if (block)
            c.set_read_timeout(0);
        c.build_all_delay();
    }

    reply_array sync_raw_results(bool block = false)
    {
        auto& c = use_client();
        auto read_timeout = c.read_timeout();
        detail::call_finally func([&c, read_timeout]() {
            c.set_read_timeout(read_timeout);
        });
        if (block)
            c.set_read_timeout(0);
        return c.get_all_reply();
    }

//transactions

    delay<czstring> discard() override final
    {
        auto& c = use_client();
        c.discard();
        return c.make_delay<czstring>();
    }

    delay<reply> exec() override final
    {
        auto& c = use_client();
        c.exec();
        return c.make_delay<reply>();
    }

    delay<czstring> multi() override final
    {
        auto& c = use_client();
        c.multi();
        return c.make_delay<czstring>();
    }

    delay<czstring> unwatch() override final
    {
        auto& c = use_client();
        c.unwatch();
        return c.make_delay<czstring>();
    }

    delay<czstring> watch(cref_string_array keys) override final
    {
        auto& c = use_client();
        c.watch(keys);
        return c.make_delay<czstring>();
    }
};

} // namespace czredis