#pragma once
#include "ve_renderer_api.h"
#include "platform/opengl/ve_opengl_renderer.h"

namespace VE {
class RenderCommand {
public:
   static void Init();
   static void Clear();
   static void SetClearColor(const Vector4& color);
   static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
   static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
private:
   inline static RendererAPI* rendererApi = new OpenGLRendererAPI();
};

} //namespace VE