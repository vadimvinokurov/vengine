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
#include "renderer/ve_buffer.h"
#include "renderer/ve_camera.h"
#include "renderer/ve_shader.h"
#include "renderer/ve_vertex_array.h"

namespace VE {
class Application {
public:
   inline static Application* Get() { return instance; }

   Application();
   virtual ~Application();

   void Run();
   void OnEvent(Event& event);
   bool OnWindowCloseEvent(WindowCloseEvent& event);
   bool OnWindowResizeEvent(WindowResizeEvent& event);
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

   float lastFrameTime = 0.0f;
   bool minimized = false;
   inline static Application* instance = nullptr;
};

}