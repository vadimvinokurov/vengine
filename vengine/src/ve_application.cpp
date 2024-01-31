#include "ve_pch.h"

#include "ve_application.h"
#include "ve_log.h"

#include <GLFW/glfw3.h>

using namespace VE;


Application::Application()
{
   Log::Init();
   window = VE::Window::Create();
   window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}


Application::~Application()
{
}


void Application::Run()
{
   while (running) {
      glClearColor(1, 0, 1, 1);
      glClear(GL_COLOR_BUFFER_BIT);
      window->OnUpdate();
   }
}


void Application::OnEvent(Event& event)
{
   EventDispatcher dispatcher(event);
   dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
   VE_TRACE("{}", event);
}


bool Application::OnWindowClose(WindowCloseEvent& event)
{
   running = false;

   return true;
}