#include "benchmarks.hpp"
#include "cpu-microbenchmark/utils.hpp"
#include "cpu-microbenchmark/optimizations.hpp"

#include <vector>
#include <cstring>
#include <memory>

template <typename T>
static FAST_MATH void stream_copy(Allocator &alloc, Timer &timer) {
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
static FAST_MATH void stream_memcpy(Allocator &alloc, Timer &timer) {
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
static FAST_MATH void stream_scale(Allocator &alloc, Timer &timer) {
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
static FAST_MATH void stream_add(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);
    T *c = alloc.allocate<T>(size);

    alloc.random_fill(a, size);
    alloc.random_fill(b, size);

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
static FAST_MATH void stream_add3(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);
    T *c = alloc.allocate<T>(size);
    T *d = alloc.allocate<T>(size);

    alloc.random_fill(a, size);
    alloc.random_fill(b, size);
    alloc.random_fill(c, size);

    timer.start();
    for (size_t i = 0; i < size; i++) {
        d[i] = a[i] + b[i] + c[i];

    }
    timer.end();
    preserve(d);

    alloc.free(a);
    alloc.free(b);
    alloc.free(c);
    alloc.free(d);
}

template <typename T>
static FAST_MATH void stream_add4(Allocator &alloc, Timer &timer) {
    constexpr size_t size = 1'000'000'000;
    T *a = alloc.allocate<T>(size);
    T *b = alloc.allocate<T>(size);
    T *c = alloc.allocate<T>(size);
    T *d = alloc.allocate<T>(size);

    alloc.random_fill(a, size);
    alloc.random_fill(b, size);
    alloc.random_fill(c, size);

    timer.start();
    for (size_t i = 0; i < size; i++) {
        d[i] = a[i] + b[i] + c[i];

    }
    timer.end();
    preserve(d);

    alloc.free(a);
    alloc.free(b);
    alloc.free(c);
    alloc.free(d);
}

template <typename T>
static FAST_MATH void stream_triad(Allocator &alloc, Timer &timer) {
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

#define ADD_BENCHMARK(name, dataTy) \
  container.push_back(std::move(std::make_unique<SingleThreadBenchmark>("stream_" # name  "_" # dataTy, stream_##name<dataTy>)));

#define ADD_ALL_TYPES(name) \
  ADD_BENCHMARK(name, float); \
  ADD_BENCHMARK(name, double); 

void createStream(std::vector<std::unique_ptr<Benchmark>> &container) {
    ADD_ALL_TYPES(copy);
    ADD_ALL_TYPES(memcpy);
    ADD_ALL_TYPES(scale);
    ADD_ALL_TYPES(add);
    ADD_ALL_TYPES(add3);
    ADD_ALL_TYPES(add4);
    ADD_ALL_TYPES(triad);
}
