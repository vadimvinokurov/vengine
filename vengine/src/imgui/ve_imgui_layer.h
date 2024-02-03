#pragma once

#include "ve_layer.h"
#include "events/ve_application_event.h"
#include "events/ve_key_event.h"
#include "events/ve_mouse_event.h"

namespace VE {
class VE_API ImGuiLayer : public Layer {
public:
   ImGuiLayer();
   virtual ~ImGuiLayer();

   virtual void OnImGuiRender() override;
   virtual void OnAttach() override;
   virtual void OnDetach() override;
   

   void Begin();
   void End();

   float time = 0.0f;
};
}