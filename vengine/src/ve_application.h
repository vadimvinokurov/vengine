#pragma once
#include "ve_pch.h"
#include "ve_layer.h"
#include "ve_layer_stack.h"
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
   void PushLayer(Layer* layer);
   void PushOverlay(Layer* layer);
private:
   std::unique_ptr<Window> window;
   LayerStack layerStack{};
   bool running = true;
};
}