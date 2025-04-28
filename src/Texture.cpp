#include "Texture.hpp"

Texture::~Texture() 
{
  glDeleteTextures(1, &m_ID);
}

void Texture::Bind(int textureUnit) 
{
  if (textureUnit < 0) return;
  m_TextureUnit = textureUnit;
  glActiveTexture(GL_TEXTURE0 + m_TextureUnit);
  glBindTexture(m_Target, m_ID);
}

void Texture::Unbind() 
{
  if (m_TextureUnit < 0) return;
  glActiveTexture(GL_TEXTURE0 + m_TextureUnit);
  glBindTexture(m_Target, 0);
  m_TextureUnit = -1;
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
  Bind(0);
  glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, val);
  glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, val);
  Unbind();
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

Texture::Texture(const void *data, GLenum target, GLenum type, GLenum internalFormat, GLenum pixelFormat) 
  : m_Target(target), m_Type(type), m_InternalFormat(internalFormat), 
  m_PixelFormat(pixelFormat), m_PixelSize(TypeToSize(type))
{
  glCreateTextures(m_Target, 1, &m_ID);
}
