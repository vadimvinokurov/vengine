#pragma once
#include "ve_camera.h"

namespace VE {
class Renderer2D {
public:
   static void Init();
   static void Shutdown();

   static void BeginScene(const Camera& camera);
   static void EndScene();

   static void DrawQuad(const Vector2& position, const Vector2& size, const Vector4& color);
   static void DrawQuad(const Vector3& position, const Vector2& size, const Vector4& color);
};

} //namespace VE
