#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() 
  : m_ID(0) 
{
  m_ID = glCreateProgram();
}

ShaderProgram::~ShaderProgram() 
{
  glDeleteProgram(m_ID);
}

void ShaderProgram::AttachShader(Shader &shader) 
{
  if (shader.GetType() == GL_COMPUTE_SHADER) throw std::exception();
  shader.Attach(m_ID);
}

void ShaderProgram::Link() {
  int res;
  glLinkProgram(m_ID);

  // Check the status of the program being linked
  glGetProgramiv(m_ID, GL_LINK_STATUS, &res);
  if (!res) {
    glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &res);
    if (!res) return;
    char *log = new char[res];
    GLsizei size;
    glGetProgramInfoLog(m_ID, res, &size, log);
    printf("%s\n", log);
  }
}
