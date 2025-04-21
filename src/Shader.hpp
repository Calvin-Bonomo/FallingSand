#pragma once

#include <string>
#include <iostream>
#include <fstream>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

enum class ShaderType {
  Compute,
  Fragment,
  Vertex,
  TesselationEval,
  TesselationCtrl,
  Geometry
};

class Shader
{
private:
  GLuint m_ID;
  GLenum m_Type;

public:
  Shader(const std::string &filename, ShaderType type);
  ~Shader();

  GLenum GetType();

  void Attach(GLuint programID);
private:
  std::string ReadShader(const std::string &filename);
};
