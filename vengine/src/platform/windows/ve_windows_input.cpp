#include "ve_pch.h"
#include "ve_windows_input.h"

#include "common/ve_assert.h"

#include "ve_application.h"
#include <GLFW/glfw3.h>

std::unique_ptr<VE::Input> VE::Input::Create()
{
   return std::make_unique<VE::WindowsInput>();
}


VE::WindowsInput::WindowsInput()
{
   if (instance) {
      ASSERT_FAILED("Already inited");
      return;
   }

   instance = this;
}


bool VE::WindowsInput::IsKeyPressedImpl(int keycode)
{
   GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
   auto state = glfwGetKey(window, keycode);
   return state == GLFW_PRESS || state == GLFW_REPEAT;
}


bool VE::WindowsInput::IsKeyMouseButtonPressedImpl(int keycode)
{
   GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
   auto state = glfwGetMouseButton(window, keycode);
   return state == GLFW_PRESS;
}


std::pair<float, float> VE::WindowsInput::GetMousePositionImpl()
{
   GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get()->GetWindow().GetNativeWindow());
   double xpos, ypos;
   glfwGetCursorPos(window, &xpos, &ypos);

   return {(float)xpos, (float)ypos};
}