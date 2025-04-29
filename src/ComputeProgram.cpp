#include "ComputeProgram.hpp"

ComputeProgram::ComputeProgram(Shader &shader) 
{
  if (shader.GetType() != GL_COMPUTE_SHADER) throw std::exception();
  m_ID = glCreateProgram();
  shader.Attach(m_ID);
  glLinkProgram(m_ID);

  // Check the status of the program being linked
  int res;
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

void ComputeProgram::Use() 
{
  glUseProgram(m_ID);
}

ComputeProgram::~ComputeProgram() 
{
  glDeleteProgram(m_ID);
}

void ComputeProgram::Dispatch(GLuint xThreads, GLuint yThreads, GLuint zThreads) {
  glDispatchCompute(xThreads, yThreads, zThreads);
}

void ComputeProgram::SetUniform(const std::string &uniformName, GLuint val) {
  GLint loc = glGetUniformLocation(m_ID, uniformName.c_str());
  glUniform1ui(loc, val);
}

void ComputeProgram::SetUniform(const std::string &uniformName, GLint val[2]) {
  GLint loc = glGetUniformLocation(m_ID, uniformName.c_str());
  glUniform2iv(loc, 2, val);
}

void ComputeProgram::SetUniform(const std::string &uniformName, GLint val) 
{
  GLint loc = glGetUniformLocation(m_ID, uniformName.c_str());
  glUniform1i(loc, val);
}
