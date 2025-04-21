#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Buffer.hpp"

class VertexArrayObject
{
private:
  GLuint m_ID;
  GLuint m_Size;

public:
  VertexArrayObject(Buffer<float> &vertices, Buffer<unsigned int> &elements);
  ~VertexArrayObject();

  void Bind();
  void Unbind();
};
