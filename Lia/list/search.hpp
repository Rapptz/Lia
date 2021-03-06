#ifndef LIA_SEARCH_LIST_COMP_HPP
#define LIA_SEARCH_LIST_COMP_HPP

#include "../detail/type_traits.hpp"
#include "../functional/adaptors/negator.hpp"
#include <algorithm>

namespace lia {
namespace search_detail {
struct has_remove_if_impl {
    template<typename T>
    static auto test(T* t) -> decltype(t->remove_if(0), Bool<true>()) {}
    template<typename>
    static auto test(...) -> Bool<false>;
};

template<typename T>
struct has_remove_if : decltype(has_remove_if_impl::test<T>(0)) {};
} // search_detail
const size_t npos = -1;

template<class Cont>
inline bool elem(Cont&& cont, ValueType<Cont> t) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    for(; first != last; ++first) {
        if(*first == t)
            return true;
    }
    return false;
}

template<class Cont>
inline bool not_elem(Cont&& cont, ValueType<Cont> t) {
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

template<class Cont, class Predicate, DisableIf<search_detail::has_remove_if<Unqualified<Cont>>>...>
inline Unqualified<Cont> filter(Cont cont, Predicate&& pred) {
    cont.erase(std::remove_if(std::begin(cont), std::end(cont), negator<Predicate>(pred)), std::end(cont));
    return cont;
}

template<class Cont, class Predicate, EnableIf<search_detail::has_remove_if<Unqualified<Cont>>>...>
inline Unqualified<Cont> filter(Cont cont, Predicate&& pred) {
    cont.remove_if(negator<Predicate>(pred));
    return cont;
}

template<class Cont, class Predicate>
inline auto partition(Cont&& cont, Predicate&& pred) -> decltype(std::make_pair(filter(cont, pred), filter(cont, negator<Predicate>(pred)))) {
    return std::make_pair(filter(cont, pred), filter(cont, negator<Predicate>(pred)));
}

template<class Cont>
inline size_t elem_index(Cont&& cont, ValueType<Cont> t) {
    size_t index = 0;
    for(auto&& i : cont) {
        if(i == t)
            return index;
        ++index;
    }
    return npos;
}

template<class Cont>
inline Rebind<Unqualified<Cont>, size_t> elem_indices(Cont&& cont, ValueType<Cont> t) {
    Rebind<Unqualified<Cont>, size_t> result;
    size_t index = 0;
    for(auto&& i : cont) {
        if(i == t)
            result.push_back(index);
        ++index;
    }
    return result;
}

template<class Cont, class Predicate>
inline size_t find_index(Cont&& cont, Predicate&& pred) {
    size_t index = 0;
    for(auto&& i : cont) {
        if(pred(i))
            return index;
        ++index;
    }
    return npos;
}

template<class Cont, class Predicate>
inline Rebind<Unqualified<Cont>, size_t> find_indices(Cont&& cont, Predicate&& pred) {
    Rebind<Unqualified<Cont>, size_t> result;
    size_t index = 0;
    for(auto&& i : cont) {
        if(pred(i))
            result.push_back(index);
        index++;
    }
    return result;
}
} // lia

#endif // LIA_SEARCH_LIST_COMP_HPP