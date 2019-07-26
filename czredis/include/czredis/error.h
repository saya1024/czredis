#pragma once

namespace czredis
{

using redis_error = std::runtime_error;

class redis_connection_error : public redis_error
{
public:
    explicit redis_connection_error(const std::string& msg) :
        redis_error("Redis connection error: " + msg)
    {
    }

    explicit redis_connection_error(asio::error_code ec) :
        redis_error("Redis connection error: asio error :" + ec.message())
    {
    }
};

class redis_commmand_error : public redis_error
{
public:
    explicit redis_commmand_error(const std::string& msg) :
        redis_error("Redis commmand error: " + msg)
    {
    }
};

class redis_data_error : public redis_error
{
public:
    explicit redis_data_error(const std::string& msg) :
        redis_error("Redis reply error: " + msg)
    {
    }
};

class redis_pool_exhausted_error : public redis_error
{
public:
    explicit redis_pool_exhausted_error() :
        redis_error("Redis pool is exhausted")
    {
    }
};

} // namespace czredis
