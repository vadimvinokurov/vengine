#pragma once
#include "math/ve_matrix3.h"
#include "math/ve_matrix4.h"
#include "renderer/ve_shader.h"

namespace VE {
class OpenGLShader : public Shader {
public:
   OpenGLShader(const std::string& filepath);
   OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
   ~OpenGLShader();

   virtual const std::string& GetName() const override;
   virtual void Bind() const override;
   virtual void Unbind() const override;

   virtual void SetInt(const std::string& name, int value) override;
   virtual void SetMat4(const std::string& name, const Matrix4& value) override;
   virtual void SetFloat3(const std::string& name, const Vector3& value) override;
   virtual void SetFloat4(const std::string& name, const Vector4& value) override;

   void UploadUniformMat3(const std::string& name, const Matrix3& matrix);
   void UploadUniformMat4(const std::string& name, const Matrix4& matrix);
   void UploadUniformInt(const std::string& name, int v);
   void UploadUniformFloat(const std::string& name, float v);
   void UploadUniformFloat2(const std::string& name, const Vector2& vec2);
   void UploadUniformFloat3(const std::string& name, const Vector3& vec3);
   void UploadUniformFloat4(const std::string& name, const Vector4& vec4);

private:
   std::string ReadFile(const std::string& filepath) const;
   std::unordered_map<unsigned int, std::string> PreProcess(const std::string& source) const;
   void Compile(const std::unordered_map<unsigned int, std::string>& shaderSources);

private:
   uint32_t redererId;
   std::string name;
};
} //namespace VE