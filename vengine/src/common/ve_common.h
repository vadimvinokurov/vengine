#pragma once

#include "ve_pch.h"

#ifdef VE_PLATFORM_WINDOWS
	#ifdef VE_BUILD_DLL
		#define VE_API __declspec(dllexport)
	#else
		#define VE_API __declspec(dllimport)
	#endif
#else
	#error VEngine only support Windows!
#endif

#define BIT(x) (1 << (x))