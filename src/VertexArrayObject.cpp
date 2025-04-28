#include "VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject(Buffer &vertices, Buffer &elements) 
  : m_LastAttribute(-1)
{
  glCreateVertexArrays(1, &m_ID);
  glVertexArrayVertexBuffer(m_ID, 0, vertices, 0, vertices.GetElementSize());
  Bind();
  elements.Bind(GL_ELEMENT_ARRAY_BUFFER);
  Unbind();
}

VertexArrayObject::~VertexArrayObject() 
{
  glDeleteVertexArrays(1, &m_ID);
}

void VertexArrayObject::Bind() 
{
  glBindVertexArray(m_ID);
}

void VertexArrayObject::Unbind() 
{
  glBindVertexArray(0);
}

template<>
void VertexArrayObject::AddAttribute<float>(bool normalized, unsigned int offset, unsigned int numValues) 
{
  glEnableVertexArrayAttrib(m_ID, ++m_LastAttribute);
  glVertexArrayAttribFormat(m_ID, m_LastAttribute, sizeof(float) * numValues, GL_FLOAT, normalized? GL_TRUE : GL_FALSE, offset);
}
