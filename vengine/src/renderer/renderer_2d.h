﻿#pragma once
#include "ve_camera.h"
#include "ve_texture.h"
#include "core/ve_memory.h"

namespace VE {
class Renderer2D {
public:
   static void Init();
   static void Shutdown();

   static void BeginScene(const Camera& camera);
   static void EndScene();

   static void DrawQuad(const Vector2& position, const Vector2& size, const Ref<Texture>& texture);
   static void DrawQuad(const Vector3& position, const Vector2& size, const Ref<Texture>& texture);
   static void DrawQuad(const Vector2& position, const Vector2& size, const Vector4& color);
   static void DrawQuad(const Vector3& position, const Vector2& size, const Vector4& color);
};

} //namespace VE
