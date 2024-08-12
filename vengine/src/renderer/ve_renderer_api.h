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
   virtual ~RendererAPI(){};
   virtual void Clear() = 0;
   virtual void SetClearColor(const Vector4& color) = 0;
   virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

   inline static API GetApi() { return api; }

private:
   inline static API api = RendererAPI::API::OpenGL;
};

}