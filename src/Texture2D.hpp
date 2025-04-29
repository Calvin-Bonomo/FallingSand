#ifndef TEXTURE_2D
#define TEXTURE_2D

#include "Texture.hpp"

class Texture2D : public Texture 
{
public:
  template<size_t N, size_t M>
  Texture2D(const unsigned char (&data)[N][M], int lods, GLint internalFormat, GLenum pixelFormat);
  template<size_t N, size_t M>
  Texture2D(const unsigned int (&data)[N][M], int lods, GLint internalFormat, GLenum pixelFormat);
  template<typename T, size_t N, size_t M>
  void Update(const T (&data)[N][M], int lod, int xOffset, int yOffset);
  template<typename T, size_t N>
  void UpdateHorizontal(const T (&data)[N], int lod, int xOffset, int yOffset);
  template<typename T, size_t M>
  void UpdateVertical(const T (&data)[M], int lod, int xOffset, int yOffset);
  template<typename T, size_t N, size_t M>
  void Get(T (&data)[N][M], int lod, int xOffset, int yOffset);
  template<typename T, size_t N>
  void GetHorizontal(T (&data)[N], int lod, int xOffset, int yOffset);
  template<typename T, size_t M>
  void GetVertical(T (&data)[M], int lod, int xOffset, int yOffset);

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
  : Texture(GL_TEXTURE_2D, GL_UNSIGNED_BYTE, internalFormat, pixelFormat), m_LODs(lods), m_Width(N), m_Height(M)
{
  this->Init(data);
}

template<size_t N, size_t M>
Texture2D::Texture2D(const unsigned int (&data)[N][M], int lods, GLint internalFormat, GLenum pixelFormat)
  : Texture(GL_TEXTURE_2D, GL_UNSIGNED_INT, internalFormat, pixelFormat), m_LODs(lods), m_Width(N), m_Height(M)
{
  this->Init(data);
}

template<typename T, size_t N, size_t M>
void Texture2D::Update(const T (&data)[N][M], int lod, int xOffset, int yOffset) 
{
  this->UpdatePixels(data, lod, xOffset, yOffset, N, M);
}

template<typename T, size_t N>
void Texture2D::UpdateHorizontal(const T (&data)[N], int lod, int xOffset, int yOffset) 
{
  this->UpdatePixels(data, lod, xOffset, yOffset, N, 1);
}

template<typename T, size_t M>
void Texture2D::UpdateVertical(const T (&data)[M], int lod, int xOffset, int yOffset) 
{
  this->UpdatePixels(data, lod, xOffset, yOffset, 1, M);
}

template<typename T, size_t N, size_t M>
void Texture2D::Get(T (&data)[N][M], int lod, int xOffset, int yOffset) 
{
  assert(sizeof(T) == m_PixelSize);
  this->GetPixels(data, lod, xOffset, yOffset, N, M);
}

template<typename T, size_t N>
void Texture2D::GetHorizontal(T (&data)[N], int lod, int xOffset, int yOffset) 
{
  assert(sizeof(T) == m_PixelSize);
  this->GetPixels(data, lod, xOffset, yOffset, N, 1);
}

template<typename T, size_t M>
void Texture2D::GetVertical(T (&data)[M], int lod, int xOffset, int yOffset) 
{
  assert(sizeof(T) == m_PixelSize);
  this->GetPixels(data, lod, xOffset, yOffset, 1, M);
}

#endif