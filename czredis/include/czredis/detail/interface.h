#pragma once

#include "../delay.h"
#include "../data.h"
#include "../params.h"
#include "interface/connection.h"
#include "interface/geo.h"
#include "interface/hashes.h"
#include "interface/hyper_log_log.h"
#include "interface/keys.h"
#include "interface/lists.h"
#include "interface/scripting.h"
#include "interface/server.h"
#include "interface/sets.h"
#include "interface/sorted_sets.h"
#include "interface/streams.h"
#include "interface/strings.h"
#include "interface/transactions.h"

namespace czredis
{
namespace detail
{

struct i_commands :
    public i_connection,
    public i_geo,
    public i_hashes,
    public i_hyper_log_log,
    public i_keys,
    public i_lists,
    public i_scripting,
    public i_server,
    public i_sets,
    public i_sorted_sets,
    public i_streams,
    public i_strings,
    public i_transactions
{};

struct i_one_key_direct_commands :
    public i_one_key_direct_geo,
    public i_one_key_direct_hashes,
    public i_one_key_direct_hyper_log_log,
    public i_one_key_direct_keys,
    public i_one_key_direct_lists,
    public i_one_key_direct_server,
    public i_one_key_direct_sets,
    public i_one_key_direct_sorted_sets,
    public i_one_key_direct_streams,
    public i_one_key_direct_strings
{};

struct i_direct_commands :
    public i_direct_connection,
    public i_direct_geo,
    public i_direct_hashes,
    public i_direct_hyper_log_log,
    public i_direct_keys,
    public i_direct_lists,
    public i_direct_scripting,
    public i_direct_server,
    public i_direct_sets,
    public i_direct_sorted_sets,
    public i_direct_streams,
    public i_direct_strings
{};

struct i_one_key_delay_commands :
    public i_one_key_delay_geo,
    public i_one_key_delay_hashes,
    public i_one_key_delay_hyper_log_log,
    public i_one_key_delay_keys,
    public i_one_key_delay_lists,
    public i_one_key_delay_server,
    public i_one_key_delay_sets,
    public i_one_key_delay_sorted_sets,
    public i_one_key_delay_streams,
    public i_one_key_delay_strings
{};

struct i_delay_commands :
    public i_delay_geo,
    public i_delay_hashes,
    public i_delay_hyper_log_log,
    public i_delay_keys,
    public i_delay_lists,
    public i_delay_scripting,
    public i_delay_server,
    public i_delay_sets,
    public i_delay_sorted_sets,
    public i_delay_streams,
    public i_delay_strings
{};

} // namespace detail
} // namespace czredis


