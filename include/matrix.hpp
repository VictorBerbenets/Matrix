#ifndef MATRIX_
#define MATRIX_

#include <istream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <utility>

#include "double_comparison.hpp"
#include "matrix_iterator.hpp"

namespace yLAB {

namespace my_concepts {

template<typename T>
concept numeric_type = requires(T item) {
    item + item; item - item; item * item; item / item;
};

} // <--- namespace my_concepts

template<my_concepts::numeric_type T>
class Matrix final {
    struct ProxyBracket;

    enum class IsZero: char { Zero = 0, nZero = 1 };
public:
    using size_type        = std::size_t;
    using value_type       = T;
    using pointer          = T*;
    using reference        = T&;
    using const_value_type = const value_type;
    using const_pointer    = T* const;
    using const_reference  = const T&;

    using iterator       = typename iterator::MatrixIterator<T>;
    using const_iterator = const typename iterator::MatrixIterator<T>;

    using matrix_size = std::pair<size_type, size_type>;
    using line_info   = std::pair<IsZero, size_type>;      
/*----------------------------------------------------------------------------*/
template<typename Iter>
    Matrix(size_type n_column, size_type n_line, Iter begin, Iter end)
    : n_column_ {n_column},
      n_line_ {n_line},
      capacity_ {n_line * n_column},
      data_ {new T[capacity_]} {
        if (static_cast<size_type>(std::distance(begin, end)) != capacity_) {
            throw std::invalid_argument{"data size != matrix's size"};
        }
        std::copy(begin, end, data_);
    }

    Matrix(size_type n_column, size_type n_line, std::istream& is)
    : n_column_ {n_column},
      n_line_ {n_line},
      capacity_ {n_line * n_column},
      data_ {new T[capacity_]} {
        for (size_type count = 0; count < capacity_; ++count) {
            T tmp {};
            is >> tmp;
            if (!is.good()) {
                throw std::runtime_error{"data reading error"};
            }
            data_[count] = tmp;
        }
    }
    
    Matrix(size_type n_column, size_type n_line, const T& aggregator = {})
    : n_column_ {n_column},
      n_line_ {n_line},
      capacity_ {n_line * n_column_},
      data_ {new T[capacity_]} {
        std::fill(data_, data_ + capacity_, aggregator);
    }

    Matrix(const Matrix& rhs)
    : n_column_ {rhs.n_column_},
      n_line_ {rhs.n_line_},
      capacity_ {rhs.capacity_},
      data_ {new T[capacity_]} {
        std::copy(rhs.data_, rhs.data_ + capacity_, data_);
    }

    Matrix(Matrix&& rhs) noexcept
    : data_     { std::exchange(rhs.data_, nullptr) },
      n_column_ { std::exchange(rhs.n_column_, 0) },
      capacity_ { std::exchange(rhs.capacity_, 0) },
      n_line_   { std::exchange(rhs.n_line_, 0) }   {};

    Matrix& operator=(const Matrix& rhs) {
        Matrix<T> tmp = rhs;
        swap(tmp);

        return *this;
    }

    Matrix& operator=(Matrix&& rhs) noexcept {
        delete[] data_;

        data_     = std::exchange(rhs.data_, nullptr);
        n_column_ = std::exchange(rhs.n_column_, 0);
        capacity_ = std::exchange(rhs.capacity_, 0);
        n_line_   = std::exchange(rhs.n_line_, 0);

        return *this;
    }

    ~Matrix() {
        delete[] data_;
    }

    ProxyBracket operator[](size_type index1) {
        return ProxyBracket(data_ + n_column_ * index1);
    }

    const ProxyBracket operator[](size_type index1) const {
        return ProxyBracket(data_ + n_column_ * index1);
    }

    bool is_square() const noexcept { return n_line_ == n_column_; }
    matrix_size get_size() const noexcept { return {n_line_, n_column_}; }

    void swap_lines(size_type id1, size_type id2) {
        static auto& matrix = *this;
        for (size_type counter = 0; counter < n_column_; ++counter) {
            std::swap(matrix[id1][counter], matrix[id2][counter]);
        }
    }
    
