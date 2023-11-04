#pragma once

#include <concepts>

namespace my_concepts {

template <typename T>
concept numeric_type = std::copy_constructible<T> &&
                       std::copyable<T> &&
                       requires(T item1, std::size_t n) {
    { item1 + item1 } -> std::convertible_to<T>;
    { item1 - item1 } -> std::convertible_to<T>;
    { item1 * item1 } -> std::convertible_to<T>;
    { item1 / item1 } -> std::convertible_to<T>;

    { item1 == item1 } -> std::convertible_to<bool>;
    { item1 != item1 } -> std::convertible_to<bool>;

    { delete new T[n] };
    { T {0} };
    { T {1} };
};

} // <--- namespace my_concepts
