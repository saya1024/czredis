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
        for (auto& r : read_results())
        {
            if (r.is_error())
                return false;
        }
        return true;
    }

    bool exec_and_reply(reply_array& results)
    {
        exec();
        auto arr = read_results();
        for (auto& r : arr)
        {
            if (r.is_error())
                return false;
        }
        results = arr.back().as_array();
        return true;
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