#ifndef LIA_SEARCH_LIST_COMP_HPP
#define LIA_SEARCH_LIST_COMP_HPP

#include "../detail/type_traits.hpp"

namespace lia {
template<class Cont>
inline bool elem(Cont&& cont, ValueType<Unqualified<Cont>> t) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    for(; first != last; ++first) {
        if(*first == t)
            return true;
    }
    return false;
}

template<class Cont>
inline bool not_elem(Cont&& cont, ValueType<Unqualified<Cont>> t) {
    return !elem(std::forward<Cont>(cont), t);
}
} // lia

#endif // LIA_SEARCH_LIST_COMP_HPP