#pragma once
#include "renderer/ve_graphics_context.h"

struct GLFWwindow;


namespace VE {
class OpenGLContext : public GraphicsContext {
public:
   OpenGLContext(GLFWwindow* windowHandle);
   virtual void SwapBuffers() override;

private:
   GLFWwindow* windowHandle;
};
}