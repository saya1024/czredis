#pragma once

#include "detail/client.h"
#include "pipeline.h"

namespace czredis
{

class redis : private asio::noncopyable
{
    using client = detail::client;
    using unique_ptr = std::unique_ptr<client, std::function<void(client*)>>;
    friend class redis_pool;

public:
    using cref_string = const rds_string&;
    using init_strings = std::initializer_list<rds_string>;

    redis(const std::string&    host    = "localhost",
          const std::string&    port    = "6379",
          const redis_config&   config  = redis_config()) :
        client_ptr_(new client(host, port, config), [](client* c) { delete c; }),
        client_(*client_ptr_)
    {
    }

    redis(redis&& r) :
        client_ptr_(std::move(r.client_ptr_)),
        client_(*client_ptr_)
    {
    }

    redis(unique_ptr&& ptr) :
        client_ptr_(std::move(ptr)),
        client_(*client_ptr_)
    {
    }

    virtual ~redis()
    {
    }

    void connect()
    {
        client_.do_connect();
    }

    void disconnect() noexcept
    {
        client_.disconnect();
    }

    pipeline get_pipline()
    {
        return pipeline(*client_ptr_);
    }


    bool auth(cref_string password)
    {
        client_.auth(password);
        read_reply().is_ok();
    }

    rds_string echo(cref_string message)
    {
        client_.echo(message);
        return read_reply().as_string();
    }

    bool ping()
    {
        client_.ping();
        return read_reply().is_pong();
    }

    void quit()
    {
        client_.quit();
        disconnect();
    }

    bool select(unsigned db)
    {
        client_.select(db);
        return read_reply().is_ok();
    }

private:
    unique_ptr client_ptr_;
    client& client_;

    reply read_reply()
    {
        client_.read_reply();
    }
};

} // namespace czredis

