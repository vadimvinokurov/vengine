#include "ve_pch.h"
#include "renderer_2d.h"

#include "ve_render_command.h"
#include "ve_renderer.h"
#include "ve_shader.h"
#include "ve_vertex_array.h"
#include "platform/opengl/opengl_shader.h"


namespace VE {
struct Renderer2DStorage {
   VE::Ref<VE::VertexArray> vertexArray;
   VE::Ref<VE::Shader> flatColorShader;
};


static Renderer2DStorage* renderer2DStorage;


void VE::Renderer2D::Init()
{
   renderer2DStorage = new Renderer2DStorage;
   renderer2DStorage->vertexArray = VertexArray::Create();

   float squareVertices[3 * 4] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f};

   VE::Ref<VertexBuffer> squareVertexBufer(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

   BufferLayout layout = {
      {ShaderDataType::Float3, "a_Position"}};

   squareVertexBufer->SetLayout(layout);
   renderer2DStorage->vertexArray->AddVertexBuffer(squareVertexBufer);

   unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
   VE::Ref<IndexBuffer> indexBuffer(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
   renderer2DStorage->vertexArray->SetIndexBuffer(indexBuffer);

   renderer2DStorage->flatColorShader = Shader::Create("./assets/shaders/flat_color.glsl");
}


void VE::Renderer2D::Shutdown()
{
   delete renderer2DStorage;
}


void VE::Renderer2D::BeginScene(const Camera& camera)
{
   std::dynamic_pointer_cast<OpenGLShader>(renderer2DStorage->flatColorShader)->Bind();
   std::dynamic_pointer_cast<OpenGLShader>(renderer2DStorage->flatColorShader)->UploadUniformMat4("viewProjection", camera.GetViewProjectionMatrix());
}


void VE::Renderer2D::EndScene()
{
}


void VE::Renderer2D::DrawQuad(const Vector2& position, const Vector2& size, const Vector4& color)
{
   DrawQuad({position.x, position.y, 0.0f}, size, color);
}


void VE::Renderer2D::DrawQuad(const Vector3& position, const Vector2& size, const Vector4& color)
{
   Transform transform(position);
   std::dynamic_pointer_cast<OpenGLShader>(renderer2DStorage->flatColorShader)->Bind();
   std::dynamic_pointer_cast<OpenGLShader>(renderer2DStorage->flatColorShader)->UploadUniformFloat4("u_Color", color);
   std::dynamic_pointer_cast<OpenGLShader>(renderer2DStorage->flatColorShader)->UploadUniformMat4("transform", transform.toMatrix());
   renderer2DStorage->vertexArray->Bind();
   RenderCommand::DrawIndexed(renderer2DStorage->vertexArray);
}
} //namespace VE