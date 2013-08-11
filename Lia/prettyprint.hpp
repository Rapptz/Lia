#ifndef LIA_PRETTY_PRINT_HPP
#define LIA_PRETTY_PRINT_HPP

#include "../detail/type_traits.hpp"
#include "../detail/iterator.hpp"
#include "../detail/indices.hpp"
#include <iosfwd>

namespace lia {
namespace pretty_print_detail {
template<class Elem, class Traits, class Tuple, size_t... Indices>
void print_tuple(std::basic_ostream<Elem, Traits>& os, const Tuple& t, indices<Indices...>) {
    using expander = int[];
    using std::get;
    (void)expander{0, (void(os << (!Indices ? "" : ", ") << get<Indices>(t)), 0)...};
}
} // pretty_print_detail
namespace operators {
template<class Elem, class Traits, typename... Args>
inline std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& os, const std::tuple<Args...>& tuple) {
    os << "(";
    pretty_print_detail::print_tuple(os, tuple, build_indices<sizeof...(Args)>());
    os << ")";
    return os;
}

template<class Elem, class Traits, typename T, typename U>
inline std::basic_ostream<Elem,Traits>& operator<<(std::basic_ostream<Elem,Traits>& os, const std::pair<T,U>& p) {
    os << '(' << p.first << ", " << p.second << ')';
    return os;
}

template<class Elem, class Traits, class Cont, EnableIf<has_begin_end<Unqualified<Cont>>>...>
inline std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& os, const Cont& cont) {
    auto first = std::begin(cont);
    auto last = std::end(cont);
    if(first == last) {
        os << "[]";
        return os;
    }
    else {
        os << '[' << *first++;
    }
    while(first != last) {
        os << ", " << *first++;
    }
    os << ']';
    return os;
}
} // operators
} // lia


#endif // LIA_PRETTY_PRINT_HPP