#pragma once

#include <string>
#include <iostream>
#include <fstream>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Shader.hpp"
#include "TextureBuffer.hpp"

class ComputeProgram
{
private:
  GLuint m_ID;

public:
  ComputeProgram(Shader &shader);
  ~ComputeProgram();

  void Dispatch(GLuint xThreads, GLuint yThreads, GLuint zThreads);
  void SetUniform(const std::string &uniformName, GLuint val);
  void SetUniform(const std::string &uniformName, GLint val[2]);
  void SetUniform(const std::string &uniformName, GLint val);
};
