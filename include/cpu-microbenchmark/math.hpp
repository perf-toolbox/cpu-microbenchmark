#pragma once

#include <cmath>

namespace cpu_benchmark {
template <typename T> inline T exp(T input) { return std::exp(input); }

template <typename T> inline T sqrt(T input) { return std::sqrt(input); }

template <typename T> inline T log(T input) { return std::log(input); }

} // namespace cpu_benchmark
