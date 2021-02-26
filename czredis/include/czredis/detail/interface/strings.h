#pragma once

namespace czredis
{
namespace detail
{

struct i_strings
{
    virtual void append(cref_string key, cref_string value) = 0;
    virtual void bitcount(cref_string key) = 0;
    virtual void bitcount(cref_string key, czint start, czint end) = 0;
    virtual void bitfield(cref_string key, cref_string_array arguments) = 0;
    virtual void bitfield_RO(cref_string key, cref_string_array arguments) = 0;
    virtual void bitop(bit_operation operation, cref_string destkey, cref_string_array keys) = 0;
    virtual void bitpos(cref_string key, czbit bit, const bitpos_param& param) = 0;
    virtual void decr(cref_string key) = 0;
    virtual void decrby(cref_string key, czint decrement) = 0;
    virtual void get(cref_string key) = 0;
    virtual void getbit(cref_string key, czint offset) = 0;
    virtual void getrange(cref_string key, czint start, czint end) = 0;
    virtual void getset(cref_string key, cref_string value) = 0;
    virtual void incr(cref_string key) = 0;
    virtual void incrby(cref_string key, czint increment) = 0;
    virtual void incrbyfloat(cref_string key, double increment) = 0;
    virtual void mget(cref_string_array keys) = 0;
    virtual void mset(cref_string_array keys_values) = 0;
    virtual void msetnx(cref_string_array keys_values) = 0;
    virtual void psetex(cref_string key, czint milliseconds, cref_string value) = 0;
    virtual void set(cref_string key, cref_string value) = 0;
    virtual void set(cref_string key, cref_string value, const set_param& param) = 0;
    virtual void setbit(cref_string key, czint offset, czbit bit) = 0;
    virtual void setex(cref_string key, czint seconds, cref_string value) = 0;
    virtual void setnx(cref_string key, cref_string value) = 0;
    virtual void setrange(cref_string key, czint offset, cref_string value) = 0;
    virtual void strlen(cref_string key) = 0;
};

struct i_one_key_direct_strings
{
    virtual czint append(cref_string key, cref_string value) = 0;
    virtual czint bitcount(cref_string key) = 0;
    virtual czint bitcount(cref_string key, czint start, czint end) = 0;
    virtual reply_array bitfield(cref_string key, cref_string_array arguments) = 0;
    virtual reply_array bitfield_RO(cref_string key, cref_string_array arguments) = 0;
    virtual czint bitpos(cref_string key, czbit bit, const bitpos_param& param) = 0;
    virtual czint decr(cref_string key) = 0;
    virtual czint decrby(cref_string key, czint decrement) = 0;
    virtual reply get(cref_string key) = 0;
    virtual czbit getbit(cref_string key, czint offset) = 0;
    virtual czstring getrange(cref_string key, czint start, czint end) = 0;
    virtual reply getset(cref_string key, cref_string value) = 0;
    virtual czint incr(cref_string key) = 0;
    virtual czint incrby(cref_string key, czint increment) = 0;
    virtual double incrbyfloat(cref_string key, double increment) = 0;
    virtual czstring psetex(cref_string key, czint milliseconds, cref_string value) = 0;
    virtual czstring set(cref_string key, cref_string value) = 0;
    virtual reply set(cref_string key, cref_string value, const set_param& param) = 0;
    virtual czbit setbit(cref_string key, czint offset, czbit bit) = 0;
    virtual czstring setex(cref_string key, czint seconds, cref_string value) = 0;
    virtual czint setnx(cref_string key, cref_string value) = 0;
    virtual czint setrange(cref_string key, czint offset, cref_string value) = 0;
    virtual czint strlen(cref_string key) = 0;
};

struct i_direct_strings
{
    virtual czint bitop(bit_operation operation, cref_string destkey, cref_string_array keys) = 0;
    virtual reply_array mget(cref_string_array keys) = 0;
    virtual czstring mset(cref_string_array keys_values) = 0;
    virtual czint msetnx(cref_string_array keys_values) = 0;
};

struct i_one_key_delay_strings
{
    virtual delay<czint> append(cref_string key, cref_string value) = 0;
    virtual delay<czint> bitcount(cref_string key) = 0;
    virtual delay<czint> bitcount(cref_string key, czint start, czint end) = 0;
    virtual delay<reply_array> bitfield(cref_string key, cref_string_array arguments) = 0;
    virtual delay<reply_array> bitfield_RO(cref_string key, cref_string_array arguments) = 0;
    virtual delay<czint> bitpos(cref_string key, czbit bit, const bitpos_param& param) = 0;
    virtual delay<czint> decr(cref_string key) = 0;
    virtual delay<czint> decrby(cref_string key, czint decrement) = 0;
    virtual delay<reply> get(cref_string key) = 0;
    virtual delay<czbit> getbit(cref_string key, czint offset) = 0;
    virtual delay<czstring> getrange(cref_string key, czint start, czint end) = 0;
    virtual delay<reply> getset(cref_string key, cref_string value) = 0;
    virtual delay<czint> incr(cref_string key) = 0;
    virtual delay<czint> incrby(cref_string key, czint increment) = 0;
    virtual delay<double> incrbyfloat(cref_string key, double increment) = 0;
    virtual delay<czstring> psetex(cref_string key, czint milliseconds, cref_string value) = 0;
    virtual delay<czstring> set(cref_string key, cref_string value) = 0;
    virtual delay<reply> set(cref_string key, cref_string value, const set_param& param) = 0;
    virtual delay<czbit> setbit(cref_string key, czint offset, czbit bit) = 0;
    virtual delay<czstring> setex(cref_string key, czint seconds, cref_string value) = 0;
    virtual delay<czint> setnx(cref_string key, cref_string value) = 0;
    virtual delay<czint> setrange(cref_string key, czint offset, cref_string value) = 0;
    virtual delay<czint> strlen(cref_string key) = 0;
};

struct i_delay_strings
{
    virtual delay<czint> bitop(bit_operation operation, cref_string destkey, cref_string_array keys) = 0;
    virtual delay<reply_array> mget(cref_string_array keys) = 0;
    virtual delay<czstring> mset(cref_string_array keys_values) = 0;
    virtual delay<czint> msetnx(cref_string_array keys_values) = 0;
};

} // namespace detail
} // namespace czredis

