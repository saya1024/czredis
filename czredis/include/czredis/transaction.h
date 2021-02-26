#pragma once

#include "detail/call_finally.h"
#include "detail/delay_commands.h"
#include "detail/one_key_delay_commands.h"

namespace czredis
{

class transaction :
    public detail::delay_commands,
    public detail::one_key_delay_commands
{
    using client = detail::client;

    std::shared_ptr<client> pclient_;
    client& client_;

private:
    client& use_client() override final
    {
        if (!client_.is_in_multi())
            throw redis_commmand_error("not in multi");
        return client_;
    }

    client& use_client(cref_string key) override final
    {
        return use_client();
    }

public:
    transaction(std::shared_ptr<client> ptr) :
        pclient_(ptr),
        client_(*pclient_)
    {}

    czstring discard()
    {
        client_.discard();
        auto ret = client_.make_delay<czstring>();
        client_.build_all_delay();
        return ret.get();
    }

    reply exec()
    {
        client_.build_all_delay();
        auto ret = client_.make_delay<reply>();
        client_.build_all_delay();
        return ret.get();
    }

    delay<czstring> multi()
    {
        client_.multi();
        return client_.make_delay<czstring>();
    }

    delay<czstring> unwatch()
    {
        client_.unwatch();
        return client_.make_delay<czstring>();
    }

    delay<czstring> watch(cref_string_array keys)
    {
        client_.watch(keys);
        return client_.make_delay<czstring>();
    }
};

} // namespace czredis