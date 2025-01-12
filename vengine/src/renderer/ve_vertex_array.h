﻿#pragma once
#include "ve_buffer.h"
#include "core/ve_memory.h"

namespace VE {
class VertexArray {
public:
   virtual ~VertexArray() = default;
   virtual void Bind() const = 0;
   virtual void Unbind() const = 0;
   virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
   virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

   virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() = 0;
   virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() = 0;
   static Ref<VertexArray> Create();
};
} //namespace VE