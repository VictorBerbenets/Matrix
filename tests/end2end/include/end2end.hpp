#pragma once

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
    using distribution_type = std::uniform_int_distribution<T>;

    static constexpr size_type MAX_MATRIX_SIZE   = 1000;
    static constexpr size_type MAX_DETERMINANT   = 1000000;
    static constexpr value_type RANDOM_MAX_COEFF = 2;
    static constexpr value_type RANDOM_MIN_COEFF = -2;
    static constexpr size_type MIN_MATRIX_SIZE   = 1;

    static constexpr value_type MAX_MATRIX_VALUE = 500;
    static constexpr value_type MIN_MATRIX_VALUE = -500;

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
        test_file << matrix_size_ << std::endl;

        auto m = upper_triangular_filling(counter);
        add_lines(m);
        write_data_to_file(test_file, m);
    }

    Matrix<T> upper_triangular_filling(size_type answ_number) {
        Matrix<T> m {matrix_size_, matrix_size_, value_type {} };
        value_type determinant {1};
        for (size_type id1 = 0; id1 < matrix_size_; ++id1) {
            for (size_type id2 = id1; id2 < matrix_size_; ++id2) {
                m[id1][id2] = random_value();
            }
            determinant *= m[id1][id1];
            if (std::abs(determinant) >= max_determ_) {
                determinant /= m[id1][id1];
                m[id1][id1] = 1;
            }
        }
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
    generator(size_type tests_number, size_type matrix_size = MAX_MATRIX_SIZE, size_type max_determ = MAX_DETERMINANT)
        : tests_number_ {tests_number}, matrix_size_ {matrix_size}, max_determ_ {max_determ} {
            if (matrix_size_ > MAX_MATRIX_SIZE) { matrix_size_ = MAX_MATRIX_SIZE; }
            if (max_determ_ > MAX_DETERMINANT) { max_determ_ = MAX_DETERMINANT; }

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
    size_type matrix_size_;
    size_type max_determ_;
    generator_type generator_;

};

} // <--- namespace matrix_testing

