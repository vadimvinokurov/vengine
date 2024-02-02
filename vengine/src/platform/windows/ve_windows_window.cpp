#include "ve_pch.h"
#include "common/ve_assert.h"
#include "common/ve_log.h"
#include "ve_windows_window.h"
#include "events/ve_application_event.h"
#include "events/ve_key_event.h"
#include "events/ve_mouse_event.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace {
static void GLFWErrorCallback(int error, const char* description)
{
   ASSERT_MSG(false, "GLFW error {} {}", error, description);
}
} //namespace


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
      glfwSetErrorCallback(GLFWErrorCallback);
      ASSERT_MSG(success, "Could not initialize GLFW!");
      GLFWInitilized = true;
   }

   pWindow = glfwCreateWindow((int)width, (int)height, title.c_str(), nullptr, nullptr);
   glfwMakeContextCurrent(pWindow);
   int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
   ASSERT_MSG(gladStatus, "Could not initialize GLAD!");
   glfwSetWindowUserPointer(pWindow, this);
   SetVSync(true);

   glfwSetWindowSizeCallback(pWindow, [](GLFWwindow* window, int width, int height) {
      auto* _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

      _this->width = width;
      _this->height = height;

      WindowResizeEvent windowResizeEvent(width, height);
      _this->eventCallback(windowResizeEvent);
   });

   glfwSetWindowCloseCallback(pWindow, [](GLFWwindow* window) {
      auto* _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

      WindowCloseEvent windowCloseEvent;
      _this->eventCallback(windowCloseEvent);
   });

   glfwSetKeyCallback(pWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
      auto* _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));


      switch (action) {
         case GLFW_PRESS:
            {
               KeyPressedEvent event(key, 0);
               _this->eventCallback(event);
               break;
            }
         case GLFW_RELEASE:
            {
               KeyReleasedEvent event(key);
               _this->eventCallback(event);
               break;
            }
         case GLFW_REPEAT:
            {
               KeyPressedEvent event(key, 1);
               _this->eventCallback(event);
               break;
            }
      }
   });

   glfwSetMouseButtonCallback(pWindow, [](GLFWwindow* window, int button, int action, int mods) {
      auto* _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

      switch (action) {
         case GLFW_PRESS:
            {
               MouseButtonPressedEvent event(button);
               _this->eventCallback(event);
               break;
            }
         case GLFW_RELEASE:
            {
               MouseButtonReleasedEvent event(button);
               _this->eventCallback(event);
               break;
            }
      }
   });

   glfwSetScrollCallback(pWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
      auto* _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

      MouseScrolledEvent event((float)xOffset, (float)yOffset);
      _this->eventCallback(event);
   });

   glfwSetCursorPosCallback(pWindow, [](GLFWwindow* window, double x, double y) {
      auto* _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

      MouseMovedEvent event((float)x, (float)y);
      _this->eventCallback(event);
   });
}


void VE::WindowsWindow::Shutdown()
{
   glfwDestroyWindow(pWindow);
}