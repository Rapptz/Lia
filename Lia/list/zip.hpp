#ifndef LIA_ZIP_LIST_COMP_HPP
#define LIA_ZIP_LIST_COMP_HPP

#include "../detail/type_traits.hpp"
#include <tuple>

namespace lia {
namespace zip_detail {
template<size_t N, typename... Args>
using Arg = Type<std::tuple_element<N, std::tuple<Args...>>>;

template<class Cont>
inline const ValueType<Cont>& forward_index(const Cont& cont, unsigned i) {
    return cont[i];
}
 
template<class Cont>
inline ValueType<Cont>&& forward_index(Cont&& cont, unsigned i) {
    return std::move(cont[i]);
}
} // zip_detail

template<typename... Args>
inline Rebind<zip_detail::Arg<0, Unqualified<Args>...>, std::tuple<ValueType<Args>...>> zip(Args&&... args) {
    auto size = min(args.size()...);
    Rebind<zip_detail::Arg<0, Unqualified<Args>...>, std::tuple<ValueType<Args>...>> result;
    for(unsigned i = 0; i < size; ++i) {
        result.emplace_back(zip_detail::forward_index(std::forward<Args>(args), i)...);
    }
    return result;
}

template<class Function, typename... Args>
inline auto zip_with(Function&& f, Args&&... args) -> Rebind<zip_detail::Arg<0, Unqualified<Args>...>, decltype(f(args.back()...))> {
    auto size = min(args.size()...);
    Rebind<zip_detail::Arg<0, Unqualified<Args>...>, decltype(f(args.back()...))> result;
    for(unsigned i = 0; i < size; ++i) {
        result.emplace_back(f(zip_detail::forward_index(std::forward<Args>(args), i)...));
    }
    return result;
}
} // lia

#endif // LIA_ZIP_LIST_COMP_HPP