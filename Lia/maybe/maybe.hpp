#ifndef LIA_MAYBE_HPP
#define LIA_MAYBE_HPP

#include "maybe_traits.hpp"
#include "../detail/type_traits.hpp"
#include <memory>
#include <stdexcept>

namespace lia {
namespace maybe_detail {
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class invalid_state : public std::runtime_error {
    invalid_state(const char* str): std::runtime_error(str) {}
};
} // maybe_detail

template<typename T>
struct maybe {
private:
    std::unique_ptr<T> value;
    static constexpr bool has_nothing = std::is_same<T, detail::nothing_t>();
public:
    using value_type = T;
    constexpr maybe() noexcept {}
    explicit maybe(T&& value) noexcept: value(new T(std::forward<T>(value))) {}

    bool state() const {
        return !has_nothing && (value != nullptr);
    }

    explicit operator bool() {
        return state();
    }

    template<typename U>
    bool operator==(const maybe<U>& rhs) const {
        return maybe_traits<T, U>::eq(value.get(), state(), rhs.data(), rhs.state());
    }

    template<typename U>
    bool operator!=(const maybe<U>& rhs) const {
        return !(*this == rhs);
    }

    template<typename U>
    bool operator<(const maybe<U>& rhs) const {
        return maybe_traits<T, U>::lt(value.get(), state(), rhs.data(), rhs.state());
    }

    template<typename U>
    bool operator<=(const maybe<U>& rhs) const {
        return !(rhs < *this);
    }

    template<typename U>
    bool operator>=(const maybe<U>& rhs) const {
        return !(*this < rhs);
    }

    template<typename U>
    bool operator>(const maybe<U>& rhs) const {
        return rhs < *this;
    }

    T* data() const {
        return value.get();
    }

    template<typename... Args>
    void emplace(Args&&... args) {
        value = maybe_detail::make_unique<T>(args...);
    }

    T& operator*() {
        if(!value)
            throw maybe_detail::invalid_state("Accessing an invalid state maybe object");
        return *value;
    }

    const T& operator*() const {
        if(!value)
            throw maybe_detail::invalid_state("Accessing an invalid state maybe object");
        return *value;
    }
};

template<typename T>
inline maybe<Decay<T>> just(T&& value) {
    return maybe<Decay<T>>{std::forward<T>(value)};
}

inline maybe<detail::nothing_t> nothing() {
    return {};
}
} // lia

#endif // LIA_MAYBE_HPP