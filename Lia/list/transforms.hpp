#ifndef LIA_TRANSFORMS_LIST_COMP_HPP
#define LIA_TRANSFORMS_LIST_COMP_HPP

#include "../detail/iterator.hpp"
#include "../detail/type_traits.hpp"
#include <algorithm>

namespace lia {
template<class Cont, typename Map>
inline auto map(const Cont& cont, Map&& mapped) -> Rebind<Cont, ResultOf<Unqualified<Map>>> {
    Rebind<Cont, ResultOf<Unqualified<Map>>> result;
    std::transform(std::begin(cont),std::end(cont), std::back_inserter(result),mapped);
    return result;
}

template<class Cont>
inline Unqualified<Cont> reverse(Cont&& cont) {
    Unqualified<Cont> result;
    std::reverse_copy(std::begin(cont), std::end(cont), std::back_inserter(result));
    return result;
}

template<class Cont>
inline Unqualified<Cont> intersperse(const Cont& cont, ValueType<Unqualified<Cont>> elem) {
    Unqualified<Cont> result;
    auto first = std::begin(cont);
    auto last = std::end(cont);
    if(first != last)
        result.push_back(*first++);
    while(first != last) {
        result.push_back(elem);
        result.push_back(*first++);
    }
    return result;
}

template<class Cont>
inline auto subsequences(const Cont& cont) -> Rebind<Cont, Unqualified<Cont>> {
    Rebind<Cont, Unqualified<Cont>> result;
    auto first = std::begin(cont);
    Unqualified<Cont> temp;
    auto max = 1ULL << cont.size();
    for(unsigned i = 0; i < max; ++i) {
        for(unsigned j = 0, h = i; h; h >>= 1, ++j) {
            if(h & 1)
                temp.push_back(*(first + j));
        }
        result.push_back(temp);
        temp.clear();
    }
    return result;
}

template<class Cont>
inline auto permutations(Cont cont) -> Rebind<Unqualified<Cont>, Unqualified<Cont>> {
    Rebind<Unqualified<Cont>, Unqualified<Cont>> result;
    do {
        result.push_back(cont);
    }
    while(std::next_permutation(std::begin(cont), std::end(cont)));
    return result;
}
} // lia

#endif // LIA_TRANSFORMS_LIST_COMP_HPP