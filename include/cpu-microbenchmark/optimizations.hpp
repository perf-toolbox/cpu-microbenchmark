#pragma once

#ifdef __clang__
#define FAST_MATH
#elif defined(__GNUG__) || defined(__GNUC__)
#define FAST_MATH __attribute__((optimize("-ffast-math")))
#endif
