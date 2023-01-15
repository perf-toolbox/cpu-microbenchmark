#include "benchmarks.hpp"
#include "cpu-microbenchmark/utils.hpp"

#include <vector>
#include <cstring>
#include <memory>

template <typename T>
void streamCopy(Allocator &alloc, Timer &timer) {
    T *a = alloc.allocate<T>(1'000'000'000);
    T *b = alloc.allocate<T>(1'000'000'000);

    alloc.random_fill(a, 1'000'000'000);

    timer.start();
    for (size_t i = 0; i < 1'000'000'000; i++) {
        b[i] = a[i];

    }
    timer.end();
    preserve(b);

    alloc.free(a);
    alloc.free(b);
}

template <typename T>
void streamMemcpy(Allocator &alloc, Timer &timer) {
    T *a = alloc.allocate<T>(1'000'000'000);
    T *b = alloc.allocate<T>(1'000'000'000);

    alloc.random_fill(a, 1'000'000'000);

    timer.start();
    std::memcpy(b, a, sizeof(T) * 1'000'000'000);
    timer.end();
    preserve(b);

    alloc.free(a);
    alloc.free(b);
}

template <typename T>
void streamScale(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);

    alloc.random_fill(a, size);

    T scale = static_cast<T>(rand()  * 1000 + 1);

    timer.start();
    for (size_t i = 0; i < size; i++) {
        b[i] = scale * a[i];

    }
    timer.end();
    preserve(b);

    alloc.free(a);
    alloc.free(b);
}

template <typename T>
void streamAdd(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);
    T *c = alloc.allocate<T>(size);

    alloc.random_fill(a, size);
    alloc.random_fill(c, size);

    timer.start();
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
void streamTriad(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);
    T *c = alloc.allocate<T>(size);

    alloc.random_fill(a, size);
    alloc.random_fill(c, size);

    T scale = static_cast<T>(rand()  * 1000 + 1);

    timer.start();
    for (size_t i = 0; i < size; i++) {
        c[i] = a[i] + scale * b[i];

    }
    timer.end();
    preserve(c);

    alloc.free(a);
    alloc.free(b);
    alloc.free(c);
}
void createStream(std::vector<std::unique_ptr<Benchmark>> &container) {
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_copy_float", streamCopy<float>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_copy_double", streamCopy<double>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_memcpy_float", streamMemcpy<float>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_memcpy_double", streamMemcpy<double>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_scale_float", streamScale<float>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_scale_double", streamScale<double>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_add_float", streamAdd<float>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_add_double", streamAdd<double>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_triad_float", streamTriad<float>)));
    container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_triad_double", streamTriad<double>)));
}
