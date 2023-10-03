#include "end2end.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        throw std::runtime_error {"invalid numbers of arguments"};
    }
    std::size_t tests_number = std::stol(argv[1]);
    std::size_t matrix_size  = std::stol(argv[2]);
    std::size_t max_determ   = std::stol(argv[3]);

    matrix_testing::generator<long long> gen(tests_number, matrix_size, max_determ);
    gen.generate_tests();
}

