#pragma once


#ifdef VE_PLATFORM_WINDOWS
#define NOINLINE __declspec(noinline)
#define AP_CHECK_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#error "Unsupported compiler!"
#endif

#define BIT(x) (1 << (x))