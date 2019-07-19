#pragma once

#include "detail/client.h"

namespace czredis
{

class redis : private asio::noncopyable
{
    using client = detail::client;
    using client_ptr = std::unique_ptr<client>;
    using unique_ptr = std::unique_ptr<client, std::function<void(client*)>>;
    friend class redis_pool;

public:
    redis(const std::string&    host    = "localhost",
          const std::string&    port    = "6379",
          const redis_config&   config  = redis_config()) :
        client_ptr_(new client(host, port, config), [](client* c) { delete c; })
    {
    }

    redis(redis&& r) :
        client_ptr_(std::move(r.client_ptr_))
    {
    }

    redis(unique_ptr&& ptr) :
        client_ptr_(std::move(ptr))
    {
    }

    virtual ~redis()
    {
    }

    void connect()
    {
        client_ptr_->connect();
    }

    void disconnect() noexcept
    {
        client_ptr_->disconnect();
    }

private:
    unique_ptr client_ptr_;
};

} // namespace czredis

