#ifndef END2END_TESTING_
#define END2END_TESTING_

#include <iostream>
#include <random>
#include <ctime>

#include "matrix.hpp"

namespace yLAB {

namespace matrix_testing {

namespace dirrs {
#if 0
    const std::string resource_dir;
    const std::string resource_dir;
    const std::string resource_dir;
#endif
}


template<typename T>
class generator {
    using size_type      = std::size_t;
    using value_type     = T;
    using generator_type = std::mt19937;
#if 0
#if type(T)
    using distribution_type = std::uniform_real_distribution<T>;
#else
    using distribution_type = std::uniform_int_distribution<T>;
#endif
#endif
    void create_source_directory(const std::string& file_name) const {

    }

    value_type random_float(T min_val, T max_val) const {
        std::uniform_real_distribution<T> distr(min_val, max_val);
        return distr(generator_);
    }

    value_type random_int(T min_val, T max_val) const {
        std::uniform_int_distribution<T> distr(min_val, max_val);
        return distr(generator_);
    }
    
    void generate_matrix() const requires(std::is_integral_v<T>);
    void generate_matrix() const requires(std::is_floating_point_v<T>);
public:
    generator(size_type tests_number)
        : tests_number_ {tests_number} {
            generator_.seed( static_cast<size_type>(std::time(nullptr)) );
    }
    
    void generate_tests() const {
        
    }

private:
    size_type tests_number_;
    generator_type generator_;

};

template<typename T>
void generator<T>::generate_matrix() const requires(std::is_integral_v<T>) {

}

template<typename T>
void generator<T>::generate_matrix() const requires(std::is_floating_point_v<T>) {
    
}

} // <--- namespace matrix_testing

} // <--- namespace yLAB

#endif

