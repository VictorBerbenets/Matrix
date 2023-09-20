#ifndef MATRIX_
#define MATRIX_

#include <istream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <utility>

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
public:
    using size_type        = std::size_t;
    using value_type       = T;
    using pointer          = T*;
    using reference        = T&;
    using const_value_type = const value_type;
    using const_pointer    = T const *;
    using const_reference  = const reference;
    using matrix_size      = std::pair<size_type, size_type>;
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
    };

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
    };
    
    Matrix(size_type n_column, size_type n_line, const T& aggregator = {})
    : n_column_ {n_column},
      n_line_ {n_line},
      capacity_ {n_line * n_column_},
      data_ {new T[capacity_]} {
        std::fill(data_, data_ + capacity_, aggregator);
    };

    Matrix(const Matrix& rhs)
    : n_column_ {rhs.n_column_},
      n_line_ {rhs.n_line_},
      capacity_ {rhs.capacity_},
      data_ {new T[capacity_]} {
        std::copy(rhs.data_, rhs.data_ + capacity_, data_);
    };

    Matrix(Matrix&& rhs)
    : data_     { std::exchange(rhs.data_, nullptr) },
      n_column_ { std::exchange(rhs.n_column_, 0) },
      capacity_ { std::exchange(rhs.capacity_, 0) },
      n_line_   { std::exchange(rhs.n_line_, 0) }   {};
    
    Matrix& operator=(const Matrix& rhs) {
        Matrix<T> tmp = rhs;
        swap(tmp);

        return *this;
    };

    Matrix& operator=(Matrix&& rhs) {
        delete[] data_;

        data_     = std::exchange(rhs.data_, nullptr);
        n_column_ = std::exchange(rhs.n_column_, 0);
        capacity_ = std::exchange(rhs.capacity_, 0);
        n_line_   = std::exchange(rhs.n_line_, 0);

        return *this;
    };

    ~Matrix() {
        delete[] data_;
    };
    
    /*ProxyBracket operator[](size_type index1) {
        return ProxyBracket(data_ + n_column_ * index1);
    }*/
    
    ProxyBracket operator[](size_type index1) const {
        return ProxyBracket(data_ + n_column_ * index1);
    }

    T determinant() const {
        if (!is_square()) {
           // throw MyExcepClass; // haven't written yet
        }
        return calculate_determinant();

    };
    // Gauss Algorithm
    T calculate_determinant() const requires(std::is_floating_point_v<T>) {
        
    }
    
    
    T calculate_determinant() const requires(std::is_integral_v<T>) {
    // here will be algrithm for integral values
    }
    
    bool is_square() const noexcept { return n_line_ == n_column_; };
    matrix_size get_size() const noexcept { return {n_line_, n_column_}; };
private:
    void swap(Matrix<T>& rhs) {
        std::swap(data_, rhs.data_);
        std::swap(n_column_, rhs.n_column_);
        std::swap(n_line_, rhs.n_line_);
        std::swap(capacity_, rhs.capacity_);
    };
/*----------------------------------------------------------------------------*/
private:
    size_type n_column_;
    size_type n_line_;
    size_type capacity_;
    pointer data_;

    struct ProxyBracket {
        ProxyBracket(pointer ptr)
            : line_ptr_ {ptr} {};

        reference operator[](size_type index2) {
            return line_ptr_[index2];
        };

        const_reference operator[](size_type index2) const {
            return line_ptr_[index2];
        }
        /*-------------------------------------------------*/    
        pointer line_ptr_;
    };

}; // <--- class Matrix

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

