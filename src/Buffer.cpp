#include "Buffer.hpp"

Buffer::Buffer()
  : m_ID(-1), m_Size(0)
{
  glGenBuffers(1, &m_ID);
}

Buffer::~Buffer() 
{
  glDeleteBuffers(1, &m_ID);
}

void Buffer::Bind(GLenum target) 
{
  if (m_Bound) return;
  m_LastTarget = target;
  glBindBuffer(m_LastTarget, m_ID);
}

void Buffer::Unbind() 
{
  if (!m_Bound) return;
  glBindBuffer(m_LastTarget, 0);
}

GLuint Buffer::GetSize() 
{
  return m_Size;
}

size_t Buffer::GetElementSize() 
{
  return m_ElementSize;
}

void Buffer::SetData(const void *data, size_t size) {
  glNamedBufferData(m_ID, size, data, GL_DYNAMIC_DRAW);
}
