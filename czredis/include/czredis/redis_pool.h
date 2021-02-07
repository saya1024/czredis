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
        config_(config),
        my_base(config.max_size, config.max_idle)
    {
    }

    virtual ~redis_pool() noexcept override
    {
    };

    redis get_redis()
    {
        auto c = borrow_object();
        if (c == nullptr)
        {
            throw redis_pool_exhausted_error();
        }
        if (c->is_connected())
        {
            if (c->database() != config_.database)
                c->select(config_.database);
            c->read_all_reply();
        }
        else
        {
            c->set_database(config_.database);
            c->do_connect();
        }
        return c;
    }

protected:
    virtual void when_return(client* c) noexcept override
    {
        try
        {
            if (c->is_connected())
            {
                if (c->is_in_multi())
                    c->discard();
                if (c->is_in_watch())
                    c->unwatch();
                c->read_all_reply();
            }
        }
        catch (const std::exception&)
        {
            c->disconnect();
        }
    }

    virtual client* new_object() override
    {
        return new client(host_, port_, config_);
    }

    virtual void delete_object(client* c) noexcept override
    {
        delete c;
    }

    std::string  host_;
    std::string  port_;
    redis_config config_;
};

} // namespace czredis


