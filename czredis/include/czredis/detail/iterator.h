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
public:
    v2_iterator(iterator1 it1, iterator2 it2) :
        it1_(it1), it2_(it2)
    {}

    bool operator==(v2_iterator<T1, T2> that) const noexcept
    {
        return (it1_ == that.it1_) == (it2_ == that.it2_);
    }

    bool operator!=(v2_iterator<T1, T2> that) const noexcept
    {
        return (it1_ != that.it1_) || (it2_ != that.it2_);
    }

    std::pair<T1&, T2&> operator*() const noexcept
    {
        return { *it1_, *it2_ };
    }

    v2_iterator& operator++()
    {
        it1_++;
        it2_++;
        return this;
    }

private:
    iterator1 it1_;
    iterator2 it2_;
};

} // namespace detail
} // namespace czredis