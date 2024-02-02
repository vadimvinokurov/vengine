#pragma once

#include "common/ve_common.h"

#ifndef VE_RETAIL

#define ASSERT(cond)                            \
   do {                                         \
      if (!(cond)) {                            \
         AssertImpl(#cond, __FILE__, __LINE__); \
      }                                         \
   } while (false)

#define ASSERT_MSG(cond, formatStr, ...)                                                   \
   do {                                                                                    \
      if (!(cond)) {                                                                       \
         VE::AssertImpl(#cond, __FILE__, __LINE__, std::format(formatStr, ##__VA_ARGS__)); \
      }                                                                                    \
   } while (false)

#define ASSERT_FAILED(formatStr, ...) ASSERT_MSG(false, formatStr, ##__VA_ARGS__)

#else
#define ASSERT(...)
#define ASSERT_MSG(...)
#define ASSERT_FAILED(...)
#endif

namespace VE {
NOINLINE void AssertImpl(std::string cond, std::string file, int line, std::string msg = {});
}