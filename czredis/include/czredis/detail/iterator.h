#pragma once

#include <utility>
#include <vector>

namespace czredis
{
namespace detail
{

template<typename T1, typename T2>
class v2_iterator
{
    typedef typename std::vector<T1>::iterator iterator1;
    typedef typename std::vector<T2>::iterator iterator2;

    iterator1 it1_;
    iterator2 it2_;

public:
    v2_iterator(iterator1 it1, iterator2 it2) :
        it1_(it1), it2_(it2)
    {}

    std::pair<T1&, T2&> operator*()
    {
        return { *it1_, *it2_ };
    }

    v2_iterator operator++()
    {
        ++it1_;
        ++it2_;
        return { it1_, it2_ };
    }

    v2_iterator operator++(int)
    {
        auto temp = v2_iterator(it1_, it2_);
        ++it1_;
        ++it2_;
        return temp;
    }

    v2_iterator operator--()
    {
        --it1_;
        --it2_;
        return { it1_, it2_ };
    }

    v2_iterator operator--(int)
    {
        auto temp = v2_iterator(it1_, it2_);
        --it1_;
        --it2_;
        return temp;
    }

    v2_iterator operator+(std::ptrdiff_t offset)
    {
        return { it1_ + offset, it2_ + offset };
    }

    v2_iterator operator-(std::ptrdiff_t offset)
    {
        return { it1_ - offset, it2_ - offset };
    }

    bool operator==(v2_iterator<T1, T2> that) const
    {
        return (it1_ == that.it1_) == (it2_ == that.it2_);
    }

    bool operator!=(v2_iterator<T1, T2> that) const
    {
        return (it1_ != that.it1_) || (it2_ != that.it2_);
    }
};

} // namespace detail
} // namespace czredis