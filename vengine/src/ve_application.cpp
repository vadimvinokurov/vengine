#include "ve_pch.h"

#include "ve_application.h"
#include "ve_log.h"

#include <GLFW/glfw3.h>

using namespace VE;

Application::Application()
{
   Log::Init();
   window = VE::Window::Create();
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