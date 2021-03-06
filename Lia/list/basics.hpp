#ifndef LIA_BASICS_LIST_COMP_HPP
#define LIA_BASICS_LIST_COMP_HPP

#include "../detail/type_traits.hpp"
#include "../detail/iterator.hpp"

namespace lia {
namespace basics_detail {
struct has_pop_front_impl {
    template<typename T>
    static auto test(T* t) -> decltype(t->pop_front(), Bool<true>()) {}
    template<typename>
    static auto test(...) -> Bool<false>;
};

template<typename T>
struct has_pop_front : decltype(has_pop_front_impl::test<T>(0)) {};
} // basics_detail

template<class Cont1, class Cont2 = Cont1, DisableIf<has_append<Unqualified<Cont1>>,
                                                     has_append<Unqualified<Cont2>>>...>
inline Unqualified<Cont1> append(Cont1 first, Cont2&& other) {
    first.insert(std::end(first),
                  std::begin(other),
                  std::end(other));
    return first;
}

template<class Str, class Str2 = Str, EnableIf<has_append<Unqualified<Str>>,
                                               has_append<Unqualified<Str2>>>...>
inline Unqualified<Str> append(Str first, Str2&& other) {
    first.append(std::forward<Str2>(other));
    return first;
}

template<class Cont>
inline auto head(Cont&& cont) -> decltype(cont.front()) {
    return cont.front();
}

template<class Cont>
inline auto last(Cont&& cont) -> decltype(cont.back()) {
    return cont.back();
}

template<class Cont, DisableIf<basics_detail::has_pop_front<Unqualified<Cont>>>...>
inline Unqualified<Cont> tail(Cont result) {
    result.erase(std::begin(result)); // Not all containers have pop_front
    return result;
}

template<class Cont, EnableIf<basics_detail::has_pop_front<Unqualified<Cont>>>...>
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