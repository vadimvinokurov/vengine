#pragma once
#include "ve_renderer_api.h"

namespace VE {


class Renderer {
public:
   static void BeginScene();
   static void EndScene();
   static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
   inline static RendererAPI::API GetAPI() { return RendererAPI::GetApi(); }
};

}