#pragma once

#include "common/ve_common.h"
#include "ve_window.h"
#include "events/ve_application_event.h"

namespace VE {
class VE_API Application {
public:
   Application();
   virtual ~Application();

   void Run();
   void OnEvent(Event& event);
   bool OnWindowClose(WindowCloseEvent& event);
private:
   std::unique_ptr<Window> window;
   bool running = true;
};
}