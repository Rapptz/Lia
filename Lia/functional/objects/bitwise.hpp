#ifndef LIA_BITWISE_FUNCTIONAL_OBJ_HPP
#define LIA_BITWISE_FUNCTIONAL_OBJ_HPP

#include <utility>

namespace lia {
struct bit_and {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) & std::forward<U>(u)) {
        return std::forward<T>(t) & std::forward<U>(u);
    }
};

struct bit_or {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) | std::forward<U>(u)) {
        return std::forward<T>(t) | std::forward<U>(u);
    }
};

struct bit_xor {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) ^ std::forward<U>(u)) {
        return std::forward<T>(t) ^ std::forward<U>(u);
    }
};

struct bit_not {
    template<typename T>
    auto operator()(T&& t) -> decltype(~std::forward<T>(t)) {
        return ~std::forward<T>(t);
    }
};
} // lia

#endif // LIA_BITWISE_FUNCTIONAL_OBJ_HPP