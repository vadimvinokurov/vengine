#include "ve_pch.h"
#include "ve_windows_window.h"
#include "common/ve_assert.h"
#include "ve_log.h"

#include <GLFW/glfw3.h>

std::unique_ptr<VE::Window> VE::Window::Create(const VE::WindowsProps& props)
{
   return std::make_unique<WindowsWindow>(props);
}


VE::WindowsWindow::WindowsWindow(const WindowsProps& props)
{
   Init(props);
}


VE::WindowsWindow::~WindowsWindow()
{
   Shutdown();
}


void VE::WindowsWindow::OnUpdate()
{
   glfwPollEvents();
   glfwSwapBuffers(pWindow);
}


std::pair<unsigned, unsigned> VE::WindowsWindow::GetSize() const
{
   return {width, height};
}


void VE::WindowsWindow::SetEventCallback(const EventCallback& cb)
{
   eventCallback = cb;
}


void VE::WindowsWindow::SetVSync(bool enabled)
{
   glfwSwapInterval(enabled ? 1 : 0);
   vsync = enabled;
}


bool VE::WindowsWindow::IsVSync() const
{
   return vsync;
}


void VE::WindowsWindow::Init(const WindowsProps& props)
{
   title = props.title;
   width = props.width;
   height = props.height;

   VE_INFO("Creating window {} ({}, {})", title, width, height);

   if (!GLFWInitilized) {
      int success = glfwInit();
      ASSERT_MSG(success, "Could not initialize GLFW!");
      GLFWInitilized = true;
   }

   pWindow = glfwCreateWindow((int)width, (int)height, title.c_str(), nullptr, nullptr);
   glfwMakeContextCurrent(pWindow);
   glfwSetWindowUserPointer(pWindow, this);
   SetVSync(true);
}


void VE::WindowsWindow::Shutdown()
{
   glfwDestroyWindow(pWindow);
}