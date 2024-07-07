#pragma once
#include "renderer/ve_buffer.h"

namespace VE {
class OpenGLVertexBuffer final : public VertexBuffer {
public:
   OpenGLVertexBuffer(const float* vertices, uint32_t size);
   virtual ~OpenGLVertexBuffer() override;
   virtual void Bind() const override;
   virtual void Unbind() const override;

private:
   uint32_t handle{};
};


class OpenGLIndexBuffer final : public IndexBuffer {
public:
   OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
   virtual ~OpenGLIndexBuffer() override;
   virtual void Bind() const override;
   virtual void Unbind() const override;
   virtual uint32_t GetCount() const override;

private:
   uint32_t handle{};
   uint32_t count{};
};

} //namespace VE