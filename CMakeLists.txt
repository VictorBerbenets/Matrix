cmake_minimum_required(VERSION 3.15)

project(matrix)

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

aux_source_directory(./src SRC_DIR)

add_executable(${PROJECT_NAME} ${SRC_DIR})

target_include_directories( ${PROJECT_NAME}
                            PRIVATE
                            ${INCLUDE_DIR})

option(INTEGRAL_MATRIX "what tipe of matrix to generate" OFF)

if (INTEGRAL_MATRIX)
    target_compile_definitions( ${PROJECT_NAME}
                                PRIVATE
                                INTEGRAL_MATRIX )
endif()

find_package(GTest REQUIRED)
enable_testing()

find_package(Threads REQUIRED)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

add_subdirectory(tests)