    Matrix& negate() & {
        for (auto& val : *this) {
            val *= -1;
        }
        return *this;
    }

    Matrix& transpose() & {
        auto& m = *this;
        auto copy = m;
        for (size_type i = 0; i < n_column_; ++i) {
            for (size_type j = 0; j < n_line_; ++j) {
                m[i][j] = copy[j][i];
            }
        }
        std::swap(n_line_, n_column_);
        return *this;
    }

    iterator begin() { return iterator{data_}; }
    iterator end()   { return iterator{data_ + capacity_}; }
    const_iterator cbegin() const { return iterator{data_}; }
    const_iterator cend()   const { return iterator{data_ + capacity_}; }

    T determinant() const {
        if (!is_square()) {
           // throw MyExcepClass; // haven't written yet
        }
        return calculate_determinant();
    }

    T calculate_determinant() const; /* Gauss algorithm */
    T calculate_determinant() const requires(std::is_integral_v<T>); /* Bareiss algorithm */
private:
    void swap(Matrix& rhs) {
        std::swap(data_, rhs.data_);
        std::swap(n_column_, rhs.n_column_);
        std::swap(n_line_, rhs.n_line_);
        std::swap(capacity_, rhs.capacity_);
    }

    line_info find_nzero_column_elem(size_type start_line, size_type column) const {
        static auto& matrix = *this;
        for (size_type start_id = start_line; start_id < n_line_; ++start_id) {
            if constexpr (std::is_floating_point_v<T>) {
                if (!cmp::is_zero(matrix[start_id][column])) {
                    return {IsZero::nZero, start_id};
                }
            } else {
                if (matrix[start_id][column] != 0) {
                    return {IsZero::nZero, start_id};
                }
            }
        }
        return {IsZero::Zero, 0};
    }

    void subtract_lines(size_type line1_id, size_type line2_id, value_type coeff) {
        static auto& matrix = *this;
        for (size_type index = line2_id; index < n_column_; ++index) {
           matrix[line1_id][index] -= matrix[line2_id][index] * coeff; 
        }
    }
/*----------------------------------------------------------------------------*/
private:
    size_type n_column_;
    size_type n_line_;
    size_type capacity_;
    pointer data_;

    class ProxyBracket {
    public:
        ProxyBracket(pointer ptr)
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
T Matrix<T>::calculate_determinant() const { // Gauss algorithm
    auto matrix = *this;
    value_type determ_val {1.0};
    bool has_sign_changed {0};
    size_type id1 {0};
    for ( ; id1 < (n_line_ - 1); ++id1) {
        auto line_inf = matrix.find_nzero_column_elem(id1, id1);
        if (line_inf.first == IsZero::Zero) { return 0; }
        if (line_inf.second != id1)  {
            matrix.swap_lines(line_inf.second, id1);
            has_sign_changed = (has_sign_changed + 1) % 2;
        }
        determ_val *= matrix[id1][id1];
        for (auto substract_id = id1 + 1; substract_id < n_line_; ++substract_id) {
            if ( !cmp::is_zero(matrix[id1][substract_id]) ) {
                auto coeff = matrix[substract_id][id1] / matrix[id1][id1];
                matrix.subtract_lines(substract_id, id1, coeff);
            }
        }
    }
    return determ_val *= matrix[id1][id1] * (has_sign_changed ? -1 : 1);
}

template<typename T>
T Matrix<T>::calculate_determinant() const requires(std::is_integral_v<T>) { // Bareiss algorithm
    auto m = *this;
    bool has_sign_changed {0};
    value_type divider {1};
    size_type k {0};
    for ( ; k < (n_line_ - 1); ++k) {
        for (size_type i = k + 1; i < n_column_; ++i ) {
            for (size_type j = k + 1; j < n_column_; ++j) {
                auto line_inf = m.find_nzero_column_elem(k, k);
                if (line_inf.first == IsZero::Zero) { return 0; }
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
    return lhs.get_size() == rhs.get_size() &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    using size_type = Matrix<T>::size_type;

    auto [n_line, n_column] = matrix.get_size();
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

