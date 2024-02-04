#include "ve_pch.h"
#include "ve_opengl_context.h"
#include "common/ve_assert.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


VE::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
   : windowHandle(windowHandle)
{
   ASSERT(windowHandle);

   glfwMakeContextCurrent(windowHandle);
   int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
   ASSERT_MSG(gladStatus, "Could not initialize GLAD!");
}


void VE::OpenGLContext::SwapBuffers()
{
   
   glfwSwapBuffers(windowHandle);
}