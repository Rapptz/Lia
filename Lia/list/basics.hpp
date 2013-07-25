#ifndef LIA_BASICS_LIST_COMP_HPP
#define LIA_BASICS_LIST_COMP_HPP

// Includes
#include "../detail/type_traits.hpp"
#include "../detail/iterator.hpp"

namespace lia {
template<class Cont1, class Cont2>
inline Unqualified<Cont1> append(Cont1&& cont1, Cont2&& cont2) {
    Unqualified<Cont1> result(std::forward<Cont2>(cont2));
    result.insert(std::begin(result),
                  std::begin(cont1),
                  std::end(cont1));
    return result;
}

template<class Cont>
inline auto head(Cont&& cont) -> decltype(cont.front()) {
    return cont.front();
}

template<class Cont>
inline auto last(Cont&& cont) -> decltype(cont.back()) {
    return cont.back();
}

template<class Cont>
inline Unqualified<Cont> tail(Cont&& cont) {
    Unqualified<Cont> result(std::forward<Cont>(cont));
    result.erase(std::begin(result)); // Not all containers have pop_front
    return result;
}

template<class Cont>
inline Unqualified<Cont> init(Cont&& cont) {
    Unqualified<Cont> result(std::forward<Cont>(cont));
    result.pop_back();
    return result;
}

template<class Cont>
inline bool null(Cont&& cont) {
    return cont.empty();
}

template<class Cont>
inline size_t length(Cont&& cont) {
    return cont.size();
}
} // lia

#endif // LIA_BASICS_LIST_COMP_HPP