#include "ve_pch.h"
#include "ve_buffer.h"
#include "ve_renderer.h"
#include "common/ve_assert.h"
#include "platform/opengl/ve_opengl_buffer.h"

using namespace VE;


uint32_t BufferElement::GetComponentCount() const
{
   switch (type) {
      case ShaderDataType::Float:
         return 1;
      case ShaderDataType::Float2:
         return 2;
      case ShaderDataType::Float3:
         return 3;
      case ShaderDataType::Float4:
         return 4;
   }

   ASSERT_FAILED("Unknow element count");
   return 0;
}


void BufferLayout::CalculateOffsetAndStride()
{
   uint32_t offset = 0;
   stride = 0;
   for (auto& element : elements) {
      element.offset = offset;
      offset += element.size;
      stride += element.size;
   }
}


VertexBuffer* VertexBuffer::Create(const float* vertices, uint32_t size)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::API::OpenGL:
         return new OpenGLVertexBuffer(vertices, size);
   }

   return nullptr;
}


IndexBuffer* IndexBuffer::Create(const uint32_t* indices, uint32_t count)
{
   switch (Renderer::GetAPI()) {
      case RendererAPI::API::None:
         ASSERT_FAILED("RendererAPI::None is currently not supported");
      case RendererAPI::API::OpenGL:
         return new OpenGLIndexBuffer(indices, count);
   }

   return nullptr;
}