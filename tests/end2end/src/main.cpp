#include "end2end.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        throw std::runtime_error {"invalid numbers of arguments"};
    }
    std::size_t tests_number = std::stol(argv[1]);
#ifdef INTEGRAL_MATRIX
    matrix_testing::generator<int> gen(tests_number);
#else
    matrix_testing::generator<double> gen(tests_number);
#endif
    gen.generate_tests();
}

