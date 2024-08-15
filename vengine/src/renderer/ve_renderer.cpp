﻿#include "ve_pch.h"
#include "ve_renderer.h"

#include "ve_camera.h"
#include "ve_render_command.h"

using namespace VE;


void Renderer::BeginScene(Camera& camera)
{
   sceneData.viewProjectionMatrix = camera.GetViewProjectionMatrix();
}


void Renderer::EndScene()
{
}


void Renderer::Submit( const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4& transform)
{
   shader->Bind();
   shader->UploadUniformMat4("viewProjection", sceneData.viewProjectionMatrix);
   shader->UploadUniformMat4("transform", transform);
   vertexArray->Bind();
   RenderCommand::DrawIndexed(vertexArray);
}