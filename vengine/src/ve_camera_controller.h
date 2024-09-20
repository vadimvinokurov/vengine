#pragma once
#include "renderer/ve_camera.h"

#include "events/ve_mouse_event.h"
#include "events/ve_application_event.h"
namespace VE {

class CameraController {
public:
   CameraController(float aspectRatio, bool rotation = false);

   Camera& GetCamera();

   void OnUpdate(float dt);
   void OnEvent(Event& event);

private:
   bool OnMouseScrolledEvent(MouseScrolledEvent& e);
   bool OnWindowResizeEvent(WindowResizeEvent& e);

private:
   float aspectRatio;
   float zoomLevel = 1.0f;
   Camera camera;


   float cameraSpeed = 5.0f;
   Vector3 cameraPosition{};
};
}