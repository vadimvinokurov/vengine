#pragma once

#include "common/ve_common.h"

namespace VE {
class VE_API Application {
public:
   Application();
   virtual ~Application();

   void Run();
};
}