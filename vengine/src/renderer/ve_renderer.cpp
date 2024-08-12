#include "ve_pch.h"
#include "ve_renderer.h"
#include "ve_render_command.h"

using namespace VE;


void Renderer::BeginScene()
{
}


void Renderer::EndScene()
{
}


void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
{
   vertexArray->Bind();
   RenderCommand::DrawIndexed(vertexArray);
}