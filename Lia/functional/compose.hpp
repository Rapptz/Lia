#ifndef LIA_FUNCTIONAL_COMPOSE_HPP
#define LIA_FUNCTIONAL_COMPOSE_HPP

#include "../detail/type_traits.hpp"

namespace lia {
template<typename First, typename Second>
struct compose_type {
    First f;
    Second g;
    compose_type(First f, Second g): f(std::move(f)), g(std::move(g)) {}

    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(f(g(std::forward<Args>(args)...))) {
        return f(g(std::forward<Args>(args)...));
    }
};

template<typename F, typename... G>
struct composer {
    using type = compose_type<Decay<F>, Type<composer<G...>>>;
};

template<typename F>
struct composer<F> {
    using type = Decay<F>;
};

template<typename... Args>
using Composer = Type<composer<Args...>>;

template<typename Function>
auto compose(Function&& f) -> Decay<Function> {
    return std::forward<Function>(f);
}

template<typename First, typename... Rest>
auto compose(First&& f, Rest&&... args) -> Composer<First, Rest...> {
    return Composer<First, Rest...>(std::forward<First>(f), compose(std::forward<Rest>(args)...));
}
} // lia

#endif // LIA_FUNCTIONAL_COMPOSE_HPP