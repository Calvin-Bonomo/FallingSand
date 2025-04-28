#pragma once

#include <cassert>
#include <array>

#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

enum class WrapMode {
  ClampToEdge,
  MirroredClamToEdge,
  ClampToBorder,
  Repeat,
  MirroredRepeat
};

class Texture
{
protected:
  virtual void InitializeTexture(const void *data) = 0;

public:
  ~Texture();

  void Bind(int textureUnit);
  void Unbind();

  void SetWrapMode(WrapMode mode);

protected:
  Texture(const void *data, GLenum target, GLenum internalFormat, GLenum type, GLenum pixelFormat);
  Texture(const Texture &) = delete;
  Texture(const Texture &&) = delete;

  inline size_t TypeToSize(GLenum type);

protected:
  GLuint m_ID;
  size_t m_PixelSize;
  GLenum m_Target, m_InternalFormat, m_PixelFormat, m_Type;

private:
  int m_TextureUnit;

private:
  void CreateTexture();
};
