#pragma once
#include "common/ve_assert.h"

namespace VE {

enum class ShaderDataType {
   None = 0,
   Float,
   Float2,
   Float3,
   Float4,
   Mat3,
   Mat4,
   Int,
   Int2,
   Int3,
   Int4,
   Bool
};


inline uint32_t ShaderDataTypeSize(ShaderDataType type)
{
   switch (type) {
      case ShaderDataType::Float:
         return 4;
      case ShaderDataType::Float2:
         return 4 * 2;
      case ShaderDataType::Float3:
         return 4 * 3;
      case ShaderDataType::Float4:
         return 4 * 4;
      case ShaderDataType::Mat3:
         return 4 * 3 * 3;
      case ShaderDataType::Mat4:
         return 4 * 4 * 4;
      case ShaderDataType::Int:
         return 4;
      case ShaderDataType::Int2:
         return 4 * 2;
      case ShaderDataType::Int3:
         return 4 * 3;
      case ShaderDataType::Int4:
         return 4 * 4;
      case ShaderDataType::Bool:
         return 1;
   }

   ASSERT_FAILED("Unknown ShaderDataType!");
   return 0;
}


struct BufferElement {
   std::string name;
   ShaderDataType type;
   uint32_t size;
   uint32_t offset;
   bool normolized;

   BufferElement(ShaderDataType type, const std::string& name, bool normolized = false)
      : name(name)
      , type(type)
      , size(ShaderDataTypeSize(type))
      , offset(0)
      , normolized(normolized)
   {
   }

   uint32_t GetComponentCount() const;
};


class BufferLayout {
public:
   BufferLayout() = default;
   BufferLayout(const BufferLayout&) = default;

   BufferLayout(const std::initializer_list<BufferElement>& elements)
      : elements(elements)
   {
      CalculateOffsetAndStride();
   }

   const std::vector<BufferElement>& GetElements() const
   {
      return elements;
   }

   uint32_t GetStride() const { return stride; }

   auto begin() { return elements.begin(); }
   auto end() { return elements.end(); }
   auto begin() const { return elements.begin(); }
   auto end() const { return elements.end(); }

private:
   void CalculateOffsetAndStride();

private:
   std::vector<BufferElement> elements;
   uint32_t stride = 0;
};


class VertexBuffer {
public:
   virtual ~VertexBuffer() = default;
   virtual void Bind() const = 0;
   virtual void Unbind() const = 0;
   virtual void SetLayout(const BufferLayout& layout) = 0;
   virtual const BufferLayout& GetLayout() const = 0;
   static VertexBuffer* Create(uint32_t size);
   static VertexBuffer* Create(const float* vertices, uint32_t size);
};


class IndexBuffer {
public:
   virtual ~IndexBuffer() = default;
   virtual void Bind() const = 0;
   virtual void Unbind() const = 0;
   virtual uint32_t GetCount() const = 0;
   static IndexBuffer* Create(const uint32_t* indices, uint32_t count);
};

} //namespace VE