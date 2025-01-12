#pragma once
#include <vengine.h>

#include "ve_camera_controller.h"
#include "renderer/ve_texture.h"


class ExampleLayer : public VE::Layer {
public:
   ExampleLayer();

   virtual void OnAttach() override {}
   virtual void OnDetach() override {}

   virtual void OnUpdate(float dt) override;
   virtual void OnImGuiRender() override;
   virtual void OnEvent(VE::Event& event) override;

private:
   VE::ShaderLibrary shaderLibrary;
   VE::Ref<VE::Texture2D> texture, textureLogo;
   VE::Ref<VE::VertexArray> vertexArray;
   VE::Ref<VE::VertexArray> squaVertexArray;
   VE::Vector3 squareColor{0.8f, 0.2f, 0.3f};
   VE::Ref<VE::CameraController> cameraController;
};