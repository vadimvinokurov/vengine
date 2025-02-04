﻿#include "ve_pch.h"
#include "ve_opengl_texture.h"


#include "stb_image.h"
#include "common/ve_assert.h"
#include "glad/glad.h"
using namespace VE;


OpenGLTexture2D::OpenGLTexture2D(uint32_t width_, uint32_t height_)
{
   width = width_;
   height = height_;
   
   internalFormat = GL_RGBA8;
   dataFormat = GL_RGBA;

   glCreateTextures(GL_TEXTURE_2D, 1, &handle);
   glTextureStorage2D(handle, 1, internalFormat, width, height);

   glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


OpenGLTexture2D::OpenGLTexture2D(const std::string& path_)
   : path(path_)
{
   int width_, height_, channels_;
   stbi_set_flip_vertically_on_load(1);
   stbi_uc* data = stbi_load(path_.c_str(), &width_, &height_, &channels_, 0);
   ASSERT_MSG(data, "Failed to load images");

   width = width_;
   height = height_;

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

   glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

   glTextureSubImage2D(handle, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

   stbi_image_free(data);
}


OpenGLTexture2D::~OpenGLTexture2D()
{
   glDeleteTextures(1, &handle);
}


void OpenGLTexture2D::SetData(void* data, uint32_t size)
{
   uint32_t bpc = dataFormat == GL_RGBA ? 4 : 3;
   ASSERT_MSG(internalFormat != 0 && dataFormat != 0, "Format not supported!");
   ASSERT_MSG(size == width * height * bpc, "Data must be entire texture");
   glTextureSubImage2D(handle, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
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