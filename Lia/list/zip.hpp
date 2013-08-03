#ifndef LIA_ZIP_LIST_COMP_HPP
#define LIA_ZIP_LIST_COMP_HPP

#include "../detail/type_traits.hpp"
#include <tuple>
#include <vector>

namespace lia {
namespace detail {
template<class Cont>
inline const ValueType<Cont>& forward_index(const Cont& cont, unsigned i) {
    return cont[i];
}
 
template<class Cont>
inline ValueType<Cont>&& forward_index(Cont&& cont, unsigned i) {
    return std::move(cont[i]);
}
} // detail

template<typename... Args>
inline std::vector<std::tuple<ValueType<Args>...>> zip(Args&&... args) {
    auto size = min(args.size()...);
    std::vector<std::tuple<ValueType<Args>...>> result;
    result.reserve(size);
    for(unsigned i = 0; i < size; ++i) {
        result.emplace_back(detail::forward_index(std::forward<Args>(args), i)...);
    }
    return result;
}

template<class Cont, class Function, typename... Args>
inline auto zip_with(Function&& f, Cont cont, Args&&... args) -> Rebind<Cont, decltype(f(cont.back(), args.back()...))> {
    Rebind<Cont, decltype(f(cont.back(), args.back()...))> result;
    auto size = min(cont.size(), args.size()...);
    for(unsigned i = 0; i < size; ++i) {
        result.emplace_back(f(detail::forward_index(cont, i), 
                              detail::forward_index(std::forward<Args>(args), i)...));
    }
    return result;
}
} // lia

#endif // LIA_ZIP_LIST_COMP_HPP