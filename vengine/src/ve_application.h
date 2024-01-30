#pragma once

#include "common/ve_common.h"
#include "ve_window.h"

namespace VE {
class VE_API Application {
public:
   Application();
   virtual ~Application();

   void Run();

private:
   std::unique_ptr<Window> window;
   bool running = true;
};
}