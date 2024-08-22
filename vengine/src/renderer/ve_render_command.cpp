#include "ve_pch.h"
#include "ve_render_command.h"
void VE::RenderCommand::Init()
{
   rendererApi->Init();
}


void VE::RenderCommand::Clear()
{
   rendererApi->Clear();
}


void VE::RenderCommand::SetClearColor(const Vector4& color)
{
   rendererApi->SetClearColor(color);
}


void VE::RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
   rendererApi->DrawIndexed(vertexArray);
}