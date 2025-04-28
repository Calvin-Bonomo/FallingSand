#pragma once

#include <string>
#include <iostream>
#include <fstream>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Shader.hpp"

class ShaderProgram
{
private:
  unsigned int m_ID;

public:
  ShaderProgram();
  ~ShaderProgram();

  void Use();
  void Stop();

  void AttachShader(Shader &shader);
  void Link();

  void SetUniform(const std::string &uniformName, GLfloat val[2]);
  void SetUniform(const std::string &uniformName, GLfloat val1, GLfloat val2);
  void SetUniform(const std::string &uniformName, GLint val);
};
