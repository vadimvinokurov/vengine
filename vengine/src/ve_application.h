#pragma once
#include "ve_pch.h"
#include "ve_layer.h"
#include "ve_layer_stack.h"
#include "common/ve_common.h"
#include "ve_window.h"
#include "common/ve_log.h"
#include "events/ve_application_event.h"
#include "imgui/ve_imgui_layer.h"
#include "platform/windows/ve_windows_input.h"

namespace VE {
class Application {
public:
   inline static Application* Get() { return instance; }

   Application();
   virtual ~Application();

   void Run();
   void OnEvent(Event& event);
   bool OnWindowClose(WindowCloseEvent& event);
   void PushLayer(Layer* layer);
   void PushOverlay(Layer* layer);
   void PopLayer(Layer* layer);
   void PopOverlay(Layer* layer);

   Window& GetWindow() { return *window; }

private:
   std::unique_ptr<Log> loger;
   std::unique_ptr<Window> window;
   std::unique_ptr<Input> input;

   ImGuiLayer imGuiLayer;
   LayerStack layerStack;
   bool running = true;

   inline static Application* instance = nullptr;
};

}