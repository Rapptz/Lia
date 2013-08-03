#ifndef LIA_DETAIL_INDICES_HPP
#define LIA_DETAIL_INDICES_HPP

#include "type_traits.hpp"
#include <tuple>

namespace lia {
template<size_t... Ns>
struct indices {};

template<size_t N, size_t... Ns>
struct build_indices : build_indices<N-1, N-1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<typename Tuple>
using IndicesFor = build_indices<std::tuple_size<Unqualified<Tuple>>::value>;
} // lia

#endif // LIA_DETAIL_INDICES_HPP
