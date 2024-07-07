#include "ve_pch.h"
#include "ve_buffer.h"
#include "ve_renderer.h"
#include "common/ve_assert.h"
#include "platform/opengl/ve_opengl_buffer.h"

using namespace VE;


VertexBuffer* VertexBuffer::Create(const float* vertices, uint32_t size)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::OpenGL:
         return new OpenGLVertexBuffer(vertices, size);
   }

   return nullptr;
}


IndexBuffer* IndexBuffer::Create(const uint32_t* indices, uint32_t size)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::OpenGL:
         return new OpenGLIndexBuffer(indices, size);
   }

   return nullptr;
}