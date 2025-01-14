#include "ve_pch.h"
#include "ve_renderer.h"

#include "renderer_2d.h"
#include "ve_camera.h"
#include "ve_render_command.h"
#include "platform/opengl/opengl_shader.h"

using namespace VE;


void Renderer::Init()
{
   RenderCommand::Init();
   Renderer2D::Init();
}


void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
   RenderCommand::SetViewport(0, 0, width, height);
}


void Renderer::BeginScene(Camera& camera)
{
   sceneData.viewProjectionMatrix = camera.GetViewProjectionMatrix();
}


void Renderer::EndScene()
{
}


void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4& transform)
{
   shader->Bind();
   std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", sceneData.viewProjectionMatrix);
   std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
   vertexArray->Bind();
   RenderCommand::DrawIndexed(vertexArray);
}