#ifndef LIA_FOLDS_LIST_COMP_HPP
#define LIA_FOLDS_LIST_COMP_HPP

#include "transforms.hpp"

namespace lia {
template<class Cont, typename T, class BinaryFunc>
inline T foldl(Cont&& cont, BinaryFunc&& func, T starting) {
    return std::accumulate(std::begin(std::forward<Cont>(cont)),
                           std::end(std::forward<Cont>(cont)),
                           starting,
                           func);
}

template<class Cont, typename T, class BinaryFunc>
inline T foldr(Cont&& cont, BinaryFunc&& func, T starting) {
    auto first = rbegin(std::forward<Cont>(cont));
    auto last = rend(std::forward<Cont>(cont));
    for(; first != last; ++first)
        starting = func(*first, starting);
    return starting;
}

template<class Cont, class BinaryFunc>
inline auto foldl1(Cont&& cont, BinaryFunc&& func) -> decltype(func(cont.back(), cont.back())) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    decltype(func(cont.back(), cont.back())) init = *first++;
    for(; first != last; ++first)
        init = func(init, *first);
    return init;
}

template<class Cont, class BinaryFunc>
inline auto foldr1(Cont&& cont, BinaryFunc&& func) -> decltype(func(cont.back(), cont.back())) {
    auto first = rbegin(cont);
    auto last = rend(cont);
    decltype(func(cont.back(), cont.back())) init = *first++;
    for(; first != last; ++first)
        init = func(*first, init);
    return init;
}

// Special folds
template<class Cont>
inline ValueType<Cont> sum(Cont&& cont) {
    using T = ValueType<Cont>;
    return foldl1(std::forward<Cont>(cont), [](T x, T y) { return x + y; });
}

template<class Cont>
inline ValueType<Cont> product(Cont&& cont) {
    using T = ValueType<Cont>;
    return foldl1(std::forward<Cont>(cont), [](T x, T y) { return x * y; });
}

template<class Cont, class Predicate = less>
inline ValueType<Cont> minimum(Cont&& cont, Predicate&& pred = Predicate()) {
    return *(std::min_element(std::begin(std::forward<Cont>(cont)),
                              std::end(std::forward<Cont>(cont)),
                              std::forward<Predicate>(pred)));
}

template<class Cont, class Predicate = less>
inline ValueType<Cont> maximum(Cont&& cont, Predicate&& pred = Predicate()) {
    return *(std::max_element(std::begin(std::forward<Cont>(cont)),
                              std::end(std::forward<Cont>(cont)),
                              std::forward<Predicate>(pred)));
}

template<class Cont, EnableIf<std::is_same<ValueType<Cont>, bool>>...>
inline bool all(Cont&& cont) {
    for(auto&& boolean : cont) {
        if(!boolean)
            return false;
    }
    return true;
}

template<class Cont, class Predicate>
inline bool all(Cont&& cont, Predicate&& pred) {
    return std::all_of(std::begin(std::forward<Cont>(cont)),
                       std::end(std::forward<Cont>(cont)),
                       std::forward<Predicate>(pred));
}

template<class Cont, EnableIf<std::is_same<ValueType<Cont>, bool>>...>
inline bool any(Cont&& cont) {
    for(auto&& boolean : cont) {
        if(boolean)
            return true;
    }
    return false;
}

template<class Cont, class Predicate>
inline bool any(Cont&& cont, Predicate&& pred) {
    return std::any_of(std::begin(std::forward<Cont>(cont)),
                       std::end(std::forward<Cont>(cont)),
                       std::forward<Predicate>(pred));
}

template<class Cont, DisableIf<is_std_string<ValueType<Cont>>>...>
inline auto concat(Cont&& cont) -> Rebind<Unqualified<Cont>, NestedValueType<Cont>> {
    Rebind<Unqualified<Cont>, NestedValueType<Cont>> result;
    for(auto&& internal : cont) {
        result.insert(std::end(result), std::begin(internal), std::end(internal));
    }
    return result;
}

template<class Cont, EnableIf<is_std_string<ValueType<Cont>>>...>
inline auto concat(Cont&& cont) -> ValueType<Cont> {
    ValueType<Cont> result;
    for(auto&& str : cont)
        result += str;
    return result;
}

template<class Cont, class T = ValueType<Cont>>
T intercalate(Cont&& cont, T&& sublist) {
    return concat(intersperse(std::forward<Cont>(cont), std::forward<T>(sublist)));
}

template<class Cont, class Callable, EnableIf<is_nested_container<Unqualified<Cont>>>...>
inline auto concat_map(Cont&& cont, Callable&& callable) -> decltype(concat(map(std::forward<Cont>(cont), std::forward<Callable>(callable)))) {
    return concat(map(std::forward<Cont>(cont), std::forward<Callable>(callable)));
}

template<class Cont, class BinaryFunc, typename T>
inline auto scanl(Cont&& cont, BinaryFunc&& f, T acc) -> Rebind<Unqualified<Cont>, decltype(f(acc, cont.back()))> {
    Rebind<Unqualified<Cont>, decltype(f(acc, cont.back()))> result;
    auto first = std::begin(cont);
    auto last = std::end(cont);
    result.push_back(acc);
    for( ; first != last; ++first) {
        acc = f(acc, *first);
        result.push_back(acc);
    }
    return result;
}

template<class Cont, class BinaryFunc>
inline auto scanl1(Cont&& cont, BinaryFunc&& f) -> Rebind<Unqualified<Cont>, decltype(f(cont.back(), cont.back()))> {
    Rebind<Unqualified<Cont>, decltype(f(cont.back(), cont.back()))> result;
    auto first = std::begin(cont);
    auto last = std::end(cont);
    decltype(f(cont.back(), cont.back())) acc = *first++;
    result.push_back(acc);
    for( ; first != last; ++first) {
        acc = f(acc, *first);
        result.push_back(acc);
    }
    return result;
}
} // lia

#endif // LIA_FOLDS_LIST_COMP_HPP