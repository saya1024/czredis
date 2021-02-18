#pragma once

namespace czredis
{
namespace detail
{

template<typename VAL>
czstring val_to_str(VAL value)
{
    return std::to_string(value);
}

inline czstring val_to_str(const czstring& value)
{
    return value;
}

class param0
{
public:
    const czstring name;
    bool use = false;

    param0(const char* n) : name(n) {}

    void append_param(string_array& params) const
    {
        if (use)
        {
            params.emplace_back(name);
        }
    }
};

template<typename VAL1>
class param1 : public param0
{
public:
    VAL1 value1;

    param1(const char* n) : param0(n) {}

    void append_param(string_array& params) const
    {
        if (use)
        {
            params.emplace_back(name);
            params.emplace_back(val_to_str(value1));
        }
    }
};

template<typename VAL1, typename VAL2>
class param2 :public param1<VAL1>
{
public:
    VAL2 value2;

    param2(const char* n) : param1<VAL1>(n) {}

    void append_param(string_array& params) const
    {
        if (param1<VAL1>::use)
        {
            params.emplace_back(param1<VAL1>::name);
            params.emplace_back(val_to_str(param1<VAL1>::value1));
            params.emplace_back(val_to_str(value2));
        }
    }
};

template<typename VAL>
class param_array : public param0
{
public:
    std::vector<VAL> values;

    param_array(const char* n) : param0(n) {}

    void append_param(string_array& params) const
    {
        if (use)
        {
            params.emplace_back(name);
            for (auto& v : values)
            {
                params.emplace_back(val_to_str(v));
            }
        }
    }
};

template<typename VAL>
class param_repeat : public param0
{
public:
    std::vector<VAL> values;

    param_repeat(const char* n) : param0(n) {}

    void append_param(string_array& params) const
    {
        if (use)
        {
            for (auto& v : values)
            {
                params.emplace_back(name);
                params.emplace_back(val_to_str(v));
            }
        }
    }
};

template<typename PARAM1, typename PARAM2>
void only_one_of_params(PARAM1 p1, PARAM2 p2)
{
    if (p1.use && p2.use)
        throw redis_commmand_error("ERR only one of "
            + p1.name + " and " + p2.name + " can be used");
}

class param_templete
{
public:
    virtual void append_params(string_array& params) const = 0;

    string_array to_string_array() const
    {
        string_array params;
        append_params(params);
        return params;
    }
};

} // namespace detail
} // namespace czredis