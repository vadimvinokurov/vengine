#include "ve_pch.h"
#include "ve_texture.h"


#include "ve_renderer.h"
#include "platform/opengl/ve_opengl_texture.h"
using namespace VE;


VE::Ref<VE::Texture2D> VE::Texture2D::Create(const std::string& path)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::API::OpenGL:
         return std::make_shared<OpenGLTexture2D>(path);
   }


   return nullptr;
}