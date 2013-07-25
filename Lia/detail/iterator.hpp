#ifndef LIA_DETAIL_ITERATOR_HPP
#define LIA_DETAIL_ITERATOR_HPP

// Includes
#include <iterator>

namespace lia {
template<typename Container>
auto rbegin(Container& cont) -> decltype(cont.rbegin()) {
    return cont.rbegin();
}

template<typename Container>
auto rbegin(const Container& cont) -> decltype(cont.crbegin()) {
    return cont.rbegin();
}

template<typename T, size_t N>
std::reverse_iterator<T*> rbegin(T (&array)[N]) {
    return std::reverse_iterator<T*>(array + N); 
}

template<typename T, size_t N>
std::reverse_iterator<const T*> rbegin(const T (&array)[N]) {
    return std::reverse_iterator<const T*>(array + N); 
}

template<typename Container>
auto rend(Container& cont) -> decltype(cont.rend()) {
    return cont.rend();
}

template<typename Container>
auto rend(const Container& cont) -> decltype(cont.crend()) {
    return cont.rend();
}

template<typename T, size_t N>
std::reverse_iterator<T*> rend(T (&array)[N]) {
    return std::reverse_iterator<T*>(array);
}

template<typename T, size_t N>
std::reverse_iterator<const T*> rend(const T (&array)[N]) {
    return std::reverse_iterator<const T*>(array);
}
} // lia

#endif //LIA_DETAIL_ITERATOR_HPP