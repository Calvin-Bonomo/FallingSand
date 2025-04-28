#pragma once

#include "Texture.hpp"

class Texture2D : public Texture 
{
public:
  template<size_t N, size_t M>
  Texture2D(const unsigned char (&data)[N][M], int lods, GLint internalFormat, GLenum pixelFormat);
  template<typename T, size_t N, size_t M>
  void Update(const T (&data)[N][M], int lod, int xOffset, int yOffset);
  template<typename T, size_t N, size_t M>
  void Get(T (&data)[N][M], int lod, int xOffset, int yOffset);

private:
  void Init(const void *data);
  void UpdatePixels(const void *data, int lod, int xOffset, int yOffset, size_t width, size_t height);
  void GetPixels(void *data, int lod, int xOffset, int yOffset, size_t width, size_t height);

private:
  int m_LODs;
  size_t m_Width, m_Height;
};

template<size_t N, size_t M>
Texture2D::Texture2D(const unsigned char (&data)[N][M], int lods, GLint internalFormat, GLenum pixelFormat)
  : m_LODs(lods), m_Width(N), m_Height(M), Texture(GL_TEXTURE_2D, internalFormat, GL_UNSIGNED_BYTE, pixelFormat)
{
  this->Init(data);
}

template<typename T, size_t N, size_t M>
void Texture2D::Update(const T (&data)[N][M], int lod, int xOffset, int yOffset) 
{
  assert(sizeof(T) == this->m_PixelSize && N <= xOffset + this->m_Width && M <= yOffset + this->m_Height);
  this->UpdatePixels(data, lod, xOffset, yOffset, N, M);
}

template<typename T, size_t N, size_t M>
void Texture2D::Get(T (&data)[N][M], int lod, int xOffset, int yOffset) 
{
  assert(sizeof(T) == this->m_PixelSize && N <= xOffset + this->m_Width && M <= yOffset + this->m_Height);
  this->GetPixels(data, lod, xOffset, yOffset, N, M);
}