#pragma once

template <class Tp>
inline __attribute__((always_inline)) void preserve(Tp const& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

template <class Tp>
inline __attribute__((always_inline)) void preserve(Tp& value) {
#if defined(__clang__)
    asm volatile("" : "+r,m"(value) : : "memory");
#else
    asm volatile("" : "+m,r"(value) : : "memory");
#endif
}

/// A dead simple memcpy. For some reason this code achieves up to
/// 3 times better performance than libc memcpy. I might need to
/// investigate more to figure out why.
inline void memcpy_opt(void *dst, const void *src, size_t size) {
    // Assume neon support
    using vec_ty = char __attribute__((ext_vector_type(128 / 8)));

    // Assume 2 LSU ports
    const size_t main_loop_count = size / (128 / 8);
    const size_t remainder = size % (128 / 8);

    auto dst_vec = reinterpret_cast<vec_ty *>(dst);
    auto src_vec = reinterpret_cast<const vec_ty *>(src);

    for (size_t i = 0; i < main_loop_count; i += 2) {
      dst_vec[i] = src_vec[i];
      dst_vec[i + 1] = src_vec[i + 1];
    }

    auto dst_byte = reinterpret_cast<char *>(dst);
    auto src_byte = reinterpret_cast<const char *>(src);
    for (size_t i = size - remainder; i < size; i += 2) {
      dst_byte[i] = src_byte[i];
      dst_byte[i + 1] = src_byte[i + 1];
    }
}
