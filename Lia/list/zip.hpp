#ifndef LIA_ZIP_LIST_COMP_HPP
#define LIA_ZIP_LIST_COMP_HPP

#include "../detail/type_traits.hpp"
#include <tuple>
#include <vector>

namespace lia {
namespace detail {
template<template<typename...> class Cont, typename T>
const T& forward_index(const Cont<T>& cont, unsigned i) {
    return cont[i];
}
 
template<template<typename...> class Cont, typename T>
T&& forward_index(Cont<T>&& cont, unsigned i) {
    return std::move(cont[i]);
}
} // detail

template<typename... Args>
std::vector<std::tuple<BareValueType<Args>...>> zip(Args&&... args) {
    auto size = min(args.size()...);
    std::vector<std::tuple<BareValueType<Args>...>> result;
    result.reserve(size);
    for(unsigned i = 0; i < size; ++i) {
        result.emplace_back(detail::forward_index(std::forward<Args>(args), i)...);
    }
    return result;
}
} // lia

#endif // LIA_ZIP_LIST_COMP_HPP