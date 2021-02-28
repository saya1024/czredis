#pragma once

#include "redis.h"
#include "redis_pool_config.h"
#include "detail/pool.h"


namespace czredis
{

class redis_pool: public detail::pool
{
    using client = detail::client;
    using my_base = detail::pool;

    std::string  host_;
    std::string  port_;
    redis_config config_;
public:
    redis_pool(cref_string host,
               cref_string port,
               redis_pool_config config = redis_pool_config()) :
        host_(host),
        port_(port),
        config_(config),
        my_base(config)
    {}

    ~redis_pool() noexcept override
    {}

    redis get_redis()
    {
        return redis(std::static_pointer_cast<client>(borrow_object()));
    }

private:

    std::shared_ptr<detail::pool_object> create_object() override
    {
        return std::static_pointer_cast<detail::pool_object>(
            std::make_shared<client>(host_, port_, config_));
    }
};

} // namespace czredis


