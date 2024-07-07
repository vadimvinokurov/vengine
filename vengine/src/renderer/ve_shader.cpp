#include "ve_pch.h"
#include "ve_shader.h"
#include <glad/glad.h>


#include "common/ve_log.h"

VE::Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
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


VE::Shader::~Shader()
{
   glDeleteProgram(redererId);
}


void VE::Shader::Bind() const
{
   glUseProgram(redererId);
}


void VE::Shader::Unbind() const
{
   glUseProgram(0);
}