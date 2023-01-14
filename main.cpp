#include "cpu-microbenchmark/registry.hpp"

#include <iostream>

void runAllBenchmarks(std::vector<std::unique_ptr<Benchmark>> &allBenchmarks) {
    for (auto &bench : allBenchmarks) {
        Timer timer;
        size_t memCounter = 0;
        Allocator allocator{memCounter};
        bench->init();
        bench->run(allocator, timer);

        double bandwidth = static_cast<double>(memCounter) / static_cast<double>(timer.getNS());
        std::cout.precision(2);
        std::cout.setf(std::ios::fixed);
        std::cout << bench->getName() << " " << bandwidth << "GB/s\n";
    }
}

int main() {
    std::vector<std::unique_ptr<Benchmark>> allBenchmarks;

    registerSingleThreadBenchmarks(allBenchmarks);

    runAllBenchmarks(allBenchmarks);

    return 0;
}
