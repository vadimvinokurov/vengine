#include "ve_pch.h"
#include "ve_opengl_texture.h"


#include "stb_image.h"
#include "common/ve_assert.h"
#include "glad/glad.h"
using namespace VE;


OpenGLTexture2D::OpenGLTexture2D(const std::string& path_)
   : path(path_)
{
   int width_, height_, channels_;
   stbi_set_flip_vertically_on_load(1);
   stbi_uc* data = stbi_load(path_.c_str(), &width_, &height_, &channels_, 0);
   ASSERT_MSG(data, "Failed to load images");

   width = width_;
   height = height_;

   GLenum internalFormat = 0, dataFormat = 0;
   if (channels_ == 4) {
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
   } else if (channels_ == 3) {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
   }

   ASSERT_MSG(internalFormat != 0 && dataFormat != 0, "Format not supported!");

   glCreateTextures(GL_TEXTURE_2D, 1, &handle);
   glTextureStorage2D(handle, 1, internalFormat, width, height);

   glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   glTextureSubImage2D(handle, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

   stbi_image_free(data);
}


OpenGLTexture2D::~OpenGLTexture2D()
{
   glDeleteTextures(1, &handle);
}


uint32_t VE::OpenGLTexture2D::GetWidth() const
{
   return width;
}


uint32_t VE::OpenGLTexture2D::GetHeight() const
{
   return height;
}


void VE::OpenGLTexture2D::Bind(uint32_t slot) const
{
   glBindTextureUnit(slot, handle);
}