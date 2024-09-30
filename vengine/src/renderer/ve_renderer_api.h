#pragma once
#include "ve_vertex_array.h"
#include "math/ve_vector.h"

namespace VE {
class RendererAPI {
public:
   enum class API {
      None = 0,
      OpenGL = 1
   };

public:
   virtual ~RendererAPI() = default;
   virtual void Init() = 0;
   virtual void Clear() = 0;
   virtual void SetClearColor(const Vector4& color) = 0;
   virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
   virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

   inline static API GetApi() { return api; }

private:
   inline static API api = RendererAPI::API::OpenGL;
};

}