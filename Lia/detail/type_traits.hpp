#ifndef LIA_DETAIL_TYPE_TRAITS_HPP
#define LIA_DETAIL_TYPE_TRAITS_HPP

// Includes
#include <type_traits>
#include <utility>
#include <cstddef>
#include <array>

namespace lia {
template<typename T>
using Type = typename T::type;

template<typename... Args>
using CommonType = Type<std::common_type<Args...>>;

template<typename T>
using UnderlyingType = Type<std::underlying_type<T>>;

template<typename T, T t>
using Const = std::integral_constant<T,t>;

template<int i>
using Integer = Const<int,i>;

template<typename T>
struct identity {
    using type = T;
};

template<typename...>
struct void_ { 
    using type = void;
};

template<typename... T>
using Void = typename void_<T...>::type;

template<bool T, typename...>
struct boolean : Const<bool, T> {};

template<bool T, typename... Args>
using Bool = Type<boolean<T,Args...>>;

template<typename If, typename Then, typename Else>
using Conditional = Type<std::conditional<If::value, Then, Else>>;

template<typename T>
using Not = Bool<!T::value>;

template<typename... Args>
struct Any : Bool<true> {};

template<typename T, typename... Args>
struct Any<T, Args...> : Conditional<T, Bool<true>, Any<Args...>> {};

template<typename... Args>
struct All : Bool<true> {};

template<typename T, typename... Args>
struct All<T, Args...> : Conditional<T, All<Args...>, Bool<false>> {};

template<typename T>
struct is_allocator {
private:
    using yes = char;
    using no = struct { char stuff[2]; };
    template<class Cont>
    static yes test(typename Cont::template rebind<Cont>::other*);
    template<class Cont>
    static no test(...);
public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template<bool Cond, typename Specialization, typename Target>
struct rebind_allocator {};

template<typename Alloc, typename Target>
struct rebind_allocator<true, Alloc, Target> { 
    using type = typename Alloc::template rebind<Target>::other;
};

template<typename T, typename Target>
struct rebind_allocator<false, T, Target> {
    using type = T;
};

template<typename T, typename Target>
using RebindAllocator = Type<rebind_allocator<is_allocator<T>::value, T, Target>>;

template<typename Specialization, typename Target>
struct rebind {};

// Sensible default: assume first parameter is for the target
template<template<typename...> class Cont, typename T, typename... Ts, typename Target>
struct rebind<Cont<T, Ts...>, Target> {
    using type = Cont<Target, RebindAllocator<Ts, Target>...>;
};

template<typename Old, size_t N, typename Target>
struct rebind<std::array<Old, N>, Target> {
    using type = std::array<Target, N>;
};

template<typename Specialization, typename Target>
using Rebind = typename rebind<Specialization, Target>::type;

template<typename Signature, typename Anon = void>
struct result_of_impl {};

template<typename Function, typename... Args>
struct result_of_impl<Function(Args...), Void<decltype(std::declval<Function>()(std::declval<Args>()...))>> {
    using type = decltype(std::declval<Function>()(std::declval<Args>()...));
};

template<typename Signature>
using ResultOf = Type<result_of_impl<Signature>>;

template<typename... Args>
using EnableIf = Type<std::enable_if<All<Args...>::value>>;

template<typename... Args>
using DisableIf = Type<std::enable_if<Not<All<Args...>>::value>>;

template<typename T>
using Decay = Type<std::decay<T>>;

template<typename T>
using RemoveRef = Type<std::remove_reference<T>>;

template<typename T>
using RemoveCV = Type<std::remove_cv<T>>;

template<typename T>
using RemoveConst = Type<std::remove_const<T>>;

template<typename T>
using RemoveVolatile = Type<std::remove_volatile<T>>;

template<typename T>
using RemoveExtents = Type<std::remove_all_extents<T>>;

template<typename T>
using RemovePointer = Type<std::remove_pointer<T>>;

template<typename T>
using AddLValueRef = Type<std::add_lvalue_reference<T>>;

template<typename T>
using AddRValueRef = Type<std::add_rvalue_reference<T>>;

template<typename T>
using AddCV = Type<std::add_cv<T>>;

template<typename T>
using AddConst = Type<std::add_const<T>>;

template<typename T>
using AddVolatile = Type<std::add_volatile<T>>;

template<typename T>
using AddPointer = Type<std::add_pointer<T>>;

template<typename T>
using Signed = Type<std::make_signed<T>>;

template<typename T>
using Unsigned = Type<std::make_unsigned<T>>;

template<typename T>
using Unqualified = RemoveCV<RemoveRef<T>>;

template<typename T>
using ValueType = typename Unqualified<T>::value_type;

template<typename T>
using NestedValueType = ValueType<ValueType<T>>; 

template<typename T>
constexpr AddConst<T>& as_const(T& t) {
    return t;
}

template<typename T>
constexpr T abs(T t) {
    return t < 0 ? -t : t;
}

template<typename T>
constexpr T min(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr auto min(T&& t, U&& u) -> CommonType<T,U> {
    return t < u ? std::forward<T>(t) : std::forward<U>(u);
}

template<typename T, typename U, typename... Args>
constexpr auto min(T&& t, U&& u, Args&&... args) -> CommonType<T,U,Args...> {
    return min(min(std::forward<T>(t), std::forward<U>(u)), std::forward<Args>(args)...);
}

template<typename T>
constexpr T max(T&& t) {
    return std::forward<T>(t);
}

template<typename T, typename U>
constexpr auto max(T&& t, U&& u) -> CommonType<T,U> {
    return t > u ? std::forward<T>(t) : std::forward<U>(u);
}

template<typename T, typename U, typename... Args>
constexpr auto max(T&& t, U&& u, Args&&... args) -> CommonType<T,U,Args...> {
    return max(max(std::forward<T>(t), std::forward<U>(u)), std::forward<Args>(args)...);
}

struct has_append_impl {
    template<typename T>
    static auto test(T* t) -> decltype(t->append(0), Bool<true>()) {}
    template<typename>
    static auto test(...) -> Bool<false>;
};

template<typename T>
struct has_append : decltype(has_append_impl::test<T>(0)) {};

template<typename T>
struct is_nested_container {
private:
    using yes = char;
    using no = struct { char stuff[2]; };
    template<class Cont>
    static yes test(typename Cont::value_type::value_type*);
    template<class Cont>
    static no test(...);
public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
};

struct has_begin_impl {
    template<typename T>
    static auto test(T* t) -> decltype(t->begin(), Bool<true>()) {}
    template<typename>
    static auto test(...) -> Bool<false>;
};

struct has_end_impl {
    template<typename T>
    static auto test(T* t) -> decltype(t->end(), Bool<true>()) {}
    template<typename>
    static auto test(...) -> Bool<false>;
};

template<typename T>
struct has_begin : decltype(has_begin_impl::test<T>(0)) {};

template<typename T>
struct has_end : decltype(has_end_impl::test<T>(0)) {};

template<typename T>
struct has_begin_end : Bool<has_begin<T>() && has_end<T>()> {};
} // lia

#endif // LIA_DETAIL_TYPE_TRAITS_HPP