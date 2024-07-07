#include "ve_pch.h"
#include "ve_application.h"

#include "common/ve_assert.h"
#include "common/ve_log.h"
#include "glad/glad.h"
#include "imgui/ve_imgui_layer.h"
#include "math/ve_vector.h"

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

   glGenVertexArrays(1, &vertexArray);
   glBindVertexArray(vertexArray);

   glGenBuffers(1, &vertexBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

   Vector3 vertices[3] = {
      Vector3(-0.5f, -0.5f, 0.0f),
      Vector3(0.5f, -0.5f, 0.0f),
      Vector3(0.0f, 0.5f, 0.0f)};

   glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * 3, (float*)vertices, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

   glGenBuffers(1, &indexBuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

   unsigned int indices[3] = {0, 1, 2};
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


Application::~Application()
{
   PopOverlay(&imGuiLayer);
}


void Application::Run()
{
   while (running) {
      glClearColor(0.1f, 0.1f, 0.1f, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      glBindVertexArray(vertexArray);
      glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

      for (Layer* layer : layerStack) {
         layer->OnUpdate();
      }

      imGuiLayer.Begin();
      for (Layer* layer : layerStack) {
         layer->OnImGuiRender();
      }
      imGuiLayer.End();

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


void Application::PopLayer(Layer* layer)
{
   layerStack.PopLayer(layer);
}


void Application::PopOverlay(Layer* layer)
{
   layerStack.PopOverlay(layer);
}