#include "TextureBuffer.hpp"

template<typename T>
TextureBuffer<T>::TextureBuffer(GLenum internalFormat, std::shared_ptr<Buffer<T>> buffer) 
{
  glGenTextures(1, &m_ID);
  Bind(0);
  glTexBuffer(GL_TEXTURE_BUFFER, internalFormat, buffer);
  Unbind();
}

template<typename T>
TextureBuffer<T>::~TextureBuffer() 
{
  glDeleteTextures(1, &m_ID);
}

template<typename T>
void TextureBuffer<T>::Bind(GLuint textureUnit) 
{
  glActiveTexture(GL_TEXTURE0 + textureUnit);
  glBindTexture(GL_TEXTURE_BUFFER, m_ID);
}

template<typename T>
void TextureBuffer<T>::Unbind() 
{
  glBindTexture(GL_TEXTURE_BUFFER, 0);
}
