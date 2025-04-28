#include "Texture2D.hpp"

void Texture2D::Init(const void *data) 
{
  glTexImage2D(m_Target, 0, m_InternalFormat, m_Width, m_Height, 0, m_PixelFormat, m_Type, data);
}

void Texture2D::UpdatePixels(const void *data, int lod, int xOffset, int yOffset, size_t width, size_t height) 
{
  glTextureSubImage2D(m_ID, lod, xOffset, yOffset, width, height, m_PixelFormat, m_Type, data);
}

void Texture2D::GetPixels(void *data, int lod, int xOffset, int yOffset, size_t width, size_t height) 
{
  glGetTextureSubImage(m_ID, 
    lod, xOffset, yOffset, 0, 
    width, height, 0, 
    m_PixelFormat, m_Type, 
    m_PixelSize * width * height, data);
}
