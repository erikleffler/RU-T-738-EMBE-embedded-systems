#pragma once
#include <stdint.h>

// For paramaters unknown at compile time

template <typename T>
constexpr T bit(const uint_fast8_t bit_index) {
    return T(1U << bit_index);
}

template <typename T>
constexpr T bits(const uint_fast8_t bit_index) {
    return bit<T>(bit_index);
}

template <typename T, typename... TBits>
constexpr T bits(const uint_fast8_t bit_index,
                 const TBits... remaining_bit_indices) {
    return bit<T>(bit_index) | bits(remaining_bit_indices...);
}

// Templated for paramaters known at compile time

template <typename T, T bit_index>
constexpr T bit() {
    return T(1U << bit_index);
}

template <typename T>
constexpr T bits() {
    return T(0);
}

template <typename T, T bit_index, T... remaining_bit_indices>
constexpr T bits() {
    return T(bit<T, bit_index>() | bits<T, remaining_bit_indices...>());
}
