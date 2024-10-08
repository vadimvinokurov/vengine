﻿#pragma once

#include "ve_window.h"
#include "renderer/ve_graphics_context.h"

struct GLFWwindow;


namespace VE {
class WindowsWindow : public Window {
public:
   WindowsWindow(const WindowsProps& props);
   ~WindowsWindow() override;
   virtual void OnUpdate() override;
   virtual std::pair<unsigned int, unsigned int> GetSize() const override;
   virtual void SetEventCallback(const EventCallback& cb) override;
   virtual void SetVSync(bool enabled) override;
   virtual bool IsVSync() const override;
   virtual void* GetNativeWindow() override { return pWindow; };

private:
   virtual void Init(const WindowsProps& props);
   virtual void Shutdown();

private:
   GLFWwindow* pWindow = nullptr;
   std::unique_ptr<GraphicsContext> context;
   std::string title;
   unsigned int width;
   unsigned int height;
   bool vsync = false;
   EventCallback eventCallback{};

   inline static bool GLFWInitilized = false;
};
}