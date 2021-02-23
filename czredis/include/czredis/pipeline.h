#pragma once

#include "detail/delay_commands.h"
#include "detail/one_key_delay_commands.h"

namespace czredis
{

class pipeline :
    public detail::delay_commands,
    public detail::one_key_delay_commands
{
    using client = detail::client;
    friend class redis;

    client& client_;

private:
    pipeline(client& c) :
        client_(c)
    {}

    client& use_client() override final
    {
        if (client_.is_in_multi())
            throw redis_commmand_error("transaction is in use");
        return client_;
    }

    client& use_client(cref_string key) override final
    {
        return use_client();
    }

public:

    void sync()
    {
        build_all_delay(use_client().get_all_reply());
    }

    reply_array sync_get_raw_replys()
    {
        return use_client().get_all_reply();
    }
};

} // namespace czredis