cmake_minimum_required (VERSION 2.8.11)

project(PYFLAVOR)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++-3.6")
set(CMAKE_C_COMPILER "/usr/bin/clang-3.6")

include_directories(py)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runtest ./tests/builtin.cc)
target_link_libraries(runtest ${GTEST_BOTH_LIBRARIES})
target_compile_options(runtest PUBLIC --std=c++1y)

target_link_libraries(runtest pthread)
