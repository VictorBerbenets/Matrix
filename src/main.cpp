#include <iostream>
#include <vector>
#include <set>

#include "matrix.hpp"

int main() {
    using namespace yLAB;
    std::vector<int> vec {1, 2, 3, 4};

    Matrix<int> m {2, 2, vec.begin(), vec.end()};
    Matrix<double> m5 {2, 2, vec.begin(), vec.end()};
    m5.determinant();
    Matrix<std::size_t> m6 {2, 2, vec.begin(), vec.end()};
    Matrix<char> m7 {2, 2, vec.begin(), vec.end()};
    m7.determinant();
    Matrix<int> m8 {2, 2, vec.begin(), vec.end()};
    int x = 0;
    m8[1][0] = x;
    //Matrix<std::set> m9 {2, 2, vec.begin(), vec.end()};
    m = std::move(Matrix<int> {2, 2, 1});

    m.determinant();
   /* m[1][1] = 100;
    m[0][1] = 1100;
    m[0][0] = 1010;
    m[1][0] = 1001;
*/
   // std::cout << m;
}

