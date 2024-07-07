#include "ve_pch.h"
#include "ve_application.h"

#include "common/ve_assert.h"
#include "common/ve_log.h"
#include "glad/glad.h"
#include "imgui/ve_imgui_layer.h"
#include "math/ve_vector.h"

using namespace VE;


static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
   switch (type) {
      case ShaderDataType::Float:
         return GL_FLOAT;
      case ShaderDataType::Float2:
         return GL_FLOAT;
      case ShaderDataType::Float3:
         return GL_FLOAT;
      case ShaderDataType::Float4:
         return GL_FLOAT;
      case ShaderDataType::Mat3:
         return GL_FLOAT;
      case ShaderDataType::Mat4:
         return GL_FLOAT;
      case ShaderDataType::Int:
         return GL_INT;
      case ShaderDataType::Int2:
         return GL_INT;
      case ShaderDataType::Int3:
         return GL_INT;
      case ShaderDataType::Int4:
         return GL_INT;
      case ShaderDataType::Bool:
         return GL_BOOL;
   }

   ASSERT_FAILED("Unknown openGl type");
   return 0;
}


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


   float vertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

   vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

   BufferLayout layout = {
      {ShaderDataType::Float3, "a_Position"},
      {ShaderDataType::Float4, "a_Color"}};

   vertexBuffer->SetLayout(layout);

   uint32_t index = 0;
   for (const auto& element : vertexBuffer->GetLayout()) {
      glEnableVertexAttribArray(index);
      glVertexAttribPointer(
         index,
         element.GetComponentCount(),
         ShaderDataTypeToOpenGLBaseType(element.type),
         element.normolized ? GL_TRUE : GL_FALSE,
         layout.GetStride(),
         (const void*)element.offset);
      ++index;
   }


   unsigned int indices[3] = {0, 1, 2};
   indexBuffer.reset(IndexBuffer::Create(indices, 3));

   std::string vertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      layout(location = 1) in vec4 a_Color;
      out vec4 v_Color;

      void main()
      {
         v_Color = a_Color;
         gl_Position = vec4(a_Position, 1.0);
      }
   )";

   std::string fragmentSrc = R"(
      #version 330 core

      layout(location = 0) out vec4 color;
      in vec4 v_Color;

      void main()
      {
         color = v_Color;
      }
   )";

   shader.reset(new Shader(vertexSrc, fragmentSrc));
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

      shader->Bind();

      glBindVertexArray(vertexArray);
      glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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