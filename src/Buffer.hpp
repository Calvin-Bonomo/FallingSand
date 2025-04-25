#pragma once

#include <stdexcept>
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

class Buffer
{
private:
  unsigned int m_ID;
  unsigned int m_Size;
  unsigned int m_ElementSize;
  GLenum m_LastTarget;
  bool m_Bound;

public:
  Buffer();
  ~Buffer();

  void Bind(GLenum target);
  void Unbind();

  template<typename T, size_t N>
  void Set(const T (&data)[N]);
  template<typename T, size_t N>
  void Update(const T (&data)[N], unsigned int offset, unsigned int numElements);
  template<typename T, size_t N>
  void Get(T (&data)[N], unsigned int offset, unsigned int numElements);

  GLuint GetSize();
  size_t GetElementSize();

  operator int() const { return m_ID; }
};

template<typename T, size_t N>
void Buffer::Set(const T (&data)[N]) {
  glNamedBufferData(m_ID, sizeof(T) * N, data, GL_DYNAMIC_DRAW);
}

template<typename T, size_t N>
void Buffer::Update(const T (&data)[N], unsigned int offset, unsigned int numElements) 
{
  if (numElements + offset > m_Size) throw std::out_of_range();
  glNamedBufferSubData(m_ID, offset * sizeof(T), sizeof(T) * numElements, data);
}

template<typename T, size_t N>
void Buffer::Get(T (&data)[N], unsigned int offset, unsigned int numElements) 
{
  if (numElements + offset > m_Size) throw std::out_of_range();
  glGetNamedBufferSubData(m_ID, offset * sizeof(T), sizeof(T) * numElements, data);
}
