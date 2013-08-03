#ifndef LIA_ARITHMETIC_FUNCTIONAL_OBJ_HPP
#define LIA_ARITHMETIC_FUNCTIONAL_OBJ_HPP

#include <utility>

namespace lia {
struct plus {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) + std::forward<U>(u)) {
        return std::forward<T>(t) + std::forward<U>(u);
    }
};

struct minus {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) - std::forward<U>(u)) {
        return std::forward<T>(t) - std::forward<U>(u);
    }
};

struct multiplies {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) * std::forward<U>(u)) {
        return std::forward<T>(t) * std::forward<U>(u);
    }
};

struct divides {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) / std::forward<U>(u)) {
        return std::forward<T>(t) / std::forward<U>(u);
    }
};

struct modulus {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) % std::forward<U>(u)) {
        return std::forward<T>(t) % std::forward<U>(u);
    }
};

struct lshift {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) << std::forward<U>(u)) {
        return std::forward<T>(t) << std::forward<U>(u);
    }
};

struct rshift {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) >> std::forward<U>(u)) {
        return std::forward<T>(t) >> std::forward<U>(u);
    }
};
} // lia

#endif // LIA_ARITHMETIC_FUNCTIONAL_OBJ_HPP