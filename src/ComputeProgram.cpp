#include "ComputeProgram.hpp"

ComputeProgram::ComputeProgram(Shader &shader) {
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

ComputeProgram::~ComputeProgram() {
  glDeleteProgram(m_ID);
}

void ComputeProgram::Dispatch(GLuint xThreads, GLuint yThreads, GLuint zThreads) {
  glUseProgram(m_ID);
  glDispatchCompute(xThreads, yThreads, zThreads);
  glUseProgram(0);
}
