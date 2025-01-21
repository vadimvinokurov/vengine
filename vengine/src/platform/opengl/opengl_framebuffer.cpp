#include "ve_pch.h"
#include "opengl_framebuffer.h"

#include "common/ve_assert.h"
#include "glad/glad.h"

namespace VE {

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
   : specification(spec)
{
   Invalidate();
}


OpenGLFramebuffer::~OpenGLFramebuffer()
{
   glDeleteFramebuffers(1, &handle);
}


void OpenGLFramebuffer::Invalidate()
{
   glCreateFramebuffers(1, &handle);
   glBindFramebuffer(GL_FRAMEBUFFER, handle);

   glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment);
   glBindTexture(GL_TEXTURE_2D, colorAttachment);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, specification.width, specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

   glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment);
   glBindTexture(GL_TEXTURE_2D, depthAttachment);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, specification.width, specification.height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0);

   ASSERT_MSG(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");

   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void OpenGLFramebuffer::Bind()
{
   glBindFramebuffer(GL_FRAMEBUFFER, handle);
}


void OpenGLFramebuffer::Unbind()
{
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
} //namespace VE
