#ifndef END2END_TESTING_
#define END2END_TESTING_

#include <iostream>
#include <random>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <climits>
#include <cmath>

#include "matrix.hpp"

namespace matrix_testing {
    using namespace yLAB;
namespace dirs {
    const std::string resource_dir = "../tests/end2end/resources/";
    const std::string tests_dir    = "../tests/end2end/resources/tests/";
    const std::string ans_dir      = "../tests/end2end/resources/answers/";
}

template<typename T>
class generator {
    using size_type      = std::size_t;
    using value_type     = T;
    using generator_type = std::mt19937;

#ifdef INTEGRAL_MATRIX
    using distribution_type = std::uniform_int_distribution<T>;
#else
    using distribution_type = std::uniform_real_distribution<T>;
#endif

    static constexpr value_type MAX_MATRIX_VALUE = 5;
    static constexpr value_type MIN_MATRIX_VALUE = 1;
    static constexpr value_type RANDOM_MAX_COEFF = 2;
    static constexpr value_type RANDOM_MIN_COEFF = -2;
    static constexpr size_type MAX_MATRIX_SIZE   = 100;
    static constexpr size_type MIN_MATRIX_SIZE   = 1;

    static constexpr value_type MAX_TYPE_SIZE = std::pow(2, sizeof(value_type) * 8) / 2 - 1;
    static constexpr value_type MIN_TYPE_SIZE = -(MAX_TYPE_SIZE + 1);

    void create_source_directory() {
        using namespace std::filesystem;
        directory_entry resource_dir(dirs::resource_dir);

        if (!resource_dir.is_directory()) {
            create_directory(dirs::resource_dir);
            create_directory(dirs::tests_dir);
            create_directory(dirs::ans_dir);
        } else {
            const path tests_path{dirs::tests_dir};
            const path answs_path{dirs::ans_dir};

            for (auto& dir_iter : directory_iterator{tests_path}) {
                remove(dir_iter.path());
            }
            for (auto& dir_iter : directory_iterator{answs_path}) {
                remove(dir_iter.path());
            }
        }
    }
 
    value_type random_value(T min_val = MIN_MATRIX_VALUE, T max_val = MAX_MATRIX_VALUE) {
        distribution_type distr(min_val, max_val);
        return distr(generator_);
    } 
    
    size_type random_unsigned(size_type min_val = MIN_MATRIX_SIZE, size_type max_val = MAX_MATRIX_SIZE) {
        std::uniform_int_distribution<size_type> distr(min_val, max_val);
        return distr(generator_);
    }   
 
    void generate_matrix(size_type counter) {
        std::string file_name = "test" + std::to_string(counter) + ".txt";
        std::ofstream test_file {dirs::tests_dir + file_name};
        auto matrix_size = random_unsigned();
        test_file << matrix_size << std::endl;

        auto m = upper_triangular_filling(matrix_size, counter);
        add_lines(m);
        std::cout << "FINAL DET\n";
        std::cout << m.determinant() << std::endl;
        std::cout << m << std::endl;
        write_data_to_file(test_file, m);
    }
    
    Matrix<T> upper_triangular_filling(size_type matrix_size, size_type answ_number) {
        Matrix<T> m {matrix_size, matrix_size, value_type {} };
        value_type determinant {1};
        for (size_type id1 = 0; id1 < matrix_size; ++id1) {
            for (size_type id2 = id1; id2 < matrix_size; ++id2) {
                m[id1][id2] = random_value();
               // std::cout << "RANDOM VALUE:\n";
                //std::cout << m[id1][id2] << std::endl;
            }
            determinant *= m[id1][id1];
            if (std::abs(determinant) >= MAX_TYPE_SIZE) {
                std::cout << "MAX VALUE:\n";
                std::cout << MAX_TYPE_SIZE << std::endl;

                determinant /= m[id1][id1];
                m[id1][id1] = 1;
            }
        }
#if 0
        std::cout << "UPPER MATRIX: " << std::endl;
#endif
        //std::cout << m << std::endl;
        std::cout << "DET AFTER TRIANGULAR\n";
        std::cout << determinant << std::endl;
        std::string ans_name = "answ" + std::to_string(answ_number) + ".txt";
        std::ofstream answ_file {dirs::ans_dir + ans_name};
        answ_file << determinant << std::endl;
        return m;
    }

    void add_lines(Matrix<T>& m) {
        for (size_type id1 = 1; id1 < m.nline(); ++id1) {
            auto coeff = random_value(RANDOM_MIN_COEFF, RANDOM_MAX_COEFF);
            for (size_type id2 = 0; id2 < m.ncolumn(); ++id2) {
                m[id1][id2] += m[0][id2] * coeff;
            }
        }
    }
    
    void write_data_to_file(std::ofstream& test_file, const Matrix<T>& m) {
        test_file << m << std::endl;
    }

public:
    generator(size_type tests_number)
        : tests_number_ {tests_number} {
            generator_.seed( static_cast<size_type>(std::time(nullptr)) );
    }
    
    void generate_tests() {
        create_source_directory();

        for (size_type counter = 1; counter <= tests_number_; ++counter) { 
            generate_matrix(counter);
        }
        
    }

private:
    size_type tests_number_;
    generator_type generator_;

};

} // <--- namespace matrix_testing

#endif

