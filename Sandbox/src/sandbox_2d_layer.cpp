#include "sandbox_2d_layer.h"
#include "../../vengine/lib3dpart/imgui/imgui.h"
#include "platform/opengl/opengl_shader.h"

using namespace VE;


Sandbox2DLayer::Sandbox2DLayer()
   : Layer("Sandbox2D")
{
}


void Sandbox2DLayer::OnAttach()
{
   auto [width, height] = VE::Application::Get()->GetWindow().GetSize();
   float windowAspectRatio = static_cast<float>(width) / static_cast<float>(height);
   cameraController.reset(new CameraController(windowAspectRatio));


   squareVertexArray = VertexArray::Create();

   float squareVertices[3 * 4] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f};

   VE::Ref<VertexBuffer> squareVertexBufer(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

   BufferLayout layout = {
      {ShaderDataType::Float3, "a_Position"}};

   squareVertexBufer->SetLayout(layout);
   squareVertexArray->AddVertexBuffer(squareVertexBufer);

   unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
   VE::Ref<IndexBuffer> indexBuffer(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
   squareVertexArray->SetIndexBuffer(indexBuffer);

   flatColorShader = Shader::Create("./assets/shaders/flat_color.glsl");
}


void Sandbox2DLayer::OnDetach()
{
}


void Sandbox2DLayer::OnUpdate(float dt)
{
   cameraController->OnUpdate(dt);

   VE::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
   VE::RenderCommand::Clear();

   VE::Renderer::BeginScene(cameraController->GetCamera());

   std::dynamic_pointer_cast<OpenGLShader>(flatColorShader)->Bind();
   std::dynamic_pointer_cast<OpenGLShader>(flatColorShader)->UploadUniformFloat4("u_Color", squareColor);

   Transform trs(Vector3(0.6f, 0, 0));
   flatColorShader->Bind();
   VE::Renderer::Submit(flatColorShader, squareVertexArray, trs.toMatrix());
   VE::Renderer::EndScene();
   VE_LOG_MSG("Sandbox2DLayer::OnUpdate {}", squareColor);
}


void Sandbox2DLayer::OnImGuiRender()
{
   ImGui::Begin("settings");
   ImGui::ColorEdit4("Square Color", squareColor.data());
   ImGui::End();
}


void Sandbox2DLayer::OnEvent(VE::Event& event)
{
   // cameraController->OnEvent(event);
}