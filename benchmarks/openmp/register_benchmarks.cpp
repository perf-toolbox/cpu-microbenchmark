#include "cpu-microbenchmark/registry.hpp"

#include "benchmarks.hpp"

void registerOpenMPBenchmarks(std::vector<std::unique_ptr<Benchmark>> &container) {
    createStreamOMP(container);
    createBS(container);
}
