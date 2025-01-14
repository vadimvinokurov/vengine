#pragma once
#include "glad/glad.h"
#include "renderer/ve_texture.h"

namespace VE {

class OpenGLTexture2D : public Texture2D {
public:
   OpenGLTexture2D(uint32_t width, uint32_t height);
   OpenGLTexture2D(const std::string& path);
   ~OpenGLTexture2D();
   virtual void SetData(void* data, uint32_t size) override;
   virtual uint32_t GetWidth() const override;
   virtual uint32_t GetHeight() const override;
   virtual void Bind(uint32_t slot = 0) const override;

private:
   std::string path;
   uint32_t width;
   uint32_t height;
   uint32_t handle;

   GLenum internalFormat = 0;
   GLenum dataFormat = 0;
};

} //namespace VE