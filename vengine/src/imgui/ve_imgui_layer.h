#pragma once

#include "ve_layer.h"
#include "events/ve_application_event.h"
#include "events/ve_key_event.h"
#include "events/ve_mouse_event.h"

namespace VE {
class VE_API ImGuiLayer : public Layer {
public:
   ImGuiLayer();
   ~ImGuiLayer();
   virtual void OnUpdate() override;
   virtual void OnEvent(Event& event) override;
   virtual void OnAttach() override;
   virtual void OnDetach() override;

private:
   bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
   bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
   bool OnMouseMovedEvent(MouseMovedEvent& e);
   bool OnMouseScrolledEvent(MouseScrolledEvent& e);
   bool OnKeyPressedEvent(KeyPressedEvent& e);
   bool OnKeyReleasedEvent(KeyReleasedEvent& e);
   bool OnKeyTypedEvent(KeyTypedEvent& e);
   bool OnWindowResizeEvent(WindowResizeEvent& e);

   float time = 0.0f;
};
}