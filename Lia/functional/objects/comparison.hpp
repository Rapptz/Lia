#ifndef LIA_COMPARISON_FUNCTIONAL_OBJ_HPP
#define LIA_COMPARISON_FUNCTIONAL_OBJ_HPP

#include <utility>

namespace lia {
struct equal_to {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) == std::forward<U>(u)) {
        return std::forward<T>(t) == std::forward<U>(u);
    }
};

struct not_equal_to {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) != std::forward<U>(u)) {
        return std::forward<T>(t) != std::forward<U>(u);
    }
};

struct greater {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) > std::forward<U>(u)) {
        return std::forward<T>(t) > std::forward<U>(u);
    }
};

struct less {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) < std::forward<U>(u)) {
        return std::forward<T>(t) < std::forward<U>(u);
    }
};

struct greater_equal {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) >= std::forward<U>(u)) {
        return std::forward<T>(t) >= std::forward<U>(u);
    }
};

struct less_equal {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) <= std::forward<U>(u)) {
        return std::forward<T>(t) <= std::forward<U>(u);
    }
};
} // lia

#endif // LIA_COMPARISON_FUNCTIONAL_OBJ_HPP