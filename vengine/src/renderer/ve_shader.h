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

   static Ref<Shader> Create(const std::string& file);
   static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);


private:
   uint32_t redererId;
};

}