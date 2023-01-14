add_library(openmp STATIC
    register_benchmarks.cpp
    stream.cpp
)

target_include_directories(openmp PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
        )

if (NOT APPLE)
    find_package(OpenMP REQUIRED)
    target_link_libraries(openmp PRIVATE ${OpenMP_C_LIBRARY})
else()
    find_library(OMP_LIB omp HINTS
        "/opt/homebrew/opt/libomp/lib"
        REQUIRED
    )
    target_compile_options(openmp PRIVATE -Xclang -fopenmp)
    target_link_libraries(openmp PRIVATE ${OMP_LIB})
endif()