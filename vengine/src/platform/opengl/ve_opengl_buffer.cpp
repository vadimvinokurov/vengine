#include "ve_pch.h"
#include "ve_opengl_buffer.h"


#include "glad/glad.h"


using namespace VE;


OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, uint32_t size)
{
   glCreateBuffers(1, &handle);
   Bind();
   glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}


OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
   glDeleteBuffers(1, &handle);
}


void OpenGLVertexBuffer::Bind() const
{
   glBindBuffer(GL_ARRAY_BUFFER, handle);
}


void OpenGLVertexBuffer::Unbind() const
{
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}


OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t count)
   : count(count)
{
   glCreateBuffers(1, &handle);
   Bind();
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}


OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
   glDeleteBuffers(1, &handle);
}


void OpenGLIndexBuffer::Bind() const
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
}


void OpenGLIndexBuffer::Unbind() const
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


uint32_t OpenGLIndexBuffer::GetCount() const
{
   return count;
}