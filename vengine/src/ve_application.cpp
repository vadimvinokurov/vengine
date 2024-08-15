#include "ve_pch.h"
#include "ve_application.h"

#include "common/ve_assert.h"
#include "common/ve_log.h"
#include "imgui/ve_imgui_layer.h"
#include "math/ve_vector.h"
#include "renderer/ve_renderer.h"
#include "renderer/ve_render_command.h"

using namespace VE;


Application::Application()
{
   ASSERT_MSG(!instance, "Instance already registered");
   instance = this;

   loger = std::make_unique<Log>();

   window = VE::Window::Create();
   window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

   input = VE::Input::Create();

   PushOverlay(&imGuiLayer);
}


Application::~Application()
{
   PopOverlay(&imGuiLayer);
}


void Application::Run()
{
   while (running) {
      for (Layer* layer : layerStack) {
         layer->OnUpdate();
      }

      imGuiLayer.Begin();
      for (Layer* layer : layerStack) {
         layer->OnImGuiRender();
      }
      imGuiLayer.End();

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


void Application::PopLayer(Layer* layer)
{
   layerStack.PopLayer(layer);
}


void Application::PopOverlay(Layer* layer)
{
   layerStack.PopOverlay(layer);
}