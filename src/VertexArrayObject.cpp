#include "VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject(Buffer<float> &vertices, Buffer<unsigned int> &elements) 
{
  
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
