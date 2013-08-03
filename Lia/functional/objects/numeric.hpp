#ifndef LIA_NUMERIC_FUNCTIONAL_OBJ_HPP
#define LIA_NUMERIC_FUNCTIONAL_OBJ_HPP

#include <utility>

namespace lia {
struct even {
    template<typename T>
    auto operator()(T&& t) -> decltype(std::forward<T>(t) % 2 == 0) {
        return std::forward<T>(t) % 2 == 0;
    }
};

struct odd {
    template<typename T>
    auto operator()(T&& t) -> decltype(std::forward<T>(t) % 2 != 0) {
        return std::forward<T>(t) % 2 != 0;
    }
};
}

#endif // LIA_NUMERIC_FUNCTIONAL_OBJ_HPP