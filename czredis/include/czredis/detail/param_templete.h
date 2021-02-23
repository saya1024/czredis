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
            if (!name.empty())
                params.emplace_back(name);
        }
    }
};

template<typename VAL1>
class param1 : public param0
{
public:
    VAL1 value1;

    param1(const char* n) :
        param0(n),
        value1{}
    {}

    void append_param(string_array& params) const
    {
        if (use)
        {
            if (!name.empty())
                params.emplace_back(name);
            params.emplace_back(val_to_str(value1));
        }
    }
};

template<typename VAL1, typename VAL2>
class param2 : public param1<VAL1>
{
    using my_base = param1<VAL1>;

public:
    VAL2 value2;

    param2(const char* n) :
        my_base(n),
        value2{}
    {}

    void append_param(string_array& params) const
    {
        if (my_base::use)
        {
            if (!my_base::name.empty())
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
            if (!name.empty())
                params.emplace_back(name);
            auto length = values.size();
            for (size_t i = 0; i < length; i++)
            {
                params.emplace_back(val_to_str(values[i]));
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
            auto length = values.size();
            for (size_t i = 0; i < length; i++)
            {
                if (!name.empty())
                    params.emplace_back(name);
                params.emplace_back(val_to_str(values[i]));
            }
        }
    }
};

class param_templete
{
public:
    virtual void append_params(string_array& cmd_params) const = 0;

    string_array to_string_array() const
    {
        string_array params;
        append_params(params);
        return params;
    }

protected:
    template<typename T>
    static void fill_up(string_array& cmd_params, T param)
    {
        param.append_param(cmd_params);
    }

    template<typename T, typename...PARAMS>
    static void fill_up(string_array& cmd_params, T param, PARAMS ...params)
    {
        param.append_param(cmd_params);
        fill_up(cmd_params, params...);
    }
};

} // namespace detail
} // namespace czredis