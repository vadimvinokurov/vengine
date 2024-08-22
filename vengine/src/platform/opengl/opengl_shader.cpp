#include "ve_pch.h"
#include "opengl_shader.h"
#include <glad/glad.h>
#include <fstream>


#include "common/ve_assert.h"
#include "common/ve_log.h"

namespace VE {
static GLenum ShaderTypeFromString(const std::string& type)
{
   if (type == "vertex") {
      return GL_VERTEX_SHADER;
   }

   if (type == "fragment" || type == "pixel") {
      return GL_FRAGMENT_SHADER;
   }

   ASSERT_FAILED("Unknown shader type!");

   return 0;
}
} //namespace VE


VE::OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
{
   std::unordered_map<GLenum, std::string> sources;
   sources[GL_VERTEX_SHADER] = vertexSource;
   sources[GL_FRAGMENT_SHADER] = fragmentSource;
   Compile(sources);
}


VE::OpenGLShader::OpenGLShader(const std::string& filepath)
{
   std::string sources = ReadFile(filepath);
   auto shaderSources = PreProcess(sources);
   Compile(shaderSources);
}


std::string VE::OpenGLShader::ReadFile(const std::string& filepath) const
{
   std::ifstream in(filepath, std::ios::in, std::ios::binary);
   std::string result;
   if (in) {
      in.seekg(0, std::ios::end);
      result.resize(in.tellg());
      in.seekg(0, std::ios::beg);
      in.read(&result[0], result.size());
      in.close();
   } else {
      ASSERT_FAILED("Coulf not open file {0}", filepath);
   }

   return result;
}


std::unordered_map<GLenum, std::string> VE::OpenGLShader::PreProcess(const std::string& source) const
{
   std::unordered_map<GLenum, std::string> shaderSources;

   const char* typeToken = "#type";
   size_t typeTokenLength = strlen(typeToken);
   size_t pos = source.find(typeToken, 0);
   while (pos != std::string::npos) {
      size_t eol = source.find_first_of("\r\n", pos);
      ASSERT_MSG(eol != std::string::npos, "Syntax error");
      size_t begin = pos + typeTokenLength + 1;
      std::string type = source.substr(begin, eol - begin);
      ASSERT_MSG(ShaderTypeFromString(type), "Invalid shader type specified");

      size_t nextLinePos = source.find_first_not_of("\r\n", eol);
      pos = source.find(typeToken, nextLinePos);
      shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
   }

   return shaderSources;
}


void VE::OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
   GLuint program = glCreateProgram();
   std::vector<GLenum> glShaderIDs(shaderSources.size());
   for (const auto& [type, source] : shaderSources) {
      GLuint shader = glCreateShader(type);

      const GLchar* sourceCStr = (const GLchar*)source.c_str();
      glShaderSource(shader, 1, &sourceCStr, 0);

      glCompileShader(shader);

      GLint isCompiled = 0;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
      if (isCompiled == GL_FALSE) {
         GLint maxLength = 0;
         glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

         std::vector<GLchar> infoLog(maxLength);
         glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

         glDeleteShader(shader);

         VE_LOG_CRITICAL("Shader compilation failure! {0}", infoLog.data());
         break;
      }

      glAttachShader(program, shader);
      glShaderIDs.push_back(shader);
   }

   redererId = program;

   // Link our program
   glLinkProgram(program);

   // Note the different functions here: glGetProgram* instead of glGetShader*.
   GLint isLinked = 0;
   glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
   if (isLinked == GL_FALSE) {
      GLint maxLength = 0;
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

      // We don't need the program anymore.
      glDeleteProgram(program);

      for (GLenum id : glShaderIDs) {
         glDeleteShader(id);
      }


      VE_LOG_CRITICAL("Shader link failure! {0}", infoLog.data());
      return;
   }

   for (GLenum id : glShaderIDs) {
      glDetachShader(program, id);
   }
}


VE::OpenGLShader::~OpenGLShader()
{
   glDeleteProgram(redererId);
}


void VE::OpenGLShader::Bind() const
{
   glUseProgram(redererId);
}


void VE::OpenGLShader::Unbind() const
{
   glUseProgram(0);
}


void VE::OpenGLShader::UploadUniformMat3(const std::string& name, const Matrix3& matrix)
{
   GLint location = glGetUniformLocation(redererId, name.c_str());
   glUniformMatrix3fv(location, 1, GL_FALSE, matrix.data());
}


void VE::OpenGLShader::UploadUniformInt(const std::string& name, int v)
{
   GLint location = glGetUniformLocation(redererId, name.c_str());
   glUniform1i(location, v);
}


void VE::OpenGLShader::UploadUniformFloat(const std::string& name, float v)
{
   GLint location = glGetUniformLocation(redererId, name.c_str());
   glUniform1f(location, v);
}


void VE::OpenGLShader::UploadUniformFloat2(const std::string& name, const Vector2& vec2)
{
   GLint location = glGetUniformLocation(redererId, name.c_str());
   glUniform2f(location, vec2.x, vec2.y);
}


void VE::OpenGLShader::UploadUniformFloat3(const std::string& name, const Vector3& vec3)
{
   GLint location = glGetUniformLocation(redererId, name.c_str());
   glUniform3f(location, vec3.x, vec3.y, vec3.z);
}


void VE::OpenGLShader::UploadUniformMat4(const std::string& name, const Matrix4& matrix)
{
   GLint location = glGetUniformLocation(redererId, name.c_str());
   glUniformMatrix4fv(location, 1, GL_FALSE, matrix.data());
}


void VE::OpenGLShader::UploadUniformFloat4(const std::string& name, const Vector4& vec4)
{
   GLint location = glGetUniformLocation(redererId, name.c_str());
   glUniform4f(location, vec4.x, vec4.y, vec4.z, vec4.z);
}