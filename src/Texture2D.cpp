#include "Texture2D.hpp"

void Texture2D::Init(const void *data) 
{
  glBindTexture(m_Target, m_ID);

  glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTextureStorage2D(m_ID, m_LODs, m_InternalFormat, m_Width, m_Height);
  glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, m_PixelFormat, m_Type, data);
  glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT);
}

void Texture2D::UpdatePixels(const void *data, int lod, int xOffset, int yOffset, size_t width, size_t height) 
{
  glTexSubImage2D(m_Target, lod, xOffset, yOffset, width, height, m_PixelFormat, m_Type, data);
  glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT);
}

void Texture2D::GetPixels(void *data, int lod, int xOffset, int yOffset, size_t width, size_t height) 
{
  glGetTextureSubImage(m_ID, 
    lod, xOffset, yOffset, 0, 
    width, height, 1, 
    m_PixelFormat, m_Type, 
    m_PixelSize * width * height, data);
}
