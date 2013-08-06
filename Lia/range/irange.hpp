#ifndef LIA_RANGE_NUMERIC_RANGE_HPP
#define LIA_RANGE_NUMERIC_RANGE_HPP

#include "../detail/iterator.hpp"
#include "../detail/type_traits.hpp"

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

    auto front() const -> decltype(*first) {
        return *first;
    }

    auto back() const -> decltype(*last) {
        static_assert(!Infinite, "Cannot receive the last element of an infinite range");
        return *--end();
    }

    size_t size() const {
        static_assert(!Infinite, "Infinite ranges do not have length");
        return std::distance(first, last);
    }
};

template<typename T>
constexpr numeric_range<T, true> irange(T begin) {
    return {begin};
}

template<typename T, typename R = numeric_range<T>>
constexpr R irange(T begin, T end) {
    return end >= begin ? R{begin, ++end} : R{begin, --end, -1};
}
} // lia

#endif // LIA_RANGE_NUMERIC_RANGE_HPP