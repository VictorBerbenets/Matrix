#ifndef MATRIX_
#define MATRIX_

namespace yLAB {

template<typename T, std::size_t N>
class Matrix {
    using size_type        = std::size_t;
    using value_type       = T;
    using pointer          = T*;
    using reference        = T&;
    using const_value_type = const value_type;
    using const_pointer    = const pointer;
    using const_reference  = const reference;
public:
template<typename Iter>
    Matrix(Iter begin, Iter end) {
        data = new T(N);

    };
    Matrix(const Matrix<T, N>& rhs) {

    };
    Matrix(Matrix<T, N>&& rhs)
    : data   { std::move(rhs.data) },
      column { rhs.column },
      line   { rhs.line } {
        rhs.column = 0;  
        rhs.line   = 0;  
    };
    
    Matrix<T, N>& operator=(const Matrix<T, N>& rhs) {
        delete[] data;
        data = new T[N];
        
        std::copy(rhs.data.begin(), rhs.data.end(), data);
        column = rhs.column;
        line   = rhs.line;

        return *this;

    };

    Matrix<T, N>& operator=(Matrix<T, N>&& rhs) {
        data = std::move(rhs.data);
        column = rhs.column;
        line   = rhs.line;
        rhs.column = 0;
        rhs.line   = 0;

        return *this;
    };

    ~Matrix() {
        delete[] data;
    };

private:
    const_pointer data;
    size_type column {0};
    size_type line {0};
};

}

#endif

