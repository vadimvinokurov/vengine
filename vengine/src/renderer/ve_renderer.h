#pragma once
#include "ve_camera.h"
#include "ve_renderer_api.h"
#include "ve_shader.h"

namespace VE {


class Renderer {
public:
   static void Init();
   static void OnWindowResize(uint32_t width, uint32_t height);
   static void BeginScene(Camera& camera);
   static void EndScene();
   static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const Matrix4& transform);
   inline static RendererAPI::API GetAPI() { return RendererAPI::GetApi(); }

private:
   struct SceneData {
      Matrix4 viewProjectionMatrix;
   };

   static inline SceneData sceneData;
};

}