#include "ve_pch.h"
#include "ve_opengl_renderer.h"

#include <glad/glad.h>

void VE::OpenGLRendererAPI::Init()
{
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void VE::OpenGLRendererAPI::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void VE::OpenGLRendererAPI::SetClearColor(const Vector4& color)
{
   glClearColor(color.red, color.green, color.green, color.alfa);
}


void VE::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
   glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}


void VE::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
   glViewport(x, y, width, height);
}