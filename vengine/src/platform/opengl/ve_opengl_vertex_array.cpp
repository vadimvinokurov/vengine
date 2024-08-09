#include "ve_pch.h"
#include "ve_opengl_vertex_array.h"


#include "glad/glad.h"

using namespace VE;


static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
   switch (type) {
      case ShaderDataType::Float:
         return GL_FLOAT;
      case ShaderDataType::Float2:
         return GL_FLOAT;
      case ShaderDataType::Float3:
         return GL_FLOAT;
      case ShaderDataType::Float4:
         return GL_FLOAT;
      case ShaderDataType::Mat3:
         return GL_FLOAT;
      case ShaderDataType::Mat4:
         return GL_FLOAT;
      case ShaderDataType::Int:
         return GL_INT;
      case ShaderDataType::Int2:
         return GL_INT;
      case ShaderDataType::Int3:
         return GL_INT;
      case ShaderDataType::Int4:
         return GL_INT;
      case ShaderDataType::Bool:
         return GL_BOOL;
   }

   ASSERT_FAILED("Unknown openGl type");
   return 0;
}


OpenGLVertexArray::OpenGLVertexArray()
{
   glCreateVertexArrays(1, &handle);
}


OpenGLVertexArray::~OpenGLVertexArray()
{
   glDeleteVertexArrays(1, &handle);
}


void OpenGLVertexArray::Bind() const
{
   glBindVertexArray(handle);
}


void OpenGLVertexArray::Unbind() const
{
   glBindVertexArray(0);
}


void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
   ASSERT_MSG(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");

   glBindVertexArray(handle);
   vertexBuffer->Bind();

   uint32_t index = 0;
   const auto& layout = vertexBuffer->GetLayout();
   for (const auto& element : vertexBuffer->GetLayout()) {
      glEnableVertexAttribArray(index);
      glVertexAttribPointer(
         index,
         element.GetComponentCount(),
         ShaderDataTypeToOpenGLBaseType(element.type),
         element.normolized ? GL_TRUE : GL_FALSE,
         layout.GetStride(),
         (const void*)element.offset);
      ++index;
   }

   vertexBuffers.push_back(vertexBuffer);
}


void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
   glBindVertexArray(handle);
   indexBuffer->Bind();
   this->indexBuffer = indexBuffer;
}


const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers()
{
   return vertexBuffers;
}


const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer()
{
   return indexBuffer;
}