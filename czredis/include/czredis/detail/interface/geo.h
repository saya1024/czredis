#pragma once

namespace czredis
{
namespace detail
{

struct i_geo
{
    virtual void geoadd(cref_string key, double longitude, double latitude, cref_string member) = 0;
    virtual void geoadd(cref_string key, tmap<czstring, geo_coordinate> members_coordinates) = 0;
    virtual void geodist(cref_string key, cref_string member1, cref_string member2, geo_unit unit) = 0;
    virtual void geohash(cref_string key, cref_string_array members) = 0;
    virtual void geopos(cref_string key, cref_string_array members) = 0;
    virtual void georadius(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param, const georadius_store_param& store_param) = 0;
    virtual void georadius_RO(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param) = 0;
    virtual void georadiusbymember(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param, const georadius_store_param& store_param) = 0;
    virtual void georadiusbymember_RO(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param) = 0;
};

struct i_one_key_direct_geo
{
    virtual czint geoadd(cref_string key, double longitude, double latitude, cref_string member) = 0;
    virtual czint geoadd(cref_string key, tmap<czstring, geo_coordinate> members_coordinates) = 0;
    virtual reply geodist(cref_string key, cref_string member1, cref_string member2, geo_unit unit) = 0;
    virtual reply_array geohash(cref_string key, cref_string_array members) = 0;
    virtual reply_array geopos(cref_string key, cref_string_array members) = 0;
    virtual reply_array georadius(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param) = 0;
    virtual reply_array georadius_RO(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param) = 0;
    virtual reply_array georadiusbymember(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param) = 0;
    virtual reply_array georadiusbymember_RO(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param) = 0;
};

struct i_direct_geo
{
    virtual reply_array georadius(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param, const georadius_store_param& store_param) = 0;
    virtual reply_array georadiusbymember(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param, const georadius_store_param& store_param) = 0;
};

struct i_one_key_delay_geo
{
    virtual delay<czint> geoadd(cref_string key, double longitude, double latitude, cref_string member) = 0;
    virtual delay<czint> geoadd(cref_string key, tmap<czstring, geo_coordinate> members_coordinates) = 0;
    virtual delay<reply> geodist(cref_string key, cref_string member1, cref_string member2, geo_unit unit) = 0;
    virtual delay<reply_array> geohash(cref_string key, cref_string_array members) = 0;
    virtual delay<reply_array> geopos(cref_string key, cref_string_array members) = 0;
    virtual delay<reply_array> georadius(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param) = 0;
    virtual delay<reply_array> georadius_RO(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param) = 0;
    virtual delay<reply_array> georadiusbymember(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param) = 0;
    virtual delay<reply_array> georadiusbymember_RO(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param) = 0;
};

struct i_delay_geo
{
    virtual delay<reply_array> georadius(cref_string key, double longitude, double latitude, double radius,
        geo_unit unit, const georadius_param& param, const georadius_store_param& store_param) = 0;
    virtual delay<reply_array> georadiusbymember(cref_string key, cref_string member, double radius,
        geo_unit unit, const georadius_param& param, const georadius_store_param& store_param) = 0;
};

} // namespace detail
} // namespace czredis

