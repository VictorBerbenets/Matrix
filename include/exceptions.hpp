#ifndef MATRIX_EXCEPTIONS_
#define MATRIX_EXCEPTIONS_

namespace matrixExcepts {

struct invalidInitMatrixSize: public std::exception {
    const char* what() const noexcept override {
        return "invalid initialization matrix size: given data size != setted matrix's size";
    }
};

struct invalidMatrixAssignment: public std::exception {
    const char* what() const noexcept override {
        return "can't assign matrix's whith different sizes";
    }
};

struct invalidMatrixAddition: public std::exception {
    const char* what() const noexcept override {
        return "can't add matrix's whith different sizes";
    }
};

struct invalidMatrixSubstraction: public std::exception {
    const char* what() const noexcept override {
        return "can't substract matrix's whith different sizes";
    }
};

struct invalidMatrixMulOperation: public std::exception {
    const char* what() const noexcept override {
        return "you cannot multiply matrices if the number of columns on the left is not equal to the number of rows on the right";
    }
};

struct invalidDeterminantCall: public std::exception {
    const char* what() const noexcept override {
        return "it is impossible to find a determinant in a non-square matrix";
    }
};

} // <--- namespace matrixExcepts

#endif

