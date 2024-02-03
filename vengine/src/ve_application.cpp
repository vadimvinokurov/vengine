#include "ve_pch.h"
#include "common/ve_log.h"
#include "ve_application.h"

#include <glad/glad.h>


#include "common/ve_assert.h"
#include "imgui/ve_imgui_layer.h"
#include "math/ve_vector.h"

using namespace VE;


Application::Application()
{
   ASSERT(!instance);

   instance = this;
   Log::Init();
   window = VE::Window::Create();
   window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
   imGuiLayer = std::make_unique<ImGuiLayer>();
   PushOverlay(imGuiLayer.get());
}


Application::~Application()
{
   layerStack.PopOverlay(imGuiLayer.get());
}


void Application::Run()
{
   while (running) {
      glClearColor(1, 0, 1, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      for (Layer* layer : layerStack) {
         layer->OnUpdate();
      }

      imGuiLayer->Begin();
      for (Layer* layer : layerStack) {
         layer->OnImGuiRender();
      }
      imGuiLayer->End();

      Vector3 v(1, 2, 3);

      VE_LOG_ERROR("{} {} {}", Input::GetMousePosition().first, Input::GetMousePosition().second, v);

      window->OnUpdate();
   }
}


void Application::OnEvent(Event& event)
{
   EventDispatcher dispatcher(event);
   dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
   VE_LOG_TRACE("{}", event);

   for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it) {
      (*it)->OnEvent(event);
      if (event.IsHandled()) {
         break;
      }
   }
}


bool Application::OnWindowClose(WindowCloseEvent& event)
{
   running = false;

   return true;
}


void Application::PushLayer(Layer* layer)
{
   layerStack.PushLayer(layer);
}


void Application::PushOverlay(Layer* layer)
{
   layerStack.PushOverlay(layer);
}