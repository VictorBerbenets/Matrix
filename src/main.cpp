#include <iostream>
#include <vector>
#include <set>

#include "matrix.hpp"

template<typename T>
auto get_data(std::vector<T>& data) {
    using namespace yLAB;
    using size_type = typename Matrix<T>::size_type;

    std::istream_iterator<T> is {std::cin};
    size_type matrix_size = *is++;
    auto data_size = matrix_size * matrix_size;

    data.reserve(data_size);
    for (size_type counter = 0; counter < (data_size - 1); ++counter) {
        data.push_back(*is++);
    }
    data.push_back(*is);

    return matrix_size;
}

int main() {
#ifdef INTEGRAL_MATRIX
    std::vector<int> data {};
    auto size = get_data(data);
    yLAB::Matrix<int> m(size, size, data.cbegin(), data.cend());
#else
    std::vector<double> data {};
    auto size = get_data(data);
    yLAB::Matrix<double> m(size, size, data.cbegin(), data.cend());
#endif
    std::cout << m.determinant() << std::endl;
}

