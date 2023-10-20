#ifndef MATRIX_
#define MATRIX_

#include <istream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <functional>
#include <concepts>
#include <memory>
#include <type_traits>
#include <initializer_list>
#include <utility>

#include "double_comparison.hpp"
#include "matrix_iterator.hpp"
#include "exceptions.hpp"

namespace yLAB {

template<typename T>
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

template<numeric_type T>
class Matrix final {
    class ProxyBracket;
    enum class IsZero: bool { Zero = 0, nZero = 1 };
public:
    using size_type        = std::size_t;
    using value_type       = T;
    using pointer          = T*;
    using reference        = T&;
    using const_value_type = const value_type;
    using const_pointer    = const T*;
    using const_reference  = const T&;

    using iterator       = MatrixIterator<T>;
    using const_iterator = const MatrixIterator<T>;

    using matrix_size = std::pair<size_type, size_type>;
    using line_info   = std::pair<IsZero, size_type>;
/*----------------------------------------------------------------------------*/
template<typename Iter>
    Matrix(size_type n_line, size_type n_column, Iter begin, Iter end)
    : n_column_ {n_column},
      n_line_ {n_line},
      capacity_ {n_line * n_column},
      data_ {new value_type[capacity_]} {
        if (static_cast<size_type>(std::distance(begin, end)) != capacity_) {
            delete [] data_;
            throw matrixExcepts::invalidInitMatrixSize();
        }
        std::copy(begin, end, data_);
    }

    Matrix(size_type n_line, size_type n_column, const T& aggregator = {})
    : n_column_ {n_column},
      n_line_ {n_line},
      capacity_ {n_line * n_column_},
      data_ {new value_type[capacity_]} {
        std::fill(data_, data_ + capacity_, aggregator);
    }

    Matrix(size_type n_line, size_type n_column, std::initializer_list<T> ls)
    : Matrix(n_line, n_column, ls.begin(), ls.end()) {}

    Matrix(const Matrix& rhs)
    : Matrix(rhs.n_line_, rhs.n_column_, rhs.cbegin(), rhs.cend()) {}

    Matrix(Matrix&& rhs)
    : data_     { std::exchange(rhs.data_, nullptr) },
      n_column_ { std::exchange(rhs.n_column_, 0) },
      capacity_ { std::exchange(rhs.capacity_, 0) },
      n_line_   { std::exchange(rhs.n_line_, 0) }   {};

    ~Matrix() { delete[] data_; }

    Matrix& operator=(const Matrix& rhs) {
        if (this == std::addressof(rhs)) { return *this; };

        Matrix tmp = rhs;
        swap(tmp);

        return *this;
    }

    Matrix& operator=(Matrix&& rhs) {
        delete[] data_;

        data_     = std::exchange(rhs.data_, nullptr);
        n_column_ = std::exchange(rhs.n_column_, 0);
        capacity_ = std::exchange(rhs.capacity_, 0);
        n_line_   = std::exchange(rhs.n_line_, 0);

        return *this;
    }

    Matrix& operator+=(const Matrix& rhs) {
        if (size() != rhs.size()) {
            throw matrixExcepts::invalidMatrixAddition();
        }
        std::transform(cbegin(), cend(), rhs.cbegin(), begin(), std::plus<value_type>{});
        return *this;
    }

    Matrix& operator-=(const Matrix& rhs) {
        if (size() != rhs.size()) {
            throw matrixExcepts::invalidMatrixSubstraction();
        }
        std::transform(cbegin(), cend(), rhs.cbegin(), begin(), std::minus<value_type>{});
        return *this;
    }

    Matrix& operator*=(value_type coeff) {
        std::transform( cbegin(), cend(), begin(), [&coeff](auto&& val) {
                                                     return std::multiplies<value_type>{}(val, coeff);
                                                 } );
        return *this;
    }

    Matrix& operator/=(value_type coeff) {
        if (is_zero(coeff)) {
            throw std::invalid_argument{"trying to divide by 0"};
        }
        std::transform( cbegin(), cend(), begin(), [&coeff](auto&& val) {
                                                     return std::divides<value_type>{}(val, coeff);
                                                 } );
        return *this;
    }

