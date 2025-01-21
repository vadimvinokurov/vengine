#include "sandbox_2d_layer.h"
#include "../../vengine/lib3dpart/imgui/imgui.h"
#include "math/ve_math_utility.h"
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

   texture = Texture2D::Create("./assets/textures/Checkerboard.png");
   textureLogo = Texture2D::Create("./assets/textures/ChernoLogo.png");
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
   VE::Renderer2D::DrawQuad(Vector3{0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, texture, 10.0f);
   VE::Renderer2D::DrawQuad(Vector2{0.0f, 0.0f}, {1.0f, 1.0f}, squareColor);
   VE::Renderer2D::DrawRotatedQuad(Vector2{-1.1f, 0.0f}, {0.5f, 0.5f}, VE_DEG2RAD(45), squareColor);
   VE::Renderer2D::DrawQuad(Vector2{1.0f, 0.0f}, {1.0f, 1.0f}, textureLogo);
   VE::Renderer2D::EndScene();
}


void Sandbox2DLayer::OnImGuiRender()
{
   ImGui::Begin("settings");
   ImGui::ColorEdit4("Square Color", squareColor.data());
   ImGui::End();


   static bool dockspaceOpen = true;
   static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

   // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
   // because it would be confusing to have two docking targets within each others.
   ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
   const ImGuiViewport* viewport = ImGui::GetMainViewport();
   ImGui::SetNextWindowPos(viewport->WorkPos);
   ImGui::SetNextWindowSize(viewport->WorkSize);
   ImGui::SetNextWindowViewport(viewport->ID);
   ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
   ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
   window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
   window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

   if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
      window_flags |= ImGuiWindowFlags_NoBackground;
   }

   ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
   ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
   ImGui::PopStyleVar(3);
   // Submit the DockSpace
   ImGuiIO& io = ImGui::GetIO();
   if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
      ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
   }

   if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
         if (ImGui::MenuItem("Close", NULL, false, dockspaceOpen != NULL)) {
            Application::Get()->Close();
         }
         ImGui::EndMenu();
      }

      ImGui::EndMenuBar();
   }

   ImGui::End();

   static bool demowindowOpen = true;
   ImGui::ShowDemoWindow(&demowindowOpen);
}


void Sandbox2DLayer::OnEvent(VE::Event& event)
{
   cameraController->OnEvent(event);
}