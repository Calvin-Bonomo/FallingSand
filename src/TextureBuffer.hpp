#pragma once

#include <memory>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Buffer.hpp"

template<typename T>
class TextureBuffer
{
private:
  GLuint m_ID;
  std::shared_ptr<Buffer<T>> m_Buffer;

public:
  TextureBuffer(GLenum internalFormat, std::shared_ptr<Buffer<T>> buffer);
  ~TextureBuffer();

  void Bind(GLuint textureUnit);
  void Unbind();

  operator unsigned int() const { return m_ID; }
};
