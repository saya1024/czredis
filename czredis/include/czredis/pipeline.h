#pragma once

#include "detail/client.h"

namespace czredis
{

class pipeline : public detail::command_interface
{
    using client = detail::client;
    friend class redis;

public:
    using cref_string = const rds_string&;
    using init_strings = std::initializer_list<rds_string>;

    reply_array read_results()
    {
        return client_.read_all_reply();
    }

    bool discard_and_reply()
    {
        discard();
        return read_results().back().is_ok();
    }

    bool exec_and_reply(reply_array& results)
    {
        exec();
        auto r = read_results().back();
        if (r.is_array())
        {
            results = std::move(r.as_array());
            return true;
        }
        return false;
    }

    bool is_in_multi() const noexcept
    {
        return client_.is_in_multi();
    }

    bool is_in_watch() const noexcept
    {
        return client_.is_in_watch();
    }


    virtual void auth(cref_string password) override
    {
        client_.auth(password);
    }

    virtual void echo(cref_string message) override
    {
        client_.echo(message);
    }

    virtual void ping() override
    {
        client_.ping();
    }

    virtual void quit() override
    {
        client_.quit();
        client_.disconnect();
    }

    virtual void select(unsigned db) override
    {
        client_.select(db);
    }


    virtual void append(cref_string key, cref_string value) override
    {
        client_.append(key, value);
    }

    virtual void bitcount(cref_string key, rds_integer start, rds_integer end) override
    {
        client_.bitcount(key, start, end);
    }

    virtual void bitop(cref_string operation, cref_string dest_key, init_strings keys) override
    {
        client_.bitop(operation, dest_key, keys);
    }

    virtual void decr(cref_string key) override
    {
        client_.decr(key);
    }

    virtual void decrby(cref_string key, rds_integer decrement) override
    {
        client_.decrby(key, decrement);
    }

    virtual void get(cref_string key) override
    {
        client_.get(key);
    }

    virtual void getbit(cref_string key, rds_integer offset) override
    {
        client_.getbit(key, offset);
    }

    virtual void getrange(cref_string key, rds_integer start, rds_integer end) override
    {
        client_.getrange(key, start, end);
    }

    virtual void getset(cref_string key, cref_string value) override
    {
        client_.getset(key, value);
    }

    virtual void incr(cref_string key) override
    {
        client_.incr(key);
    }

    virtual void incrby(cref_string key, rds_integer increment)
    {
        client_.incrby(key, increment);
    }

    virtual void incrbyfloat(cref_string key, double increment) override
    {
        client_.incrbyfloat(key, increment);
    }

    virtual void mget(init_strings keys) override
    {
        client_.mget(keys);
    }

    virtual void mset(init_strings key_value_pairs) override
    {
        client_.mset(key_value_pairs);
    }

    virtual void msetnx(init_strings key_value_pairs) override
    {
        client_.mset(key_value_pairs);
    }

    virtual void psetex(cref_string key, rds_integer milliseconds, cref_string value) override
    {
        client_.psetex(key, milliseconds, value);
    }

    virtual void set(cref_string key, cref_string value, init_strings params = {}) override
    {
        client_.set(key, value, params);
    }

    virtual void setbit(cref_string key, rds_integer offset, bool value) override
    {
        client_.setbit(key, offset, value);
    }

    virtual void setex(cref_string key, rds_integer seconds, cref_string value) override
    {
        client_.setex(key, seconds, value);
    }

    virtual void setnx(cref_string key, cref_string value)
    {
        client_.setnx(key, value);
    }

    virtual void setrange(cref_string key, rds_integer offset, cref_string value) override
    {
        client_.setrange(key, offset, value);
    }

    virtual void strlen(cref_string key) override
    {
        client_.strlen(key);
    }

    
    virtual void unwatch() override
    {
        client_.unwatch();
    }

    virtual void watch(init_strings keys) override
    {
        client_.watch(keys);
    }

    virtual void discard() override
    {
        client_.discard();
    }

    virtual void exec() override
    {
        client_.exec();
    }

    virtual void multi() override
    {
        client_.multi();
    }

protected:
    pipeline(client& c) :
        client_(c)
    {
    }

private:
    client& client_;
};

}