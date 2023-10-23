cmake_minimum_required(VERSION 3.15)

project(tests)

aux_source_directory(./unit UNIT)
aux_source_directory(./end2end/src END2END)

add_executable(unit ${UNIT})
add_executable(end2end ${END2END})

target_include_directories( unit
                            PRIVATE ${INCLUDE_DIR}
                          )

target_link_libraries( unit
                       PRIVATE ${GTEST_LIBRARIES}
                       PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                     )

target_include_directories( end2end
                            PRIVATE end2end/include
                            PRIVATE ${INCLUDE_DIR}
                          )
set_target_properties(
    unit end2end PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

