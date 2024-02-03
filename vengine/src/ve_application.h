#pragma once
#include "ve_pch.h"
#include "ve_layer.h"
#include "ve_layer_stack.h"
#include "common/ve_common.h"
#include "ve_window.h"
#include "events/ve_application_event.h"
#include "platform/windows/ve_windows_input.h"

namespace VE {
class VE_API Application {
public:
   Application();
   virtual ~Application();

   inline static Application* Get() { return instance; }


   void Run();
   void OnEvent(Event& event);
   bool OnWindowClose(WindowCloseEvent& event);
   void PushLayer(Layer* layer);
   void PushOverlay(Layer* layer);

   Window& GetWindow() { return *window; }

private:
   std::unique_ptr<Window> window;
   LayerStack layerStack{};
   WindowsInput input{};
   bool running = true;

   inline static Application* instance = nullptr;
};

}