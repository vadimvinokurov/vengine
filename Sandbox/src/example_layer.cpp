#include "example_layer.h"
#include "ve_camera_controller.h"
#include "../../vengine/lib3dpart/imgui/imgui.h"
#include "core/ve_memory.h"
#include "platform/opengl/opengl_shader.h"
#include "renderer/ve_texture.h"

using namespace VE;


ExampleLayer::ExampleLayer()
   : Layer("Example")
{
   auto [width, height] = VE::Application::Get()->GetWindow().GetSize();
   float windowAspectRatio = static_cast<float>(width) / static_cast<float>(height);
   cameraController.reset(new CameraController(windowAspectRatio));

   vertexArray.reset(VertexArray::Create());
   {
      float vertices[3 * 7] = {
         -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
         0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

      std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));


      BufferLayout layout = {
         {ShaderDataType::Float3, "a_Position"},
         {ShaderDataType::Float4, "a_Color"}};

      vertexBuffer->SetLayout(layout);
      vertexArray->AddVertexBuffer(vertexBuffer);

      unsigned int indices[3] = {0, 1, 2};
      std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, 3));
      vertexArray->SetIndexBuffer(indexBuffer);
   }

   squaVertexArray.reset(VertexArray::Create());
   {
      float vertices[5 * 4] = {
         -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

      std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));

      BufferLayout layout = {
         {ShaderDataType::Float3, "a_Position"},
         {ShaderDataType::Float2, "a_TexCoord"}};

      vertexBuffer->SetLayout(layout);
      squaVertexArray->AddVertexBuffer(vertexBuffer);

      uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
      std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
      squaVertexArray->SetIndexBuffer(indexBuffer);
   }

   auto textureShader = shaderLibrary.Load("./assets/shaders/Texture.glsl");

   texture = Texture2D::Create("./assets/textures/Checkerboard.png");
   textureLogo = Texture2D::Create("./assets/textures/ChernoLogo.png");

   std::dynamic_pointer_cast<OpenGLShader>(textureShader)->Bind();
   std::dynamic_pointer_cast<OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
}


void ExampleLayer::OnUpdate(float dt)
{
   cameraController->OnUpdate(dt);

   Matrix4 trs1;

   VE::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
   VE::RenderCommand::Clear();

   VE::Renderer::BeginScene(cameraController->GetCamera());

   Vector4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
   Vector4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);

   // Material* material = new Material();
   // MaterialInststance* materialInstance = new MaterialInststance();
   // material->Set("uColor", redColor);
   // squareMesh->SetMaterial(material);

   auto textureShader = shaderLibrary.Get("Texture");

   std::dynamic_pointer_cast<OpenGLShader>(textureShader)->Bind();
   std::dynamic_pointer_cast<OpenGLShader>(textureShader)->UploadUniformFloat3("uColor", squareColor);

   Transform trs(Vector3(0.6f, 0, 0));
   texture->Bind();
   VE::Renderer::Submit(textureShader, squaVertexArray, trs.toMatrix());
   textureLogo->Bind();
   VE::Renderer::Submit(textureShader, squaVertexArray, trs.toMatrix());
   VE::Renderer::EndScene();
}


void ExampleLayer::OnImGuiRender()
{
   ImGui::Begin("settings");
   ImGui::ColorEdit3("Square Colot", squareColor.data());
   ImGui::End();
}


void ExampleLayer::OnEvent(VE::Event& event)
{
   cameraController->OnEvent(event);
}