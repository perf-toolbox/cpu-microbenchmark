#pragma once

#include <vector>

#include "benchmark.hpp"

void registerSingleThreadBenchmarks(std::vector<std::unique_ptr<Benchmark>>&);
void registerOpenMPBenchmarks(std::vector<std::unique_ptr<Benchmark>>&);
