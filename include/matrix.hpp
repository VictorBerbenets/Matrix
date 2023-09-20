#ifndef MATRIX_
#define MATRIX_

#include <istream>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <concepts>
#include <type_traits>

namespace yLAB {

template<typename T>
concept numeric_type = requires(T item) {
    item + item; item - item; item * item; item / item;
};

template<numeric_type T>
class Matrix final {
public:
    using size_type        = std::size_t;
    using value_type       = T;
    using pointer          = T*;
    using reference        = T&;
    using const_value_type = const value_type;
    using const_pointer    = const pointer;
    using const_reference  = const reference;
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

    Matrix(const Matrix<T>& rhs)
    : n_column_ {rhs.n_column_},
      n_line_ {rhs.n_line_},
      capacity_ {rhs.capacity_},
      data_ {new T[capacity_]} {
        std::copy(rhs.data_, rhs.data_ + capacity_, data_);
    };

    Matrix(Matrix<T>&& rhs)
    : data_     { std::exchange(rhs.data_, nullptr) },
      n_column_ { std::exchange(rhs.n_column_, 0) },
      capacity_ { std::exchange(rhs.capacity_, 0) },
      n_line_   { std::exchange(rhs.n_line_, 0) }   {};
    
    Matrix<T>& operator=(const Matrix<T>& rhs) {
        Matrix<T> tmp = rhs;
        swap(tmp);

        return *this;
    };

    Matrix<T>& operator=(Matrix<T>&& rhs) {
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
    
   // ProxyBracket operator[](size_type index1) const

    T determinant() const {
        if (n_column_ != n_line_) {
           // throw MyExcepClass; // haven't written yet
        }


    };

    T calculate_determinant() const requires(std::is_floating_point_v<T>) {
    // here will Gauss algorithm 
    }
    
    
    T calculate_determinant() const requires(std::is_integral_v<T>) {
    // here will be algrithm for integral values
    }

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
#if 0
    struct ProxyBracket {
        T& operator[](size_type index2) {
            return ...;
        };

        const T& operator[](size_type index2) const {
            return ...;
        }
    };
#endif
}; // <--- class Matrix

} // <--- namespace yLAB

#endif

