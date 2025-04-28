#include "VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject(Buffer &vertices, Buffer &elements) 
  : m_Size(elements.GetSize()), m_LastAttribute(0)
{
  glCreateVertexArrays(1, &m_ID);
  Bind();
  elements.Bind(GL_ELEMENT_ARRAY_BUFFER);
  Unbind();
  glVertexArrayVertexBuffer(m_ID, 0, vertices, 0, vertices.GetElementSize());
}

VertexArrayObject::VertexArrayObject(Buffer &vertices) 
  : m_Size(vertices.GetSize()), m_LastAttribute(0)
{
  glCreateVertexArrays(1, &m_ID);
  Bind();
  Unbind();
  glVertexArrayVertexBuffer(m_ID, 0, vertices, 0, vertices.GetElementSize());
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

void VertexArrayObject::DrawStrip() 
{
  Bind();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, m_Size);
  Unbind();
}

template<>
void VertexArrayObject::AddAttribute<float>(bool normalized, unsigned int offset, unsigned int numValues) 
{
  glEnableVertexArrayAttrib(m_ID, m_LastAttribute);
  glVertexArrayAttribFormat(m_ID, m_LastAttribute, numValues, GL_FLOAT, normalized? GL_TRUE : GL_FALSE, offset);
  glVertexArrayAttribBinding(m_ID, m_LastAttribute, 0);
  m_LastAttribute++;
}