    ProxyBracket operator[](size_type index1) {
        return ProxyBracket(data_ + n_column_ * index1);
    }

    const ProxyBracket operator[](size_type index1) const {
        return ProxyBracket(data_ + n_column_ * index1);
    }

    size_type nline() const noexcept { return n_line_; }
    size_type ncolumn() const noexcept { return n_column_; }
    bool is_square() const noexcept { return n_line_ == n_column_; }
    matrix_size size() const noexcept { return {n_line_, n_column_}; }

    void swap_lines(size_type id1, size_type id2) {
        size_type offset1 = id1 * n_column_;
        size_type offset2 = id2 * n_column_;
        std::swap_ranges( begin() + offset1, begin() + (offset1 + n_column_),
                          begin() + offset2 );
    }

    void swap(Matrix& rhs) noexcept {
        std::swap(data_, rhs.data_);
        std::swap(n_column_, rhs.n_column_);
        std::swap(n_line_, rhs.n_line_);
        std::swap(capacity_, rhs.capacity_);
    }

    Matrix& negate() & {
        for (auto& val : *this) {
            val *= -1;
        }
        return *this;
    }

    Matrix& transpose() & {
        if (is_square()) {
            return transpose_square();
        }
        auto& m     = *this;
        Matrix copy = m;
        std::swap(m.n_line_, m.n_column_);
        for (size_type i = 0; i < n_line_; ++i) {
            for (size_type j = 0; j < n_column_; ++j) {
                m[i][j] = copy[j][i];
            }
        }
        return *this;
    }

    iterator begin() noexcept { return iterator{data_}; }
    iterator end()   noexcept { return iterator{data_ + capacity_}; }
    const_iterator cbegin() const noexcept { return iterator{data_}; }
    const_iterator cend()   const noexcept { return iterator{data_ + capacity_}; }

    auto determinant() const {
        if (!is_square()) { throw matrixExcepts::invalidDeterminantCall(); }

        if constexpr (std::unsigned_integral<T>) {
            Matrix<double> m {n_line_, n_column_, cbegin(), cend()};
            return m.determinant();
        } else if (std::signed_integral<T>) {
            Matrix m = *this;
            return m.Bareiss();
        } else {
            Matrix m = *this;
            return m.Gauss();
        }
    }
private:
    value_type Gauss(); /* Gauss algorithm */
    value_type Bareiss(); /* Bareiss algorithm */

    line_info find_max_column_elem(size_type start_line, size_type column) const {
        auto& matrix = *this;
        std::pair<value_type, size_type> max_pair {value_type {}, 0};
        size_type start_id = start_line;
        for ( ; start_id < n_line_; ++start_id) {
            if (std::abs(matrix[start_id][column]) > std::abs(max_pair.first)) {
                max_pair.first  =  matrix[start_id][column];
                max_pair.second = start_id;
            }
        }
        return !is_zero(max_pair.first) ? line_info{IsZero::nZero, max_pair.second} : line_info{IsZero::Zero, 0};
    }

    line_info find_nzero_column_elem(size_type start_line, size_type column) const {
        auto& matrix = *this;
        for (size_type start_id = start_line; start_id < n_line_; ++start_id) {
            if (!is_zero(matrix[start_id][column])) {
                return {IsZero::nZero, start_id};
            }
        }
        return  {IsZero::Zero, 0};
    }

    bool is_zero(value_type val) const noexcept {
        if constexpr (std::is_floating_point_v<T>) {
            return cmp::is_zero(val);
        } else {
            return val == value_type{0};
        }
    }

    void subtract_lines(size_type line1_id, size_type line2_id, value_type coeff) {
        auto& matrix = *this;
        for (size_type index = line2_id; index < n_column_; ++index) {
           matrix[line1_id][index] -= matrix[line2_id][index] * coeff;
        }
    }

    Matrix& transpose_square() {
        auto& m = *this;
        for (size_type id1 = 0; id1 < n_line_; ++id1) {
            for (size_type id2 = id1; id2 < n_line_; ++id2) {
                std::swap(m[id1][id2], m[id2][id1]);
            }
        }
        return m;
    }
/*----------------------------------------------------------------------------*/
private:
    size_type n_column_;
    size_type n_line_;
    size_type capacity_;
    pointer data_;

