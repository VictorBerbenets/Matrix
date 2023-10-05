#ifndef DOUBLE_COMPARISON_
#define DOUBLE_COMPARISON_

#include <algorithm>
#include <type_traits>
#include <cmath>

namespace yLAB {

namespace cmp {

static constexpr double epsilon = 1e-6;

template<typename T>
bool are_equal(T val1, T val2,
                      T maxDiff    = epsilon,
                      T maxRelDiff = epsilon) requires(std::is_floating_point_v<T>) {
    T diff = std::fabs(val1 - val2);
    if (diff < maxDiff)
        return true;

    val1 = std::fabs(val1);
    val2 = std::fabs(val2);
    T largest = std::max(val1, val2);

    return diff < largest * maxRelDiff;
}

template<typename T>
bool is_zero(T expr) requires(std::is_floating_point_v<T>) {
    return are_equal(expr, static_cast<T>(0));
}

} // <--- namespace cmp

} // <--- namespace yLAB

#endif

