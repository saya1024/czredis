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
    using cref_string = const czstring&;
    using init_string_list = std::initializer_list<czstring>;

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
        return read_reply().is_ok();
    }

    czstring echo(cref_string message)
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


    czint append(cref_string key, cref_string value)
    {
        client_.append(key, value);
        return read_reply().as_integer();
    }

    czint bitcount(cref_string key)
    {
        client_.bitcount(key, 0, -1);
        return read_reply().as_integer();
    }

    czint bitcount(cref_string key, czint start, czint end)
    {
        client_.bitcount(key, start, end);
        return read_reply().as_integer();
    }

    czint bitop(cref_string operation, cref_string dest_key, init_string_list keys)
    {
        client_.bitop(operation, dest_key, keys);
        return read_reply().as_integer();
    }

    czint decr(cref_string key)
    {
        client_.decr(key);
        return read_reply().as_integer();
    }
    czint decrby(cref_string key, czint decrement)
    {
        client_.decrby(key, decrement);
        return read_reply().as_integer();
    }

    reply get(cref_string key)
    {
        client_.get(key);
        return read_reply();
    }

    bool getbit(cref_string key, czint offset)
    {
        client_.getbit(key, offset);
        return read_reply().as_integer() == 1;
    }

    czstring getrange(cref_string key, czint start, czint end)
    {
        client_.getrange(key, start, end);
        return read_reply().as_string();
    }

    reply getset(cref_string key, cref_string value)
    {
        client_.getset(key, value);
        return read_reply();
    }

    czint incr(cref_string key)
    {
        client_.incr(key);
        return read_reply().as_integer();
    }

    czint incrby(cref_string key, czint increment)
    {
        client_.incrby(key, increment);
        return read_reply().as_integer();
    }

    double incrbyfloat(cref_string key, double increment)
    {
        client_.incrbyfloat(key, increment);
        return std::stod(read_reply().as_string());
    }

    reply_array mget(init_string_list keys)
    {
        client_.mget(keys);
        return read_reply().as_array();
    }

    bool mset(init_string_list key_value_pairs)
    {
        client_.mset(key_value_pairs);
        return read_reply().is_ok();
    }

    bool msetnx(init_string_list key_value_pairs)
    {
        client_.msetnx(key_value_pairs);
        return read_reply().as_integer() == 1;
    }

    bool psetex(cref_string key, czint milliseconds, cref_string value)
    {
        client_.psetex(key, milliseconds, value);
        return read_reply().is_ok();
    }

    bool set(cref_string key, cref_string value, init_string_list params = {})
    {
        client_.set(key, value, params);
        return read_reply().is_ok();
    }

    czbit setbit(cref_string key, czint offset, czbit bit)
    {
        client_.setbit(key, offset, bit);
        return static_cast<czbit>(read_reply().as_integer());
    }

    bool setex(cref_string key, czint seconds, cref_string value)
    {
        client_.setex(key, seconds, value);
        return read_reply().is_ok();
    }

    bool setnx(cref_string key, cref_string value)
    {
        client_.setnx(key, value);
        return read_reply().as_integer() == 1;
    }

    czint setrange(cref_string key, czint offset, cref_string value)
    {
        client_.setrange(key, offset, value);
        return read_reply().as_integer();
    }

    czint strlen(cref_string key)
    {
        client_.strlen(key);
        return read_reply().as_integer();
    }


private:
    unique_ptr client_ptr_;
    client& client_;

    reply read_reply()
    {
        auto r = client_.read_reply();
        if (r.is_error())
            throw redis_commmand_error(r.as_string());
        return std::move(r);
    }
};

} // namespace czredis

