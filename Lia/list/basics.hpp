#ifndef LIA_BASICS_LIST_COMP_HPP
#define LIA_BASICS_LIST_COMP_HPP

#include "../detail/type_traits.hpp"
#include "../detail/iterator.hpp"

namespace lia {
namespace detail {
struct has_pop_front_impl {
    template<typename T>
    static auto test(T* t) -> decltype(t->pop_front(), Bool<true>()) {}
    template<typename>
    static auto test(...) -> Bool<false>;
};

template<typename T>
struct has_pop_front : decltype(has_pop_front_impl::test<T>(0)) {};
} // detail
template<class Cont1, class Cont2 = Cont1, DisableIf<is_std_string<Unqualified<Cont1>>,
                                                     is_std_string<Unqualified<Cont2>>>...>
inline Unqualified<Cont1> append(Cont1&& cont1, Cont2&& cont2) {
    Unqualified<Cont1> result(std::forward<Cont1>(cont1));
    result.insert(std::end(result),
                  std::begin(cont2),
                  std::end(cont2));
    return result;
}

template<class Str, class Str2 = Str, EnableIf<is_std_string<Unqualified<Str>>,
                                               is_std_string<Unqualified<Str2>>>...>
inline Unqualified<Str> append(Str&& str, Str2&& str2) {
    Unqualified<Str> result(std::forward<Str>(str));
    result.append(std::forward<Str2>(str2));
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

template<class Cont, DisableIf<detail::has_pop_front<Unqualified<Cont>>>...>
inline Unqualified<Cont> tail(Cont result) {
    result.erase(std::begin(result)); // Not all containers have pop_front
    return result;
}

template<class Cont, EnableIf<detail::has_pop_front<Unqualified<Cont>>>...>
inline Unqualified<Cont> tail(Cont result) {
    result.pop_front();
    return result;
}

template<class Cont>
inline Unqualified<Cont> init(Cont result) {
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