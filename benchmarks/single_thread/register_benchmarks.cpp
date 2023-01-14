#include "cpu-microbenchmark/registry.hpp"

#include "benchmarks.hpp"

void registerSingleThreadBenchmarks(std::vector<std::unique_ptr<Benchmark>> &container) {
    createStream(container);
}