#include <vengine.h>

using namespace VE;


class ExampleLayer : public VE::Layer {
public:
   ExampleLayer()
      : Layer("Example")
   {
      auto [width, height] = VE::Application::Get()->GetWindow().GetSize();
      float windowAspectRatio = static_cast<float>(width) / static_cast<float>(height);
      camera.reset(new Camera(60.0f, windowAspectRatio, 0.1f, 8000));

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
         float vertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f};

         std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));

         BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"}};

         vertexBuffer->SetLayout(layout);
         squaVertexArray->AddVertexBuffer(vertexBuffer);

         uint32_t indices[6] = {0, 1, 2, 2, 3, 0};
         std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
         squaVertexArray->SetIndexBuffer(indexBuffer);
      }


      std::string vertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      layout(location = 1) in vec4 a_Color;

      uniform mat4 viewProjection;
      uniform mat4 transform;

      out vec4 v_Color;

      void main()
      {
         v_Color = a_Color;
         gl_Position = viewProjection * transform * vec4(a_Position, 1.0);
      }
   )";

      std::string fragmentSrc = R"(
      #version 330 core

      layout(location = 0) out vec4 color;
      in vec4 v_Color;

      void main()
      {
         color = v_Color;
      }
   )";

      shader.reset(new Shader(vertexSrc, fragmentSrc));

      std::string vertexSrc2 = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      uniform mat4 viewProjection;
      uniform mat4 transform;

      void main()
      {
         gl_Position = viewProjection * transform * vec4(a_Position, 1.0);
      }
   )";

      std::string fragmentSrc2 = R"(
      #version 330 core

      layout(location = 0) out vec4 color;

      void main()
      {
         color = vec4(0.2,0.3, 0.8, 1.0);
      }
   )";

      shader2.reset(new Shader(vertexSrc2, fragmentSrc2));
   }

   virtual void OnAttach() override {}
   virtual void OnDetach() override {}

   virtual void OnUpdate(float dt) override
   {
      if (Input::IsKeyPressed(VE_KEY_W)) {
         cameraPosition.y -= cameraSpeed * dt;
      } else if (Input::IsKeyPressed(VE_KEY_S)) {
         cameraPosition.y += cameraSpeed * dt;
      } else if (Input::IsKeyPressed(VE_KEY_A)) {
         cameraPosition.x += cameraSpeed * dt;
      } else if (Input::IsKeyPressed(VE_KEY_D)) {
         cameraPosition.x -= cameraSpeed * dt;
      }
      //camera->SetPosition(cameraPosition);


      Matrix4 trs;
      trs.GetOrigin() = cameraPosition;

      VE::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
      VE::RenderCommand::Clear();

      VE::Renderer::BeginScene(*camera);
      VE::Renderer::Submit(shader2, squaVertexArray, trs);
      VE::Renderer::Submit(shader, vertexArray, trs);
      VE::Renderer::EndScene();
   }

   virtual void OnImGuiRender() override {}

   virtual void OnEvent(VE::Event& event)
   {
      MAKE_EVENT_DISPATCHER(event);
      DISPATCH_EVENT(ExampleLayer, KeyPressedEvent);
   }

   bool OnKeyPressedEvent(VE::KeyPressedEvent& event)
   {
      return false;
   }

private:
   std::shared_ptr<VE::VertexArray> vertexArray;
   std::shared_ptr<VE::VertexArray> squaVertexArray;
   std::shared_ptr<VE::Shader> shader;
   std::shared_ptr<VE::Shader> shader2;

   std::shared_ptr<VE::Camera> camera;

   float cameraSpeed = 5.0f;
   Vector3 cameraPosition{};
};


class Sandbox : public VE::Application {
public:
   Sandbox()
   {
      PushLayer(new ExampleLayer());
   }
};


int main()
{
   auto sandbox = new Sandbox();
   sandbox->Run();

   delete sandbox;
   return 0;
}