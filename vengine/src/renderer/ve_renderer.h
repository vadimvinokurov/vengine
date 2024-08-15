#pragma once
#include "ve_camera.h"
#include "ve_renderer_api.h"
#include "ve_shader.h"

namespace VE {


class Renderer {
public:
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