    class ProxyBracket {
    public:
        ProxyBracket(pointer ptr) noexcept
            : line_ptr_ {ptr} {}

        reference operator[](size_type index2) {
            return line_ptr_[index2];
        }

        const_reference operator[](size_type index2) const {
            return line_ptr_[index2];
        }
    private:
        pointer line_ptr_;
    };

}; // <--- class Matrix

template<typename T>
Matrix<T>::value_type Matrix<T>::Gauss() { // Gauss algorithm
    auto m = *this;
    value_type determ_val {1};
    bool has_sign_changed {false};
    size_type id1 {0};
    for ( ; id1 < (n_line_ - 1); ++id1) {
        auto line_inf = m.find_max_column_elem(id1, id1);
        if (line_inf.first == IsZero::Zero) { return value_type{0}; }
        if (line_inf.second != id1)  {
            m.swap_lines(line_inf.second, id1);
            has_sign_changed = (has_sign_changed + 1) % 2;
        }
        determ_val *= m[id1][id1];
        for (auto substract_id = id1 + 1; substract_id < n_line_; ++substract_id) {
            if (!is_zero(m[substract_id][id1])) {
                auto coeff = m[substract_id][id1] / m[id1][id1];
                m.subtract_lines(substract_id, id1, coeff);
            }
        }
    }
    auto result = determ_val *= m[id1][id1] * (has_sign_changed ? -1 : 1);
    return is_zero(result) ? value_type{0} : result;
}

template<typename T>
Matrix<T>::value_type Matrix<T>::Bareiss() { // Bareiss algorithm
    auto m = *this;
    bool has_sign_changed {false};
    value_type divider {1};
    size_type k {0};
    for ( ; k < (n_line_ - 1); ++k) {
        for (size_type i = k + 1; i < n_column_; ++i ) {
            for (size_type j = k + 1; j < n_column_; ++j) {
                auto line_inf = m.find_nzero_column_elem(k, k);
                if (line_inf.first == IsZero::Zero) { return value_type{0}; }
                if (line_inf.second != k)  {
                    m.swap_lines(line_inf.second, k);
                    has_sign_changed = (has_sign_changed + 1) % 2;
                }
                m[i][j] = (m[i][j] * m[k][k] - m[i][k] * m[k][j]) / divider;
            }
        }
        divider = m[k][k];
    }
    return m[k][k] * (has_sign_changed ? -1 : 1);
}

template<typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return lhs.size() == rhs.size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template<typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    auto copy = lhs;
    return copy += rhs;
}

template<typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    auto copy = lhs;
    return copy -= rhs;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs, typename Matrix<T>::value_type coeff) {
    auto copy = lhs;
    return copy *= coeff;
}

template<typename T>
Matrix<T> operator*(typename Matrix<T>::value_type coeff, const Matrix<T>& rhs) {
    return rhs * coeff;
}

template<typename T>
Matrix<T> operator/(const Matrix<T>& lhs, typename Matrix<T>::value_type coeff) {
    auto copy = lhs;
    return copy /= coeff;
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    using size_type = Matrix<T>::size_type;

    if (lhs.ncolumn() != rhs.nline()) { throw matrixExcepts::invalidMatrixMulOperation(); }

    Matrix<T> res(lhs.nline(), rhs.ncolumn());
    for (size_type id1 = 0; id1 < lhs.nline(); ++id1) {
        for (size_type id2 = 0; id2 < rhs.ncolumn(); ++id2) {
            T mul_result {0};
            for (size_type id3 = 0; id3 < rhs.nline(); ++id3) {
                mul_result += lhs[id1][id3] * rhs[id3][id2];
            }
            res[id1][id2] = mul_result;
        }
    }
    return res;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    using size_type = typename Matrix<T>::size_type;

    auto [n_line, n_column] = matrix.size();
    for (size_type index1 = 0; index1 < n_line; ++index1) {
        for (size_type index2 = 0; index2 < n_column; ++index2) {
            os << matrix[index1][index2] << ' ';
        }
        os << std::endl;
    }
    return os;
}

} // <--- namespace yLAB

#endif
