#ifndef LIA_TRANSFORMS_LIST_COMP_HPP
#define LIA_TRANSFORMS_LIST_COMP_HPP

#include "../detail/iterator.hpp"
#include "../detail/type_traits.hpp"
#include "../functional/objects/comparison.hpp"
#include <algorithm>

namespace lia {
template<class Cont, typename Function>
inline auto map(Cont&& cont, Function&& f) -> Rebind<Unqualified<Cont>, decltype(f(cont.back()))> {
    Rebind<Unqualified<Cont>, decltype(f(cont.back()))> result;
    std::transform(std::begin(cont),std::end(cont), std::back_inserter(result), f);
    return result;
}

template<class Cont>
inline Unqualified<Cont> reverse(Cont cont) {
    std::reverse(std::begin(cont), std::end(cont));
    return cont;
}

template<class Cont>
inline Unqualified<Cont> intersperse(Cont&& cont, ValueType<Cont> elem) {
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
inline auto subsequences(Cont&& cont) -> Rebind<Unqualified<Cont>, Unqualified<Cont>> {
    Rebind<Unqualified<Cont>, Unqualified<Cont>> result;
    auto first = std::begin(cont);
    Unqualified<Cont> temp;
    auto max = 1ULL << cont.size();
    for(unsigned i = 0; i < max; ++i) {
        for(unsigned j = 0, h = i; h; h >>= 1, ++j) {
            if(h & 1) {
                auto iter = std::next(first, j);
                temp.push_back(*iter);
            }
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

template<class Cont, class Predicate = less>
inline Unqualified<Cont> sort(Cont cont, Predicate&& pred = Predicate()) {
    std::sort(std::begin(cont), std::end(cont), pred);
    return cont;
}

template<class Cont, class Predicate = equal_to>
inline Unqualified<Cont> remove(Cont cont, ValueType<Cont> t, Predicate&& pred = Predicate()) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    for(; first != last; ++first) {
        if(pred(t, *first)) {
            cont.erase(first);
            break;
        }
    }
    return cont;
}
} // lia

#endif // LIA_TRANSFORMS_LIST_COMP_HPP