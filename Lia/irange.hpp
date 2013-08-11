#ifndef LIA_IRANGE_HPP
#define LIA_IRANGE_HPP

#include "irange/numeric_range.hpp"

namespace lia {
template<typename T>
constexpr numeric_range<T, true> irange(T begin) {
    return {begin};
}

template<typename T, typename R = numeric_range<T>>
constexpr R irange(T begin, T end) {
    return end >= begin ? R{begin, ++end} : R{begin, --end, -1};
}
} // lia

#endif // LIA_IRANGE_HPP