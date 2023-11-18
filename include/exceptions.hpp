#pragma once

#include <exception>

namespace matrixExcepts {

struct invalidInitMatrixSize: public std::exception {
    const char* what() const noexcept override {
        return "invalid initialization matrix size: given data size != set matrix's size";
    }
};

struct invalidMatrixAddition: public std::exception {
    const char* what() const noexcept override {
        return "can't add matrices whit different sizes";
    }
};

struct invalidMatrixSubstraction: public std::exception {
    const char* what() const noexcept override {
        return "can't substract matrices whit different sizes";
    }
};

struct invalidMatrixMulOperation: public std::exception {
    const char* what() const noexcept override {
        return "you cannot multiply matrices with not suitable parameters";
    }
};

struct invalidDeterminantCall: public std::exception {
    const char* what() const noexcept override {
        return "it is impossible to find a determinant in a non-square matrix";
    }
};

} // <--- namespace matrixExcepts

