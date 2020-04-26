cmake_minimum_required(VERSION 3.17)
project(f2i)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/benchmark)

add_executable(f2i main.cc)
target_link_libraries(f2i benchmark_main)

