#include <gtest/gtest.h>

#include "matrix.hpp"

using namespace yLAB;

TEST(Matrix, Transpose1) {
    Matrix<int> m {2, 2, {4, 2, 9, 0}};
    m.transpose();
    Matrix<int> ans {2, 2, {4, 9, 2, 0}};

    ASSERT_EQ(m, ans);
}

TEST(Matrix, Transpose2) {
    Matrix<int> m {3, 2, {2, 1, -3, 0, 4, -1}};
    m.transpose();
    Matrix<int> ans {2, 3, {2, -3, 4, 1, 0, -1}};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose3) {
    Matrix<int> m {3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    m.transpose();
    Matrix<int> ans {3, 3, {1, 4, 7, 2, 5, 8, 3, 6, 9}};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose4) {
    Matrix<int> m {2, 3, {1, 2, 3, 4, 5, 6}};
    m.transpose();
    Matrix<int> ans {3, 2, {1, 4, 2, 5, 3, 6}};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose5) {
    Matrix<int> m {4, 4, {1, 11, 185, 13, 5, 12, 9, 26, 6, 9, 19, 21, 10, 14, 13, 2}};
    m.transpose();
    Matrix<int> ans {4, 4, {1, 5, 6, 10, 11, 12, 9, 14, 185, 9, 19, 13, 13, 26, 21, 2}};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose6) {
    Matrix<int> m {1, 1, 1000000};
    m.transpose();
    Matrix<int> ans {1, 1, 1000000};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose7) {
    Matrix<int> m {3, 3, {1, 0, 0, 0, 1, 0, 0, 0, 1}};
    m.transpose();
    Matrix<int> ans {3, 3, {1, 0, 0, 0, 1, 0, 0, 0, 1}};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose8) {
    Matrix<int> m {2, 2, {0, 0, 0, 0}};
    m.transpose();
    Matrix<int> ans {2, 2, {0, 0, 0, 0}};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose9) {
    Matrix<int> m {1, 10, {-1, -2, -3, -4, -5, 5, 6, 7, 8, 9}};
    m.transpose();
    Matrix<int> ans {10, 1, {-1, -2, -3, -4, -5, 5, 6, 7, 8, 9}};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose10) {
    Matrix<int> m {10, 1, {-1, -2, -3, -4, -5, 5, 6, 7, 8, 9}};
    m.transpose();
    Matrix<int> ans {1, 10, {-1, -2, -3, -4, -5, 5, 6, 7, 8, 9}};

    ASSERT_EQ(m, ans);

}

TEST(Matrix, Transpose11) {
    Matrix<double> m {10, 1, {-1.5, -2.643, -3.245, -4.64326, -5.245, 5.5643634, 6.6234, 7.643, 8.9679, 9.234}};
    m.transpose();
    Matrix<double> ans {1, 10, {-1.5, -2.643, -3.245, -4.64326, -5.245, 5.5643634, 6.6234, 7.643, 8.9679, 9.234}};

    ASSERT_EQ(m, ans);

}

