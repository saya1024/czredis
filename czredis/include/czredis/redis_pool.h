#pragma once

#include "detail/pool.h"
#include "redis.h"

namespace czredis
{

class redis_pool: public detail::pool<detail::client>
{
    using client = detail::client;
    using my_base = detail::pool<client>;
public:
    redis_pool(const std::string&       host,
               const std::string&       port,
               const redis_pool_config& config = redis_pool_config()) :
        host_(host),
        port_(port),
        redis_config_(config),
        my_base(config.max_size, config.max_idle)
    {
    }

    virtual ~redis_pool() noexcept override
    {
    };

    redis get_redis()
    {
        auto p = borrow_object();
        if (p == nullptr)
        {
            throw redis_pool_exhausted_error();
        }
        return std::move(p);
    }

protected:
    virtual void when_return(client* c) noexcept override
    {
        try
        {
            if (c->is_in_multi())
                c->discard();
            if (c->is_in_watch())
                c->unwatch();
            c->read_all_reply();
        }
        catch (const std::exception&)
        {
            c->disconnect();
        }
    }

    virtual client* new_object() override
    {
        return new client(host_, port_, redis_config_);
    }

    virtual void delete_object(client* c) noexcept override
    {
        delete c;
    }

    std::string  host_;
    std::string  port_;
    redis_config redis_config_;
};

} // namespace czredis


