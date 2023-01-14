#include "cpu-microbenchmark/registry.hpp"

#include "benchmarks.hpp"

void registerOpenMPBenchmarks(std::vector<std::unique_ptr<Benchmark>> &container) {
    createStream(container);
}
