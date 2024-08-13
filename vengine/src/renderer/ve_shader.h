#pragma once
#include "math/ve_matrix4.h"

namespace VE {
class Shader {
public:
   Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
   ~Shader();

   void Bind() const;
   void Unbind() const;

   void UploadUniformMat4(const std::string& name, const Matrix4& matrix);

private:
   uint32_t redererId;
};
}