#pragma once

#include "detail/client_config.h"

namespace czredis
{

class redis_config : public detail::client_config
{
public:
    redis_config()
    {
        set_username("");
        set_password("");
        set_database(0);
        set_connect_timeout(2000);
        set_socket_read_timeout(2000);
        set_socket_write_timeout(2000);
    }
};

} // namespace czredis