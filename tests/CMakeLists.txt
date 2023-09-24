cmake_minimum_required(VERSION 3.15)

project(tests)

enable_testing()
add_subdirectory(googletest)

aux_source_directory(./unit UNIT)
aux_source_directory(./end2end/src END2END)

add_executable(unit ${UNIT})
add_executable(end2end ${END2END})

target_include_directories( unit
                            PRIVATE googletest/
                            PRIVATE ${INCLUDE_DIR}
                          )
target_link_libraries(unit gtest_main gmock_main)

if (INTEGRAL_MATRIX)
    target_compile_definitions( end2end
                                PRIVATE
                                INTEGRAL_MATRIX )
endif()

target_include_directories( end2end
                            PRIVATE end2end/include
                            PRIVATE ${INCLUDE_DIR}
                          )
set_target_properties(
    unit end2end PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

