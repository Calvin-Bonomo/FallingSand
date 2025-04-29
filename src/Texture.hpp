#ifndef TEXTURE
#define TEXTURE

#include <cassert>
#include <array>
#include "stdio.h"

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

enum class FilteringMode {
  Nearest,
  Linear
};

class Texture
{
public:
  ~Texture();

  void Bind();
  void Unbind();

  void BindAsImage(GLuint unit, GLint level, bool layered, GLint layer, GLenum access);

  void SetWrapMode(WrapMode mode);
  void SetFilteringMode(FilteringMode mode);

protected:
  Texture(GLenum target, GLenum type, GLint internalFormat, GLenum pixelFormat);
  Texture(const Texture &) = delete;
  Texture(const Texture &&) = delete;

  inline size_t TypeToSize(GLenum type);

protected:
  GLuint m_ID;
  size_t m_PixelSize;
  GLenum m_Target, m_PixelFormat, m_Type;
  GLint m_InternalFormat;
};

#endif