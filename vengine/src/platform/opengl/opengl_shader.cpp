﻿#include "ve_pch.h"
#include "opengl_shader.h"
#include <glad/glad.h>


#include "common/ve_log.h"

VE::OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
{
   // Create an empty vertex shader handle
   GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

   // Send the vertex shader source code to GL
   // Note that std::string's .c_str is NULL character terminated.
   const GLchar* source = (const GLchar*)vertexSource.c_str();
   glShaderSource(vertexShader, 1, &source, 0);

   // Compile the vertex shader
   glCompileShader(vertexShader);

   GLint isCompiled = 0;
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
   if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      glDeleteShader(vertexShader);

      VE_LOG_CRITICAL("Vertex shader compilation failure! {0}", infoLog.data());
      return;
   }

   // Create an empty fragment shader handle
   GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

   // Send the fragment shader source code to GL
   // Note that std::string's .c_str is NULL character terminated.
   source = (const GLchar*)fragmentSource.c_str();
   glShaderSource(fragmentShader, 1, &source, 0);

   // Compile the fragment shader
   glCompileShader(fragmentShader);

   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
   if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<GLchar> infoLog(maxLength);
      glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      glDeleteShader(fragmentShader);
      // Either of them. Don't leak shaders.
      glDeleteShader(vertexShader);

      VE_LOG_CRITICAL("Vertex shader compilation failure! {0}", infoLog.data());
      return;
   }

   // Vertex and fragment shaders are successfully compiled.
   // Now time to link them together into a program.
   // Get a program object.
   GLuint program = glCreateProgram();
   redererId = program;

   // Attach our shaders to our program
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);

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
      // Don't leak shaders either.
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);

      VE_LOG_CRITICAL("Shader link failure! {0}", infoLog.data());
      return;
   }

   // Always detach shaders after a successful link.
   glDetachShader(program, vertexShader);
   glDetachShader(program, fragmentShader);
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