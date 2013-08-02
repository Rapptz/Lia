#ifndef LIA_SEARCH_LIST_COMP_HPP
#define LIA_SEARCH_LIST_COMP_HPP

#include "../detail/type_traits.hpp"
#include <algorithm>

namespace lia {
namespace detail {
template<typename T>
struct negate {
    T pred;
    negate(T t): pred(std::move(t)) {}
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(!pred(std::forward<Args>(args)...)) {
        return !pred(std::forward<Args>(args)...);
    }
};
} // detail

const size_t npos = -1;

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

template<class Cont, class Predicate>
inline auto find(Cont&& cont, Predicate&& pred) -> decltype(std::begin(cont)) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    for(; first != last; ++first) {
        if(pred(*first))
            return first;
    }
    return last;
}

template<class Cont, class Predicate>
inline Unqualified<Cont> filter(Cont cont, Predicate&& pred) {
    cont.erase(std::remove_if(std::begin(cont), std::end(cont), detail::negate<Predicate>(pred)),std::end(cont));
    return cont;
}

template<class Cont, class Predicate>
inline auto partition(Cont&& cont, Predicate&& pred) -> decltype(std::make_pair(filter(cont, pred), filter(cont, detail::negate<Predicate>(pred)))) {
    return std::make_pair(filter(cont, pred), filter(cont, detail::negate<Predicate>(pred)));
}

template<class Cont>
inline size_t elem_index(Cont&& cont, ValueType<Unqualified<Cont>> t) {
    size_t index = 0;
    for(auto&& i : cont) {
        if(i == t)
            return index;
        ++index;
    }
    return npos;
}

template<class Cont>
inline Rebind<Unqualified<Cont>, size_t> elem_indices(Cont&& cont, ValueType<Unqualified<Cont>> t) {
    Rebind<Unqualified<Cont>, size_t> result;
    size_t index = 0;
    for(auto&& i : cont) {
        if(i == t)
            result.push_back(index);
        ++index;
    }
    return result;
}
} // lia

#endif // LIA_SEARCH_LIST_COMP_HPP