#ifndef LIA_MAYBE_MASTER_HPP
#define LIA_MAYBE_MASTER_HPP

#include "maybe/maybe.hpp"

namespace lia {
template<typename T>
inline maybe<Decay<T>> just(T&& value) {
    return maybe<Decay<T>>{std::forward<T>(value)};
}

inline maybe<nothing_t> nothing() {
    return {};
}
} // lia

#endif // LIA_MAYBE_MASTER_HPP