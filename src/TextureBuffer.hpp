#pragma once

#include <memory>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Buffer.hpp"

class TextureBuffer
{
private:
  GLuint m_ID;
  std::shared_ptr<Buffer> m_Buffer;

public:
  TextureBuffer(GLenum internalFormat, const Buffer &buffer);
  ~TextureBuffer();

  void Bind(GLuint textureUnit);
  void Unbind();

  operator int() const { return m_ID; }
};
