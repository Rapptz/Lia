#ifndef LIA_SUBLIST_LIST_COMP_HPP
#define LIA_SUBLIST_LIST_COMP_HPP

// Includes
#include "../detail/type_traits.hpp"

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

template<class Cont>
inline Unqualified<Cont> take(Cont&& cont, size_t n) {
    if(cont.size() < n)
        return cont;
    auto first = std::begin(cont);
    Unqualified<Cont> result;
    for(size_t i = 0; i < n; ++i)
        result.push_back(*first++);
    return result;
}

template<class Cont>
inline Unqualified<Cont> drop(Cont&& cont, size_t n) {
    if(cont.size() < n)
        return {};
    auto first = std::begin(cont) + n;
    auto last = std::end(cont);
    Unqualified<Cont> result;
    for(; first != last; ++first)
        result.push_back(*first);
    return result;
}

template<class Cont>
inline auto split_at(Cont&& cont, size_t n) -> decltype(std::make_pair(take(cont, n), drop(cont, n))) {
    return std::make_pair(take(cont, n), drop(cont, n));
}

template<class Cont, class Predicate>
inline Unqualified<Cont> take_while(Cont&& cont, Predicate&& pred) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    Unqualified<Cont> result;
    for(; first != last; ++first) {
        if(pred(*first))
            result.push_back(*first);
        else
            break;
    }
    return result;
}

template<class Cont, class Predicate>
inline Unqualified<Cont> drop_while(Cont&& cont, Predicate&& pred) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    Unqualified<Cont> result;
    bool met = false;
    for(; first != last; ++first) {
        if(!(met || pred(*first))) {
            met = true;
        }
        if(met) {
            result.push_back(*first);
        }
    }
    return result;
}

template<class Cont, class Predicate>
inline auto span(Cont&& cont, Predicate&& pred) -> decltype(std::make_pair(take_while(cont, pred), drop_while(cont, pred))) {
    return std::make_pair(take_while(cont, pred), drop_while(cont, pred));
}

template<class Cont, class Predicate>
inline auto span_not(Cont&& cont, Predicate&& pred) -> decltype(span(cont, detail::negate<Predicate>(pred))) {
    return span(cont, detail::negate<Predicate>(pred));
}

} // lia

#endif // LIA_SUBLIST_LIST_COMP_HPP