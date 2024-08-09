#include "ve_pch.h"
#include "ve_vertex_array.h"


#include "ve_renderer.h"
#include "platform/opengl/ve_opengl_vertex_array.h"

using namespace VE;


VertexArray* VertexArray::Create()
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::OpenGL:
         return new OpenGLVertexArray();
   }

   return nullptr;
}