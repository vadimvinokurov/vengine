#pragma once
#include <string>

#include "core/ve_memory.h"
#include "math/ve_matrix4.h"

namespace VE {
class Shader {
public:
   virtual ~Shader() = default;

   virtual void Bind() const = 0;
   virtual void Unbind() const = 0;

   virtual void SetInt(const std::string& name, int value) = 0;
   virtual void SetMat4(const std::string& name, const Matrix4& value) = 0;
   virtual void SetFloat3(const std::string& name, const Vector3& value) = 0;
   virtual void SetFloat4(const std::string& name, const Vector4& value) = 0;

   virtual const std::string& GetName() const = 0;

   static Ref<Shader> Create(const std::string& file);
   static Shader* Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);


private:
   uint32_t redererId;
};


class ShaderLibrary {
public:
   void Add(const std::string& name, const Ref<Shader>& shader);
   Ref<Shader> Load(const std::string& filepath);
   Ref<Shader> Load(const std::string& name, const std::string& filepath);

   Ref<Shader> Get(const std::string& name);
   bool Exists(const std::string& name) const;

private:
   std::unordered_map<std::string, Ref<Shader>> shaders;
};

} //namespace VE