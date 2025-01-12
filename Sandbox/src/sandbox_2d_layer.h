#pragma once

#include <vengine.h>
#include "ve_camera_controller.h"


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

   VE::Ref<VE::Shader> flatColorShader;
   VE::Ref<VE::VertexArray> squareVertexArray;

   VE::Vector4 squareColor{0.8f, 0.2f, 0.3f, 1.0f};
};