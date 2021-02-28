#pragma once

#include "common.h"

namespace czredis
{

using redis_error = std::runtime_error;

class redis_io_error : public redis_error
{
public:
    explicit redis_io_error(asio::error_code ec) :
        redis_error("io error: " + ec.message())
    {}
};

class redis_connection_error : public redis_error
{
public:
    explicit redis_connection_error(const std::string& msg) :
        redis_error("connection error: " + msg)
    {}
};

class redis_commmand_error : public redis_error
{
public:
    explicit redis_commmand_error(const std::string& msg) :
        redis_error("commmand error: " + msg)
    {}
};

class redis_data_error : public redis_error
{
public:
    explicit redis_data_error(const std::string& msg) :
        redis_error("data error: " + msg)
    {}
};

class redis_pool_exhausted_error : public redis_error
{
public:
    explicit redis_pool_exhausted_error() :
        redis_error("pool is exhausted")
    {}
};

} // namespace czredis
