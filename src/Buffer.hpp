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
  template<typename T, size_t N>
  Buffer(const T (&data)[N]);
  ~Buffer();

  void Bind(GLenum target);
  void Unbind();

  template<typename T, size_t N>
  void Update(const T (&data)[N], unsigned int offset, unsigned int numElements);
  template<typename T, size_t N>
  void Get(T (&data)[N], unsigned int offset, unsigned int numElements);

  GLuint GetSize();
  size_t GetElementSize();

  operator unsigned int() const { return m_ID; }

private:
  void Init();
  void SetData(const void *data, size_t size);
};

template<typename T, size_t N>
Buffer::Buffer(const T (&data)[N]) 
  : m_Size(N), m_ElementSize(sizeof(T))
{
  this->Init();
  this->SetData(data, sizeof(T) * N);
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
