add_library(openmp STATIC
    register_benchmarks.cpp
    stream.cpp
    blacksholes.cpp
)

target_include_directories(openmp PRIVATE
        ${PROJECT_SOURCE_DIR}/include/
        )

if (UNIX)
    target_compile_options(openmp PRIVATE -mtune=native)
    if (${CMAKE_BUILD_TYPE} MATCHES "Release")
        target_compile_options(openmp PRIVATE -O3)
    endif()
endif()

if (NOT APPLE)
    find_package(OpenMP REQUIRED)
    target_link_libraries(openmp PRIVATE OpenMP::OpenMP_CXX)
else()
    find_library(OMP_LIB omp HINTS
        "/opt/homebrew/opt/libomp/lib"
        REQUIRED
    )
    find_file(OMP_INCLUDE omp.h HINTS
        "/opt/homebrew/opt/libomp/include"
        REQUIRED
    )
    #message(FATAL_ERROR $<PATH:GET_ROOT_PATH,${OMP_INCLUDE}>)
    target_compile_options(openmp PRIVATE -Xclang -fopenmp)
    target_link_libraries(openmp PRIVATE ${OMP_LIB})
    target_include_directories(openmp PRIVATE $<PATH:GET_PARENT_PATH,${OMP_INCLUDE}>)
endif()
