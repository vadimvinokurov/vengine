#pragma once

#include <vengine.h>
#include "ve_camera_controller.h"
#include "renderer/ve_texture.h"


class Sandbox2DLayer : public VE::Layer {
public:
   Sandbox2DLayer();

   virtual void OnAttach() override;
   virtual void OnDetach() override;

   virtual void OnUpdate(float dt) override;
   virtual void OnImGuiRender() override;
   virtual void OnEvent(VE::Event& event) override;

private:
   VE::Ref<VE::CameraController> cameraController;
   VE::Ref<VE::Texture2D> texture, textureLogo;
   VE::Vector4 squareColor{0.8f, 0.2f, 0.3f, 1.0f};
};