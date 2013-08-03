#ifndef LIA_LOGICAL_FUNCTIONAL_OBJ_HPP
#define LIA_LOGICAL_FUNCTIONAL_OBJ_HPP

#include <utility>

namespace lia {
struct logical_and {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) && std::forward<U>(u)) const {
        return std::forward<T>(t) && std::forward<U>(u);
    }
};

struct logical_or {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) || std::forward<U>(u)) const {
        return std::forward<T>(t) || std::forward<U>(u);
    }
};

struct logical_not {
    template<typename T>
    auto operator()(T&& t) -> decltype(!std::forward<T>(t)) const {
        return !std::forward<T>(t);
    }
};
} // lia

#endif // LIA_LOGICAL_FUNCTIONAL_OBJ_HPP