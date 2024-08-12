#include "ve_pch.h"
#include "ve_opengl_renderer.h"

#include <glad/glad.h>

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