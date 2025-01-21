#pragma once
#include "core/ve_memory.h"

namespace VE {
struct FramebufferSpecification {
   uint32_t width, height;
};


class Framebuffer {
public:
   virtual ~Framebuffer() = default;
   virtual void Bind() = 0;
   virtual void Unbind() = 0;

   virtual uint32_t GetColorAttachmentHandle() const = 0;
   virtual const FramebufferSpecification& GetFramebufferSpecification() const = 0;

   static VE::Ref<Framebuffer> Create(const FramebufferSpecification& spec);
};

} //namespace VE
