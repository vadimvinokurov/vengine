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


VE::Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::API::OpenGL:
         return new OpenGLShader(name, vertexSrc, fragmentSrc);
   }


   return nullptr;
}


void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
{
   ASSERT(!Exists(name));
   shaders[name] = shader;
}


Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
{
   Ref<Shader> shader = Shader::Create(filepath);
   Add(shader->GetName(), shader);
   return shader;
}


Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
   Ref<Shader> shader = Shader::Create(filepath);
   Add(name, shader);
   return shader;
}


Ref<Shader> ShaderLibrary::Get(const std::string& name)
{
   if (!Exists(name)) {
      return {};
   }
   return shaders[name];
}


bool ShaderLibrary::Exists(const std::string& name) const
{
   return shaders.contains(name);
}