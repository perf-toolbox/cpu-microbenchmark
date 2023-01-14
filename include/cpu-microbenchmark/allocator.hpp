#pragma once

#include <cstdlib>
#include <random>

class Allocator {
public:
    explicit Allocator(size_t &counter) : mCounter(counter) {}

    template <typename T>
    [[nodiscard]] T *allocate(size_t count, size_t alignment = alignof(std::max_align_t)) {
        mCounter += count * sizeof(T);
        return static_cast<T*>(std::aligned_alloc(alignment, count * sizeof(T)));
    }

    template <typename T>
    void random_fill(T *ptr, size_t count) {
        std::random_device rd;
        std::mt19937 gen(rd());
        if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dis(1.0, 2.0);

            for (size_t i = 0; i < count; i++) {
                ptr[i] = dis(gen);
            }
        } else {
            std::uniform_int_distribution<T> dis(1, 100'000);

            for (size_t i = 0; i < count; i++) {
                ptr[i] = dis(gen);
            }
        }
    }

    template <typename T>
    void free(T* ptr) {
        std::free(ptr);
    }
private:
    size_t &mCounter;
};