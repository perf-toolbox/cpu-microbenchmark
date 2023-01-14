#pragma once

#include <functional>
#include <utility>

#include "cpu-microbenchmark/benchmark.hpp"

class SingleThreadBenchmark : public Benchmark {
    using runner = std::function<void(Allocator&, Timer&)>;

public:
    SingleThreadBenchmark(std::string name, runner func) : mRunner(std::move(func)), Benchmark(std::move(name)) {}

    void init() override {}

    void run(Allocator &alloc, Timer &timer) override {
        mRunner(alloc, timer);
    }

private:
    runner mRunner;
};
