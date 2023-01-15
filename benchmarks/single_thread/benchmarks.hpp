#pragma once

#include "single_thread_benchmark.hpp"

#include <memory>
#include <vector>

void createStream(std::vector<std::unique_ptr<Benchmark>> &container);
