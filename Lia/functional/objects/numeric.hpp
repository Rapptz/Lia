#ifndef LIA_NUMERIC_FUNCTIONAL_OBJ_HPP
#define LIA_NUMERIC_FUNCTIONAL_OBJ_HPP

#include <utility>

namespace lia {
struct even {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) % std::forward<U>(u) == 0) {
        return std::forward<T>(t) % std::forward<U>(u) == 0;
    }
};

struct odd {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) % std::forward<U>(u) != 0) {
        return std::forward<T>(t) % std::forward<U>(u) != 0;
    }
};
}

#endif // LIA_NUMERIC_FUNCTIONAL_OBJ_HPP