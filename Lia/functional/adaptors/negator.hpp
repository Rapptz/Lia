#ifndef LIA_NEGATOR_ADAPTOR_HPP
#define LIA_NEGATOR_ADAPTOR_HPP

#include <utility>

namespace lia {
template<typename T>
struct negator {
    T pred;
    negator(T t): pred(std::move(t)) {}
    template<typename... Args>
    auto operator()(Args&&... args) -> decltype(!pred(std::forward<Args>(args)...)) {
        return !pred(std::forward<Args>(args)...);
    }
};
} // lia

#endif // LIA_NEGATOR_ADAPTOR_HPP