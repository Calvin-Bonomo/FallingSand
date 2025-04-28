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
  GLint m_LastAttribute;

public:
  VertexArrayObject(Buffer &vertices, Buffer &elements);
  ~VertexArrayObject();

  template<typename T>
  void AddAttribute(bool normalized, unsigned int offset, unsigned int numValues);

  void Bind();
  void Unbind();
};
