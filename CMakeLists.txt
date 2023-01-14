cmake_minimum_required(VERSION 3.24)
project(cpu_microbenchmark)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(benchmarks)

add_executable(cpu_microbenchmark main.cpp)

target_include_directories(cpu_microbenchmark PRIVATE include)

target_link_libraries(cpu_microbenchmark PRIVATE
    single_thread
    openmp
)