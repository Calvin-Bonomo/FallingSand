#include "TextureBuffer.hpp"

TextureBuffer::TextureBuffer(GLenum internalFormat, const Buffer &buffer) 
{
  glGenTextures(1, &m_ID);
  Bind(0);
  glTexBuffer(GL_TEXTURE_BUFFER, internalFormat, buffer);
  Unbind();
}

TextureBuffer::~TextureBuffer() 
{
  glDeleteTextures(1, &m_ID);
}

void TextureBuffer::Bind(GLuint textureUnit) 
{
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(GL_TEXTURE_BUFFER, m_ID);
}

void TextureBuffer::Unbind() 
{
  glBindTexture(GL_TEXTURE_BUFFER, 0);
}
