#include "ve_pch.h"
#include "ve_assert.h"
#include "ve_log.h"

NOINLINE void VE::AssertImpl(std::string cond, std::string file, int line, std::string msg)
{
   std::string logMsg = std::format("{}({}): {}. ", file, line, cond) + msg;
   VE_ERROR(logMsg);

   if (IsDebuggerPresent()) { //TODO: encapsulate to platform code
      __debugbreak();
      return;
   }

   int* invalidPointer = nullptr;
   *invalidPointer = 0xFFFF;
}