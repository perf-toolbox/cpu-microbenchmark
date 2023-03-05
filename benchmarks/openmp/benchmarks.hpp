#pragma once

#include "omp_benchmark.hpp"

#include <memory>
#include <vector>

void createStreamOMP(std::vector<std::unique_ptr<Benchmark>> &container);
void createBS(std::vector<std::unique_ptr<Benchmark>> &container);
