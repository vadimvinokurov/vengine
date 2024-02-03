#include "ve_pch.h"
#include "ve_imgui_layer.h"

#include "ve_application.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

VE::ImGuiLayer::ImGuiLayer()
   : Layer("ImGuiLayer")
{
}


VE::ImGuiLayer::~ImGuiLayer()
{
}


void VE::ImGuiLayer::OnAttach()
{
   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO();
   (void)io;
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
   io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
   //io.ConfigViewportsNoAutoMerge = true;
   //io.ConfigViewportsNoTaskBarIcon = true;

   // Setup Dear ImGui style
   ImGui::StyleColorsDark();

   ImGuiStyle& style = ImGui::GetStyle();
   if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      style.WindowRounding = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
   }

   // Setup Platform/Renderer backends
   ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)(Application::Get()->GetWindow().GetNativeWindow()), true);
   ImGui_ImplOpenGL3_Init("#version 410");
}


void VE::ImGuiLayer::OnDetach()
{
   // Cleanup
   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();
}


void VE::ImGuiLayer::Begin()
{

   ImGuiIO& io = ImGui::GetIO();
   auto [width, height] = Application::Get()->GetWindow().GetSize();
   io.DisplaySize = ImVec2(width, height);

   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();
}


void VE::ImGuiLayer::End()
{
   ImGui::Render();
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

   ImGuiIO& io = ImGui::GetIO();

   if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      GLFWwindow* backup_current_context = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backup_current_context);
   }
}


void VE::ImGuiLayer::OnImGuiRender()
{
   static bool show = true;
   ImGui::ShowDemoWindow(&show);
}