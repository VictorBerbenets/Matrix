#ifndef MATRIX_
#define MATRIX_

#include <istream>
#include <stdexcept>

namespace yLAB {

template<typename T, std::size_t N>
class Matrix final {
    using size_type        = std::size_t;
    using value_type       = T;
    using pointer          = T*;
    using reference        = T&;
    using const_value_type = const value_type;
    using const_pointer    = const pointer;
    using const_reference  = const reference;
public:
template<typename Iter>
    Matrix(Iter begin, Iter end)
    : data_ { new T[N*N] } {
        //std::cout << "BEFORE COPY\n";
        std::copy(begin, end, data_);
        //std::cout << "AFTER  COPY\n";
    };

    Matrix(std::istream& is)
    : data_ { new T[N*N] } {
        for (size_type count = 0; count < N * N; ++count) {
            T tmp {};
            is >> tmp;
            if (!is.good()) {
                throw std::runtime_error{"data reading error"};
            }
            *(data_ + count) = tmp;
        }

    };

    Matrix(const Matrix<T, N>& rhs) {
        data_ = new T[N*N];
        std::cout << "BEFORE COPY\n";
        std::copy(rhs.data_, rhs.data_ + N, data_);
        std::cout << "AFTER  COPY\n";
        column_ = rhs.column_;
        line_   = rhs.line_;
    };

    Matrix(Matrix<T, N>&& rhs)
    : data_   { std::move(rhs.data_) },
      column_ { rhs.column_ },
      line_   { rhs.line_ } {
        rhs.column_ = 0;  
        rhs.line_   = 0;  
    };
    
    Matrix<T, N>& operator=(const Matrix<T, N>& rhs) {
        //delete[] data_;
        std::cout << "BEING\n";
        Matrix<T, N> tmp = rhs;
        std::cout << "END\n";
        Swap(tmp, *this);

        return *this;
    };

    Matrix<T, N>& operator=(Matrix<T, N>&& rhs) {
        data_   = std::move(rhs.data_);
        column_ = rhs.column_;
        line_   = rhs.line_;
        rhs.column_ = 0;
        rhs.line_   = 0;

        return *this;
    };

    ~Matrix() {
        delete[] data_;
    };

    void Swap(Matrix<T, N>& lhs, Matrix<T, N> rhs) {
        std::swap(lhs.data_, rhs.data_);
        std::swap(lhs.column_, rhs.column_);
        std::swap(lhs.line_, rhs.line_);
    };

private:
    pointer data_;
    size_type column_ {0};
    size_type line_ {0};
}; // <--- class Matrix

} // <--- namespace yLAB

#endif

