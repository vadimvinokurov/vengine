#include "sandbox_2d_layer.h"
#include "../../vengine/lib3dpart/imgui/imgui.h"
#include "platform/opengl/opengl_shader.h"
#include "renderer/renderer_2d.h"

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
}


void Sandbox2DLayer::OnDetach()
{
}


void Sandbox2DLayer::OnUpdate(float dt)
{
   cameraController->OnUpdate(dt);

   VE::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
   VE::RenderCommand::Clear();

   VE::Renderer2D::BeginScene(cameraController->GetCamera());
   VE::Renderer2D::DrawQuad(Vector2{0.0f, 0.0f}, {1.0f, 1.0f}, {0.8f, 0.2f, 0.3f, 1.0f});
   VE::Renderer2D::DrawQuad(Vector2{1.0f, 0.0f}, {1.0f, 1.0f}, {0.2f, 0.2f, 0.3f, 1.0f});
   VE::Renderer2D::EndScene();
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