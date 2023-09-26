#include <gtest/gtest.h>

#include "matrix.hpp"

using namespace yLAB;

TEST(Matrix, Addition1) {
    Matrix<long long> m1 {2, 2, {1, 2, 3, 4}};
    Matrix<long long> m2 {2, 2, {2, 4, 6, 8}};
    Matrix<long long> ans {2, 2, {3, 6, 9, 12}};

    ASSERT_EQ(m1 + m2, ans);
}

TEST(Matrix, Addition2) {
    Matrix<long long> m1 {1, 1, 100};
    Matrix<long long> m2 {1, 1, 5};
    Matrix<long long> ans {1, 1, 105};

    ASSERT_EQ(m1 + m2, ans);
}

TEST(Matrix, Addition3) {
    Matrix<long long> m1 {1000, 1000, 0};
    Matrix<long long> m2 {1000, 1000, 1000};
    Matrix<long long> ans {1000, 1000, 1000};

    ASSERT_EQ(m1 + m2, ans);
}

TEST(Matrix, Addition4) {
    Matrix<long long> m1 {3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    Matrix<long long> m2 {3, 3, 0};
    Matrix<long long> ans {3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};

    ASSERT_EQ(m1 + m2, ans);
}

TEST(Matrix, Addition5) {
    Matrix<long long> m1 {5, 5, 1};
    Matrix<long long> m2 {5, 5, 1};
    Matrix<long long> ans {5, 5, 2};

    ASSERT_EQ(m1 + m2, ans);
}


TEST(Matrix, Substraction1) {
    Matrix<long long> m1 {1, 1, 100};
    Matrix<long long> m2 {1, 1, 5};
    Matrix<long long> ans {1, 1, 95};
    
    ASSERT_EQ(m1 - m2, ans);
}

TEST(Matrix, Substraction2) {
    Matrix<long long> m1 {50, 50, 100};
    Matrix<long long> m2 {50, 50, 100};
    Matrix<long long> ans {50, 50, 0};
    
    ASSERT_EQ(m1 - m2, ans);
}

TEST(Matrix, Substraction3) {
    Matrix<long long> m1 {1, 1, 5};
    Matrix<long long> m2 {1, 1, 5};
    Matrix<long long> ans {1, 1, 0};
    
    ASSERT_EQ(m1 - m2, ans);
}

TEST(Matrix, Substraction4) {
    Matrix<long long> m1 {100, 100, -10};
    Matrix<long long> m2 {100, 100, 500};
    Matrix<long long> ans {100, 100, -510};
    
    ASSERT_EQ(m1 - m2, ans);
}

TEST(Matrix, Substraction5) {
    Matrix<long long> m1 {3, 3, {1, 0, 0, 0, 1, 0, 0, 0, 1}};
    Matrix<long long> m2 {3, 3, 0};
    Matrix<long long> ans {3, 3, {1, 0, 0, 0, 1, 0, 0, 0, 1}};
    
    ASSERT_EQ(m1 - m2, ans);
}

TEST(Matrix, ScalarMul1) {
    Matrix<long long> m1 {3, 3, {1, 0, 0, 0, 1, 0, 0, 0, 1}};
    long long coeff = 0;
    Matrix<long long> ans {3, 3, 0};

    ASSERT_EQ(m1 *= coeff, ans);
}

TEST(Matrix, ScalarMul2) {
    Matrix<long long> m1 {3, 3, {-1, 0, 0, 0, -1, 0, 0, 0, -1}};
    long long coeff = -10;
    Matrix<long long> ans {3, 3, {10, 0, 0, 0, 10, 0, 0, 0, 10}};

    ASSERT_EQ(m1 * coeff, ans);
}

TEST(Matrix, ScalarMul3) {
    Matrix<long long> m1 {3, 3, 0};
    long long coeff = 100000;
    Matrix<long long> ans {3, 3, 0};

    ASSERT_EQ(coeff * m1, ans);
}

TEST(Matrix, ScalarMul4) {
    Matrix<long long> m1 {1, 1, 500};
    long long coeff = 10;
    Matrix<long long> ans {1, 1, 5000};

    ASSERT_EQ(m1 *=coeff, ans);
}

TEST(Matrix, ScalarMul5) {
    Matrix<long long> m1 {3, 3, 0};
    long long coeff = 0;
    Matrix<long long> ans {3, 3, 0};

    ASSERT_EQ(coeff * m1, ans);
}

TEST(Matrix, ScalarDivision1) {
    Matrix<long long> m1 {3, 3, 0};
    long long coeff = -100;
    Matrix<long long> ans {3, 3, 0};

    ASSERT_EQ(m1 /= coeff, ans);
}

TEST(Matrix, ScalarDivision2) {
    Matrix<long long> m1 {3, 3, 3};
    long long coeff = 3;
    Matrix<long long> ans {3, 3, 1};

    ASSERT_EQ(m1 / coeff, ans);
}

TEST(Matrix, ScalarDivision3) {
    Matrix<long long> m1 {1, 1, 100 };
    long long coeff = -100;
    Matrix<long long> ans {1, 1, -1};

    ASSERT_EQ(m1 / coeff, ans);
}

TEST(Matrix, ScalarDivision4) {
    Matrix<long long> m1 {500, 500, 1000000};
    long long coeff = -10000;
    Matrix<long long> ans {500, 500, -100};

    ASSERT_EQ(m1 /= coeff, ans);
}

TEST(Matrix, ScalarDivision5) {
    Matrix<long long> m1 {500, 500, 0};
    long long coeff = -10000000;
    Matrix<long long> ans {500, 500, 0};

    ASSERT_EQ(m1 / coeff, ans);
}

