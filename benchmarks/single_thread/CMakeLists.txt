add_library(single_thread STATIC
    register_benchmarks.cpp
    stream.cpp
)

target_include_directories(single_thread PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
)