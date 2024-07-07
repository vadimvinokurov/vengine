#include "ve_pch.h"
#include "ve_opengl_context.h"
#include "common/ve_assert.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>


#include "common/ve_log.h"


VE::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
   : windowHandle(windowHandle)
{
   ASSERT(windowHandle);

   glfwMakeContextCurrent(windowHandle);
   int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
   ASSERT_MSG(gladStatus, "Could not initialize GLAD!");
   VE_LOG_MSG("OpenGL Info: ");
   VE_LOG_MSG(" Vender: {0}", (const char*)glGetString(GL_VENDOR));
   VE_LOG_MSG(" Renderer: {0}", (const char*)glGetString(GL_RENDERER));
   VE_LOG_MSG(" Version: {0}", (const char*)glGetString(GL_VERSION));
}


void VE::OpenGLContext::SwapBuffers()
{
   
   glfwSwapBuffers(windowHandle);
}