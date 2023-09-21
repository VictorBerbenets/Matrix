#ifndef DOUBLE_COMPARISON_
#define DOUBLE_COMPARISON

#include <cmath>

namespace yLAB {
    
namespace cmp {

static constexpr double epsilon = 1e-6;

inline bool are_equal(double val1, double val2,
                      double maxDiff    = epsilon,
                      double maxRelDiff = epsilon) {
    double diff = std::fabs(val1 - val2);
    if (diff < maxDiff)
        return true;

    val1 = std::fabs(val1);
    val2 = std::fabs(val2);
    double largest = std::max(val1, val2);

    return diff < largest * maxRelDiff;
}

inline bool is_zero(double expr) {
    return are_equal(expr, 0);
}

} // <--- namespace cmp

} // <--- namespace yLAB
#endif
