#pragma once

#include <stdexcept>
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

template<typename T>
class Buffer
{
private:
  unsigned int m_ID;
  unsigned int m_Size;
  GLenum m_LastTarget;
  bool m_Bound;

public:
  Buffer() = delete;
  template<size_t N>
  Buffer(const T (&data)[N], unsigned int size);
  ~Buffer();

  void Bind(GLenum target);
  void Unbind();

  template<size_t N>
  void Update(unsigned int offset, const T (&data)[N], unsigned int size);
  template<size_t N>
  void Get(unsigned int offset, T (&data)[N], unsigned int size);

  GLuint GetSize();
};
