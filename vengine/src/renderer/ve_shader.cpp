#include "ve_pch.h"
#include "ve_shader.h"
#include "ve_renderer.h"
#include "platform/opengl/opengl_shader.h"


using namespace VE;


Ref<Shader> Shader::Create(const std::string& file)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::API::OpenGL:
         return std::make_shared<OpenGLShader>(file);
   }


   return {};
}


VE::Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::API::OpenGL:
         return new OpenGLShader(vertexSrc, fragmentSrc);
   }


   return nullptr;
}