#include "ve_pch.h"
#include "renderer_2d.h"

#include "ve_render_command.h"
#include "ve_renderer.h"
#include "ve_shader.h"
#include "ve_vertex_array.h"


namespace VE {
struct Renderer2DStorage {
   VE::Ref<VE::VertexArray> vertexArray;
   VE::Ref<VE::Shader> textureShader;
   VE::Ref<VE::Texture2D> whiteTexture;
};


static Renderer2DStorage* renderer2DStorage;


void VE::Renderer2D::Init()
{
   renderer2DStorage = new Renderer2DStorage;
   renderer2DStorage->vertexArray = VertexArray::Create();

   float squareVertices[5 * 4] = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
      -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

   VE::Ref<VertexBuffer> squareVertexBufer(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

   BufferLayout layout = {
      {ShaderDataType::Float3, "a_Position"},
      {ShaderDataType::Float2, "a_TexCoord"}};

   squareVertexBufer->SetLayout(layout);
   renderer2DStorage->vertexArray->AddVertexBuffer(squareVertexBufer);

   unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
   VE::Ref<IndexBuffer> indexBuffer(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
   renderer2DStorage->vertexArray->SetIndexBuffer(indexBuffer);

   renderer2DStorage->textureShader = Shader::Create("./assets/shaders/texture.glsl");
   renderer2DStorage->whiteTexture = Texture2D::Create(1, 1);
   uint32_t whiteTextureData = 0xffffffff;
   renderer2DStorage->whiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
}


void VE::Renderer2D::Shutdown()
{
   delete renderer2DStorage;
}


void VE::Renderer2D::BeginScene(const Camera& camera)
{
   renderer2DStorage->textureShader->Bind();
   renderer2DStorage->textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
   renderer2DStorage->textureShader->SetInt("u_Texture", 0);
}


void VE::Renderer2D::EndScene()
{
}


void Renderer2D::DrawQuad(const Vector2& position, const Vector2& size, const Ref<Texture>& texture)
{
   DrawQuad({position.x, position.y, 0.0f}, size, texture);
}


void Renderer2D::DrawQuad(const Vector3& position, const Vector2& size, const Ref<Texture>& texture)
{
   Transform transform(position, {}, Vector3(size.x, size.y, 1.0f));
   renderer2DStorage->textureShader->SetMat4("u_Transform", transform.toMatrix());
   renderer2DStorage->textureShader->SetFloat4("u_Color", Vector4{1.0f, 1.0f, 1.0f, 1.0f});
   texture->Bind();
   renderer2DStorage->vertexArray->Bind();
   RenderCommand::DrawIndexed(renderer2DStorage->vertexArray);
}


void VE::Renderer2D::DrawQuad(const Vector2& position, const Vector2& size, const Vector4& color)
{
   DrawQuad({position.x, position.y, 0.0f}, size, color);
}


void VE::Renderer2D::DrawQuad(const Vector3& position, const Vector2& size, const Vector4& color)
{
   Transform transform(position, {}, Vector3(size.x, size.y, 1.0f));
   renderer2DStorage->textureShader->SetMat4("u_Transform", transform.toMatrix());

   renderer2DStorage->textureShader->SetFloat4("u_Color", color);
   renderer2DStorage->whiteTexture->Bind();

   renderer2DStorage->vertexArray->Bind();
   RenderCommand::DrawIndexed(renderer2DStorage->vertexArray);
}
} //namespace VE