#ifndef LIA_IRANGE_NUMERIC_RANGE_ITERATOR_HPP
#define LIA_IRANGE_NUMERIC_RANGE_ITERATOR_HPP

#include "../detail/iterator.hpp"

namespace lia {
template<typename T, bool Infinite = false>
struct numeric_range_iterator : std::iterator<std::bidirectional_iterator_tag, T> {
private:
    T current;
    std::ptrdiff_t step;
public:
    template<typename U, bool B>
    friend struct numeric_range;
    
    numeric_range_iterator(): current(0), step(1) {}
    numeric_range_iterator(T t, std::ptrdiff_t s = 1): current(t), step(s) {}

    T operator*() const { 
        return current;
    }

    const T* operator->() const {
        return &current;
    }

    auto operator++() -> decltype(*this) {
        current += step;
        return *this;
    }

    numeric_range_iterator operator++(int) {
        auto copy = *this;
        ++(*this);
        return copy;
    }

    auto operator--() -> decltype(*this) {
        current -= step;
        return *this;
    }

    numeric_range_iterator operator--(int) {
        auto copy = *this;
        --(*this);
        return copy;
    }

    bool operator!=(const numeric_range_iterator& other) const {
        return Infinite ? true : other.current != current;
    }

    bool operator==(const numeric_range_iterator& other) const {
        return Infinite ? false : other.current == current;
    }
};
} // lia

#endif // LIA_IRANGE_NUMERIC_RANGE_ITERATOR_HPP