#ifndef LIA_MAYBE_TRAITS_HPP
#define LIA_MAYBE_TRAITS_HPP

namespace lia {
struct nothing_t {};

template<typename T, typename U>
struct maybe_traits {
    static bool eq(const T* lhs, bool lhs_state, const U* rhs, bool rhs_state) {
        return (!lhs_state && !rhs_state) || (lhs_state && rhs_state && (*lhs == *rhs));
    }
    static bool lt(const T* lhs, bool lhs_state, const U* rhs, bool rhs_state) {
        return rhs_state && (!lhs_state || *lhs < *rhs);
    }
};

template<typename T>
struct maybe_traits<T, nothing_t> {
    static bool eq(const T* lhs, bool lhs_state, const nothing_t* rhs, bool rhs_state) {
        return !lhs_state;
    }
    static bool lt(const T* lhs, bool lhs_state, const nothing_t* rhs, bool rhs_state) {
        return false;
    }
};

template<typename U>
struct maybe_traits<nothing_t, U> {
    static bool eq(const nothing_t* lhs, bool lhs_state, const U* rhs, bool rhs_state) {
        return !rhs_state;
    }
    static bool lt(const nothing_t* lhs, bool lhs_state, const U* rhs, bool rhs_state) {
        return rhs_state;
    }
};

template<>
struct maybe_traits<nothing_t, nothing_t> {
    static bool eq(const nothing_t* lhs, bool lhs_state, const nothing_t* rhs, bool rhs_state) {
        return true;
    }
    static bool lt(const nothing_t* lhs, bool lhs_state, const nothing_t* rhs, bool rhs_state) {
        return false;
    }
};
} // lia

#endif // LIA_MAYBE_TRAITS_HPP