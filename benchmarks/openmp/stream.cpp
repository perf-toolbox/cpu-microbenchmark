#include "benchmarks.hpp"
#include "cpu-microbenchmark/utils.hpp"

#include <vector>
#include <omp.h>

template <typename T>
static void streamCopy(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);

    alloc.random_fill(a, size);

    timer.start();
#pragma omp parallel for simd
    for (size_t i = 0; i < 1'000'000'000; i++) {
        b[i] = a[i];

    }
    timer.end();
    preserve(b);

    alloc.free(a);
    alloc.free(b);
}

template <typename T>
static void streamScale(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);

    alloc.random_fill(a, size);

    T scale = static_cast<T>(rand()  * 1000 + 1);

    timer.start();
#pragma omp parallel for
    for (size_t i = 0; i < size; i++) {
        b[i] = scale * a[i];

    }
    timer.end();
    preserve(b);

    alloc.free(a);
    alloc.free(b);
}

template <typename T>
static void streamAdd(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);
    T *c = alloc.allocate<T>(size);

    alloc.random_fill(a, size);
    alloc.random_fill(c, size);

    timer.start();
#pragma omp parallel for
    for (size_t i = 0; i < size; i++) {
        c[i] = a[i] + b[i];

    }
    timer.end();
    preserve(c);

    alloc.free(a);
    alloc.free(b);
    alloc.free(c);
}

template <typename T>
static void streamTriad(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);
    T *c = alloc.allocate<T>(size);

    alloc.random_fill(a, size);
    alloc.random_fill(c, size);

    T scale = static_cast<T>(rand()  * 1000 + 1);

    timer.start();
#pragma omp parallel for
    for (size_t i = 0; i < size; i++) {
        c[i] = a[i] + scale * b[i];

    }
    timer.end();
    preserve(c);

    alloc.free(a);
    alloc.free(b);
    alloc.free(c);
}

void createStreamOMP(std::vector<std::unique_ptr<Benchmark>> &container) {
    container.push_back(std::move(std::make_unique<OpenMPBenchmark>("stream_copy_float", streamCopy<float>)));
    container.push_back(std::move(std::make_unique<OpenMPBenchmark>("stream_copy_double", streamCopy<double>)));
    container.push_back(std::move(std::make_unique<OpenMPBenchmark>("stream_scale_float", streamScale<float>)));
    container.push_back(std::move(std::make_unique<OpenMPBenchmark>("stream_scale_double", streamScale<double>)));
    container.push_back(std::move(std::make_unique<OpenMPBenchmark>("stream_add_float", streamAdd<float>)));
    container.push_back(std::move(std::make_unique<OpenMPBenchmark>("stream_add_double", streamAdd<double>)));
    container.push_back(std::move(std::make_unique<OpenMPBenchmark>("stream_triad_float", streamTriad<float>)));
    container.push_back(std::move(std::make_unique<OpenMPBenchmark>("stream_triad_double", streamTriad<double>)));
}