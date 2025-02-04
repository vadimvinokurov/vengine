﻿#include "ve_pch.h"
#include "ve_vertex_array.h"


#include "ve_renderer.h"
#include "platform/opengl/ve_opengl_vertex_array.h"

using namespace VE;


VE::Ref<VertexArray> VertexArray::Create()
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::API::OpenGL:
         return VE::Ref<VertexArray>{new OpenGLVertexArray()};
   }

   return nullptr;
}