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


#else
#define ASSERT(...)
#define ASSERT_MSG(...)
#endif

namespace VE {
NOINLINE void AssertImpl(std::string cond, std::string file, int line, std::string msg = {});
}