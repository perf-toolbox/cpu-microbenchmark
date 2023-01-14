#pragma once

#include <chrono>

class Timer {
public:
    void start() {
        mStartNS = std::chrono::high_resolution_clock::now();
    }
    void end() {
        auto end = std::chrono::high_resolution_clock::now();
        mElapsedNS += std::chrono::duration_cast<std::chrono::nanoseconds>(end-mStartNS).count();
    }

    [[nodiscard]] size_t getNS() const {
        return mElapsedNS;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> mStartNS;
    size_t mElapsedNS = 0;
};