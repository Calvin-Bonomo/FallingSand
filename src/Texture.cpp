#include "Texture.hpp"

Texture::~Texture() 
{
  glDeleteTextures(1, &m_ID);
}

void Texture::Bind() 
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(m_Target, m_ID);
}

void Texture::Unbind() 
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(m_Target, 0);
}

void Texture::SetWrapMode(WrapMode mode) 
{
  int val;
  switch (mode)
  {
    case WrapMode::ClampToEdge:
      val = GL_CLAMP_TO_EDGE;
      break;
    case WrapMode::MirroredClamToEdge:
      val = GL_MIRROR_CLAMP_TO_EDGE;
      break;
    case WrapMode::ClampToBorder:
      val = GL_CLAMP_TO_BORDER;
      break;
    case WrapMode::Repeat:
      val = GL_REPEAT;
      break;
    case WrapMode::MirroredRepeat:
      val = GL_MIRRORED_REPEAT;
      break;
  }
  glBindTexture(m_Target, m_ID);
  glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, val);
  glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, val);
  glBindTexture(m_Target, 0);
}

void Texture::SetFilteringMode(FilteringMode mode) 
{
  int val;
  switch(mode) {
    case FilteringMode::Nearest:
      val = GL_NEAREST;
      break;
    case FilteringMode::Linear:
      val = GL_LINEAR;
      break;
  }
  glBindTexture(m_Target, m_ID);
  glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, val);
  glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, val);
  glBindTexture(m_Target, 0);
}

inline size_t Texture::TypeToSize(GLenum type) 
{
  size_t elementSize;
  switch(type) {
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
    case GL_UNSIGNED_BYTE_2_3_3_REV:
    case GL_UNSIGNED_BYTE_3_3_2:
      elementSize = sizeof(char);
      break;
    case GL_SHORT:
    case GL_UNSIGNED_SHORT:
    case GL_UNSIGNED_SHORT_5_6_5:
    case GL_UNSIGNED_SHORT_5_6_5_REV:
    case GL_UNSIGNED_SHORT_4_4_4_4:
    case GL_UNSIGNED_SHORT_4_4_4_4_REV:
    case GL_UNSIGNED_SHORT_5_5_5_1:
    case GL_UNSIGNED_SHORT_1_5_5_5_REV:
      elementSize = sizeof(short);
      break;
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_UNSIGNED_INT_8_8_8_8:
    case GL_UNSIGNED_INT_8_8_8_8_REV:
    case GL_UNSIGNED_INT_10_10_10_2:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
      elementSize = sizeof(int);
      break;
    default:
      elementSize = 0;
      break;
  }
  return elementSize;
}

Texture::Texture(GLenum target, GLenum type, GLint internalFormat, GLenum pixelFormat) 
  : m_Target(target), m_Type(type), m_InternalFormat(internalFormat), 
  m_PixelFormat(pixelFormat), m_PixelSize(TypeToSize(type))
{
  glGenTextures(1, &m_ID);
}

void Texture::BindAsImage(GLuint unit, GLint level, bool layered, GLint layer, GLenum access) 
{
  glBindImageTexture(unit, m_ID, level, layered? GL_TRUE : GL_FALSE, layer, access, m_InternalFormat);
}
