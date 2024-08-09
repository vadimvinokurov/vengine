#pragma once
#include "renderer/ve_vertex_array.h"

namespace VE {
class OpenGLVertexArray final : public VertexArray {
public:
   OpenGLVertexArray();
   virtual ~OpenGLVertexArray() override;
   virtual void Bind() const override;
   virtual void Unbind() const override;
   virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
   virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

   virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() override;
   virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() override;

private:
   std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
   std::shared_ptr<IndexBuffer> indexBuffer;

   uint32_t handle{};
};
} //namespace VE