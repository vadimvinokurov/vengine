#include "ve_pch.h"
#include "ve_framebuffer.h"

#include "ve_renderer.h"
#include "platform/opengl/opengl_framebuffer.h"


namespace VE {

Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::API::OpenGL:
         return std::make_shared<OpenGLFramebuffer>(spec);
   }

   return {};
}

} //namespace VE