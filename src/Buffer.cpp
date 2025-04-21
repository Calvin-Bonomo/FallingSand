#include "Buffer.hpp"

template<typename T>
template<size_t N>
Buffer<T>::Buffer(const T (&data)[N], unsigned int size)
  : m_ID(-1), m_Size(size)
{
  glGenBuffers(1, &m_ID);
  glNamedBufferData(m_ID, sizeof(T) * m_Size, data, GL_DYNAMIC_DRAW);
}

template<typename T>
Buffer<T>::~Buffer() 
{
  glDeleteBuffers(1, &m_ID);
}

template<typename T>
void Buffer<T>::Bind(GLenum target) 
{
  if (m_Bound) return;
  m_LastTarget = target;
  glBindBuffer(m_LastTarget, m_ID);
}

template<typename T>
void Buffer<T>::Unbind() 
{
  if (!m_Bound) return;
  glBindBuffer(m_LastTarget, 0);
}

template<typename T>
template<size_t N>
void Buffer<T>::Update(unsigned int offset, const T (&data)[N], unsigned int size) 
{
  if (size + offset > m_Size) throw std::out_of_range();
  glNamedBufferSubData(m_ID, offset * sizeof(T), sizeof(T) * size, data);
}

template<typename T>
template<size_t N>
void Buffer<T>::Get(unsigned int offset, T (&data)[N], unsigned int size) 
{
  if (size + offset > m_Size) throw std::out_of_range();
  glGetNamedBufferSubData(m_ID, offset * sizeof(T), sizeof(T) * size, data)
}

template<typename T>
GLuint Buffer<T>::GetSize() 
{
  return m_Size;
}
