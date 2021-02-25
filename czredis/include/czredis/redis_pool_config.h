#pragma once

#include "redis_config.h"
#include "detail/pool_config.h"

namespace czredis
{

class redis_pool_config :
    public redis_config,
    public detail::pool_config
{
public:
    redis_pool_config() : redis_config()
    {
        set_pool_size(8);
        set_init_size(8);
        set_exhausted_action(when_pool_exhausted::kWait);
        set_max_wait_time(1000);
        set_max_idle_time(60 * 1000);
        set_health_check_retry(3);
        set_health_check_interval(30 * 1000);
        set_health_check_on_borrow(false);
    }
};

} // namespace czredis