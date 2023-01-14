#pragma once

#include <string>
#include <functional>
#include <utility>

#include "allocator.hpp"
#include "timer.hpp"

class Benchmark {
public:
    explicit Benchmark(std::string name) : mName(std::move(name)) {}

    [[nodiscard]] const std::string &getName() const { return mName; }

    virtual void init() = 0;
    virtual void run(Allocator &alloc, Timer &timer) = 0;

    virtual ~Benchmark() = default;
private:
    std::string mName;
};
