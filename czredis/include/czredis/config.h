#pragma once

#include "common.h"

namespace czredis
{

struct redis_config
{
    czstring username               = "";
    czstring password               = "";
    unsigned database               = 0;
    unsigned connect_timeout        = 2000;
    unsigned socket_read_timeout    = 2000;
    unsigned socket_write_timeout   = 2000;
};

struct redis_pool_config : redis_config
{
    czstring name   = "";
    size_t max_size = 100;
    size_t max_idle = 20;
};

} // namespace czredis

