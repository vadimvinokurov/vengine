#pragma once
#include "renderer/ve_framebuffer.h"

namespace VE {
class OpenGLFramebuffer : public Framebuffer {
public:
   OpenGLFramebuffer(const FramebufferSpecification& spec);
   virtual ~OpenGLFramebuffer();
   void Invalidate();
   virtual void Bind() override;
   virtual void Unbind() override;

   virtual uint32_t GetColorAttachmentHandle() const override { return colorAttachment; }
   virtual const FramebufferSpecification& GetFramebufferSpecification() const override { return specification; }

private:
   uint32_t handle;
   uint32_t colorAttachment, depthAttachment;
   FramebufferSpecification specification;
};
} //namespace VE
