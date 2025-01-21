#include "ve_pch.h"
#include "ve_camera_controller.h"


#include "ve_input.h"
#include "ve_key_codes.h"

using namespace VE;


CameraController::CameraController(float aspectRatio, bool rotation)
   : aspectRatio(aspectRatio)
   , camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel, OrthogonalCamera)
{
}


Camera& CameraController::GetCamera()
{
   return camera;
}


void CameraController::OnUpdate(float dt)
{
   if (Input::IsKeyPressed(VE_KEY_W)) {
      cameraPosition.y += cameraSpeed * dt;
   }
   if (Input::IsKeyPressed(VE_KEY_S)) {
      cameraPosition.y -= cameraSpeed * dt;
   }
   if (Input::IsKeyPressed(VE_KEY_A)) {
      cameraPosition.x -= cameraSpeed * dt;
   }
   if (Input::IsKeyPressed(VE_KEY_D)) {
      cameraPosition.x += cameraSpeed * dt;
   }

   camera.SetPosition(cameraPosition);
}


void CameraController::OnEvent(Event& event)
{
   MAKE_EVENT_DISPATCHER(event);
   DISPATCH_EVENT(CameraController, MouseScrolledEvent);
   DISPATCH_EVENT(CameraController, WindowResizeEvent);
}


bool CameraController::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
   zoomLevel -= e.GetYOffset() * 0.25f;
   zoomLevel = max(zoomLevel, 0.25f);
   camera.SetOrthogonal(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
   return false;
}


bool CameraController::OnWindowResizeEvent(WindowResizeEvent& e)
{
   aspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
   camera.SetOrthogonal(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
   return false;
}