#include <gtest/gtest.h>

#include "matrix.hpp"

using namespace yLAB;

TEST(Matrix, Multiplication1) {
    Matrix<int> m1 {2, 2, {4, 2, 9, 0}};
    Matrix<int> m2 {2, 2, {3, 1, -3, 4}};
    Matrix<int> ans {2, 2, {6, 12, 27, 9}};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication2) {
    Matrix<int> m1 {3, 2, {2, 1, -3, 0, 4, -1}};
    Matrix<int> m2 {2, 3, {5, -1, 6, -3, 0, 7}};
    Matrix<int> ans {3, 3, {7, -2, 19, -15, 3, -18, 23, -4, 17}};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication3) {
    Matrix<int> m1 {3, 3, {2, -1, 3, 4, 2, 0, -1, 1, 1}};
    Matrix<int> m2 {3, 1, {1, 2, -1}};
    Matrix<int> ans {3, 1, {-3, 8, 0}};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication4) {
    Matrix<int> m1 {3, 1, {1, 2, 3}};
    Matrix<int> m2 {1, 3, {-2, -3, 4}};
    Matrix<int> ans {3, 3, {-2, -3, 4, -4, -6, 8, -6, -9, 12}};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication5) {
    Matrix<int> m1 {1, 3, {-2, -3, 4}};
    Matrix<int> m2 {3, 1, {1, 2, 3}};
    Matrix<int> ans {1, 1, {4}};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication6) {
    Matrix<int> m1 {2, 2, {3, 5, 2, 1}};
    Matrix<int> m2 {2, 3, {8, 2, 3, 1, 7, 2}};
    Matrix<int> ans {2, 3, {29, 41, 19, 17, 11, 8}};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication7) {
    Matrix<int> m1 {3, 3, {1, 4, 3, 2, 1, 5, 3, 2, 1}};
    Matrix<int> m2 {3, 3, {5, 2, 1, 4, 3, 2, 2, 1, 5}};
    Matrix<int> ans {3, 3, {27, 17, 24, 24, 12, 29, 25, 13, 12}};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication8) {
    Matrix<int> m1 {2, 2, {100, 101, 102, 103}};
    Matrix<int> m2 {2, 2, {1, 0, 0, 1}};
    Matrix<int> ans {2, 2, {100, 101, 102, 103}};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication9) {
    Matrix<int> m1 {4, 4, {1, 0, 2, -1, -2, 0, -4, 2, 1, 0, 2, -1, 3, 0, 6, -3}};
    Matrix<int> m2 {4, 4, {2, 1, 3, -1, -4, -2, -6, 2, 2, 1, 3, -1, 6, 3, 9, -3}};
    Matrix<int> ans {4, 4, 0};

    ASSERT_EQ(ans, m1 * m2);
}

TEST(Matrix, Multiplication10) {
    Matrix<int> m1 {4, 4, {1, 0, 2, -1, -2, 0, -4, 2, 1, 0, 2, -1, 3, 0, 6, -3}};
    Matrix<int> m2 {4, 4, 0};
    Matrix<int> ans {4, 4, 0};

    ASSERT_EQ(ans, m1 * m2);
}
