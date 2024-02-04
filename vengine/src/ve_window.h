#pragma once

#include "common/ve_common.h"
#include "events/ve_event.h"

namespace VE {

struct WindowsProps {
   std::string title = "VEngine";
   unsigned int width = 1280;
   unsigned int height = 720;
};


class Window {
public:
   virtual ~Window() = default;
   virtual void OnUpdate() = 0;
   virtual std::pair<unsigned int, unsigned int> GetSize() const = 0;
   virtual void SetEventCallback(const EventCallback& cb) = 0;
   virtual void SetVSync(bool enabled) = 0;
   virtual bool IsVSync() const = 0;
   virtual void* GetNativeWindow() = 0;

   static std::unique_ptr<Window> Create(const WindowsProps& props = {});
};

}