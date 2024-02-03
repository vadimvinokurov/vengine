﻿#include "ve_pch.h"
#include "ve_imgui_layer.h"

#include "ve_application.h"
#include "GLFW/glfw3.h"
#include "platform/opengl/imgui_impl_opengl3.h"

VE::ImGuiLayer::ImGuiLayer()
   : Layer("ImGuiLayer")
{
}


VE::ImGuiLayer::~ImGuiLayer()
{
}


void VE::ImGuiLayer::OnAttach()
{
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGui::StyleColorsDark();

   ImGuiIO& io = ImGui::GetIO();
   io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
   io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

   // TEMPORARY: should eventually use Hazel key codes
   io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
   io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
   io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
   io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
   io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
   io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
   io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
   io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
   io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
   io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
   io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
   io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
   io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
   io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
   io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
   io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
   io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
   io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
   io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
   io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
   io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

   ImGui_ImplOpenGL3_Init("#version 410");
}


void VE::ImGuiLayer::OnDetach()
{
   ImGui_ImplOpenGL3_Shutdown();
   ImGui::DestroyContext();
}


bool VE::ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
   ImGuiIO& io = ImGui::GetIO();
   io.MouseDown[e.GetButton()] = true;
   return false;
}


bool VE::ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
   ImGuiIO& io = ImGui::GetIO();
   io.MouseDown[e.GetButton()] = false;
   return false;
}


bool VE::ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
{
   ImGuiIO& io = ImGui::GetIO();
   io.MousePos = ImVec2(e.GetX(), e.GetY());
   return false;
}


bool VE::ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
   ImGuiIO& io = ImGui::GetIO();
   io.MouseWheel += e.GetYOffset();
   io.MouseWheelH += e.GetXOffset();
   return false;
}


bool VE::ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
{
   ImGuiIO& io = ImGui::GetIO();
   io.KeysDown[e.GetKeyCode()] = true;
   io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
   io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
   io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
   io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
   return false;
}


bool VE::ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
{
   ImGuiIO& io = ImGui::GetIO();
   io.KeysDown[e.GetKeyCode()] = false;
   return false;
}


bool VE::ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
{
   ImGuiIO& io = ImGui::GetIO();
   io.AddInputCharacter(e.GetKeyCode());
   return false;
}


bool VE::ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
{
   ImGuiIO& io = ImGui::GetIO();
   io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
   io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

   return false;
}


void VE::ImGuiLayer::OnUpdate()
{
   ImGuiIO& io = ImGui::GetIO();
   auto [width, height] = Application::Get()->GetWindow().GetSize();
   io.DisplaySize = ImVec2(width, height);
   float currentTime = (float)glfwGetTime();
   io.DeltaTime = time > 0.0f ? (currentTime - time) : (1.0f / 60.0f);
   time = currentTime;

   ImGui_ImplOpenGL3_NewFrame();
   ImGui::NewFrame();

   static bool show = true;

   ImGui::ShowDemoWindow(&show);

   ImGui::Render();
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void VE::ImGuiLayer::OnEvent(Event& event)
{
   MAKE_EVENT_DISPATCHER(event);
   DISPATCH_EVENT(ImGuiLayer, MouseButtonPressedEvent);
   DISPATCH_EVENT(ImGuiLayer, MouseButtonReleasedEvent);
   DISPATCH_EVENT(ImGuiLayer, MouseMovedEvent);
   DISPATCH_EVENT(ImGuiLayer, MouseScrolledEvent);
   DISPATCH_EVENT(ImGuiLayer, KeyPressedEvent);
   DISPATCH_EVENT(ImGuiLayer, KeyReleasedEvent);
   DISPATCH_EVENT(ImGuiLayer, KeyTypedEvent);
   DISPATCH_EVENT(ImGuiLayer, WindowResizeEvent);
}