#pragma once

#include "common.h"

namespace czredis
{

using redis_error = std::runtime_error;

class redis_io_error : public redis_error
{
public:
    explicit redis_io_error(const asio::error_code& ec) :
        redis_error("redis asio error: " + ec.message())
    {}

    explicit redis_io_error(cref_string msg) :
        redis_error("redis io error: " + msg)
    {}
};

class redis_connection_error : public redis_error
{
public:
    explicit redis_connection_error(cref_string msg) :
        redis_error("redis connection error: " + msg)
    {}
};

class redis_commmand_error : public redis_error
{
public:
    explicit redis_commmand_error(cref_string msg) :
        redis_error("redis commmand error: " + msg)
    {}
};

class redis_data_error : public redis_error
{
public:
    explicit redis_data_error(cref_string msg) :
        redis_error("redis data error: " + msg)
    {}
};

class redis_pool_exhausted_error : public redis_error
{
public:
    explicit redis_pool_exhausted_error() :
        redis_error("redis pool is exhausted")
    {}
};

} // namespace czredis
