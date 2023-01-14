add_library(single_thread STATIC
    register_benchmarks.cpp
    stream.cpp
)

target_include_directories(single_thread PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
)

if (UNIX)
    target_compile_options(single_thread PRIVATE -mtune=native)
    if (${CMAKE_BUILD_TYPE} MATCHES "Release")
        target_compile_options(single_thread PRIVATE -O3)
    endif()
endif()