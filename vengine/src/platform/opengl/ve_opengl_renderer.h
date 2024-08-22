#pragma once
#include "renderer/ve_renderer_api.h"


namespace VE {
class OpenGLRendererAPI : public RendererAPI {
public:
   virtual void Init() override;
   virtual void Clear() override;
   virtual void SetClearColor(const Vector4& color) override;
   virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
};
}