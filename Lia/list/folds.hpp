#ifndef LIA_FOLDS_LIST_COMP_HPP
#define LIA_FOLDS_LIST_COMP_HPP

// Includes
#include "transforms.hpp"

namespace lia {
namespace detail {
struct less {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) < std::forward<U>(u)) {
        return std::forward<T>(t) < std::forward<U>(u);
    }
};
struct greater {
    template<typename T, typename U>
    auto operator()(T&& t, U&& u) -> decltype(std::forward<T>(t) > std::forward<U>(u)) {
        return std::forward<T>(t) > std::forward<U>(u);
    }
};
} // detail

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
        starting = func(*first,starting);
    return starting;
}

template<class Cont, class BinaryFunc>
inline auto foldl1(Cont&& cont, BinaryFunc&& func) -> ResultOf<Unqualified<BinaryFunc>> {
    auto first = std::begin(std::forward<Cont>(cont));
    auto last = std::end(std::forward<Cont>(cont));
    ResultOf<Unqualified<BinaryFunc>> init = *first++;
    for(; first != last; ++first)
        init = func(init, *first);
    return init;
}

template<class Cont, class BinaryFunc>
inline auto foldr1(Cont&& cont, BinaryFunc&& func) -> ResultOf<Unqualified<BinaryFunc>> {
    auto first = rbegin(std::forward<Cont>(cont));
    auto last = rend(std::forward<Cont>(cont));
    ResultOf<Unqualified<BinaryFunc>> init = *first++;
    for(; first != last; ++first)
        init = func(*first, init);
    return init;
}

// Special folds
template<class Cont>
inline ValueType<Unqualified<Cont>> sum(Cont&& cont) {
    using T = ValueType<Unqualified<Cont>>;
    return foldl1(std::forward<Cont>(cont),[](T x, T y) { return x + y; });
}

template<class Cont>
inline ValueType<Unqualified<Cont>> product(Cont&& cont) {
    using T = ValueType<Unqualified<Cont>>;
    return foldl1(std::forward<Cont>(cont),[](T x, T y) { return x * y; });
}

template<class Cont, class Predicate = detail::less>
inline ValueType<Unqualified<Cont>> minimum(Cont&& cont, Predicate&& pred = Predicate()) {
    return *(std::min_element(std::begin(std::forward<Cont>(cont)),
                              std::end(std::forward<Cont>(cont)),
                              std::forward<Predicate>(pred)));
}

template<class Cont, class Predicate = detail::less>
inline ValueType<Unqualified<Cont>> maximum(Cont&& cont, Predicate&& pred = Predicate()) {
    return *(std::max_element(std::begin(std::forward<Cont>(cont)),
                              std::end(std::forward<Cont>(cont)),
                              std::forward<Predicate>(pred)));
}

template<class Cont, EnableIf<std::is_same<ValueType<Unqualified<Cont>>, bool>>...>
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

template<class Cont, EnableIf<std::is_same<ValueType<Unqualified<Cont>>, bool>>...>
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

template<class Cont, EnableIf<is_nested_container<Unqualified<Cont>>>...>
inline auto concat(Cont&& cont) -> Rebind<Unqualified<Cont>, NestedValueType<Cont>> {
    Rebind<Unqualified<Cont>, NestedValueType<Cont>> result;
    for(auto&& internal : cont) {
        result.insert(std::end(result), std::begin(internal), std::end(internal));
    }
    return result;
}

template<class Cont, EnableIf<is_std_string<ValueType<Unqualified<Cont>>>>...>
inline auto concat(Cont&& cont) -> ValueType<Unqualified<Cont>> {
    ValueType<Unqualified<Cont>> result;
    for(auto&& str : cont)
        result += str;
    return result;
}

template<class Cont, class Callable, EnableIf<is_nested_container<Unqualified<Cont>>>...>
inline auto concatMap(Cont&& cont, Callable&& callable) -> decltype(concat(map(std::forward<Cont>(cont), std::forward<Callable>(callable)))) {
    return concat(map(std::forward<Cont>(cont), std::forward<Callable>(callable)));
}
} // lia

#endif //LIA_FOLDS_LIST_COMP_HPP