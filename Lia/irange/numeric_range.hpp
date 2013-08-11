#ifndef LIA_IRANGE_NUMERIC_RANGE_HPP
#define LIA_IRANGE_NUMERIC_RANGE_HPP

#include <type_traits>
#include "numeric_range_iterator.hpp"

namespace lia {
template<typename T, bool Infinite = false>
struct numeric_range {
public:
    using value_type = T;
    using iterator = numeric_range_iterator<T, Infinite>;
    using const_iterator = const iterator;
private:
    iterator first;
    iterator last;
public:
    static_assert(std::is_integral<T>(), "numeric_range must be integral types only");
    numeric_range() {}
    numeric_range(T begin): first(begin) {}
    numeric_range(T begin, T end): first(begin), last(end) {
        static_assert(!Infinite, "Cannot define an end to an infinite range");
    }

    numeric_range(T begin, T end, std::ptrdiff_t step): first(begin, step), last(end, step) {
        static_assert(!Infinite, "Cannot define an end to an infinite range");
    }

    auto step(std::ptrdiff_t t) -> decltype(*this) {
        first.step = t;
        last.step = t;
        return *this;
    }

    iterator begin() const {
        return first;
    }

    iterator end() const {
        return last;
    }

    bool empty() const {
        return first == last;
    }

    static constexpr bool is_infinite() {
        return Infinite;
    }

    void pop_back() {
        static_assert(!Infinite, "Cannot pop_back an infinite range");
        if(empty())
            return;
        --last;
    }

    void pop_front() {
        if(empty())
            return;
        ++first;
    }

    T& front() {
        return *first;
    }

    const T& front() const {
        return *first;
    }

    T& back() {
        static_assert(!Infinite, "Cannot receive the last element of an infinite range");
        return *--end();
    }

    const T& back() const {
        static_assert(!Infinite, "Cannot receive the last element of an infinite range");
        return *--end();
    }

    size_t size() const {
        static_assert(!Infinite, "Infinite ranges do not have length");
        return std::distance(first, last);
    }
};
} // lia

#endif // LIA_IRANGE_NUMERIC_RANGE_HPP