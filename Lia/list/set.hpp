#ifndef LIA_SET_LIST_COMP_HPP
#define LIA_SET_LIST_COMP_HPP

#include "../detail/type_traits.hpp"
#include <algorithm>
#include <unordered_set>

namespace lia {
template<class Cont>
inline Unqualified<Cont> nub(Cont&& cont) {
    std::unordered_set<ValueType<Unqualified<Cont>>> hashed;
    Unqualified<Cont> result;
    auto first = std::begin(std::forward<Cont>(cont));
    auto last = std::end(std::forward<Cont>(cont));
    for(; first != last; ++first) {
        if(hashed.find(*first) != std::end(hashed))
            continue;
        result.push_back(*first);
        hashed.insert(*first);
    }
    return result;
}
} // lia

#endif // LIA_SET_LIST_COMP_HPP
