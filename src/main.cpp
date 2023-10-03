#include <iostream>
#include <iterator>
#include <vector>

#include "matrix.hpp"

template<typename T>
auto get_data(std::vector<T>& data) {
    using size_type = typename yLAB::Matrix<T>::size_type;

    std::istream_iterator<T> is {std::cin};
    size_type matrix_size = *is++;

    data.insert(data.cend(), is, std::istream_iterator<T> {});

    return matrix_size;
}

int main() {
#ifdef INTEGRAL_MATRIX
    std::vector<long long> data {};
    auto size = get_data(data);
    yLAB::Matrix<long long> m(size, size, data.cbegin(), data.cend());
#else
    std::vector<long double> data {};
    auto size = get_data(data);
    yLAB::Matrix<long double> m(size, size, data.cbegin(), data.cend());
#endif
    std::cout << m.determinant() << std::endl;
}

