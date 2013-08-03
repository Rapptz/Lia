#ifndef LIA_FUNCTIONAL_CURRY_HPP
#define LIA_FUNCTIONAL_CURRY_HPP

#include "../detail/indices.hpp"

namespace lia {
namespace detail {
template<typename F, typename Tuple, size_t... Indices>
constexpr ResultOf<F(Type<std::tuple_element<Indices, Tuple>>...)> invoke_impl(F&& f, Tuple&& t, indices<Indices...>) {
    using std::get;
    return std::forward<F>(f)(get<Indices>(std::forward<Tuple>(t))...);
}
template<typename F, typename Tuple>
constexpr auto invoke(F&& f, Tuple&& tuple) -> decltype(invoke_impl(std::declval<F>(), std::declval<Tuple>(), IndicesFor<Tuple>{})) {
    return invoke_impl(std::forward<F>(f), std::forward<Tuple>(tuple), IndicesFor<Tuple>{});
}
} // detail

template<typename Function, typename... Args>
struct curry_type {
    using tuple_type = std::tuple<Args...>;
private:
    Function func;
    tuple_type args;
public:
    curry_type(Function&& f, tuple_type n): func(std::forward<Function>(f)), args(std::move(n)) {}

    template<typename... T>
    auto operator()(T&&... t) -> decltype(detail::invoke(func, std::tuple_cat(std::move(args), std::forward_as_tuple(t...)))) {
        return detail::invoke(func, std::tuple_cat(std::move(args), std::forward_as_tuple(t...)));
    }
};

template<typename Function, typename... Args>
constexpr curry_type<Function, Args...> curry(Function&& f, Args&&... args) {
    return { std::forward<Function>(f), std::forward_as_tuple(args...) };
}
} // lia

#endif // LIA_FUNCTIONAL_CURRY_HPP