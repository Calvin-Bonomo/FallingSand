#include "Shader.hpp"

Shader::Shader(const std::string &filename, ShaderType type) 
{
  std::string source = ReadShader(filename);
  int sourceLen = source.size();
  const char *srcArr = source.c_str();
  switch (type) {
    case ShaderType::Compute: 
      m_Type = GL_COMPUTE_SHADER; 
      break;
    case ShaderType::Fragment:
      m_Type = GL_FRAGMENT_SHADER;
      break;
    case ShaderType::Vertex:
      m_Type = GL_VERTEX_SHADER;
      break;
    case ShaderType::TesselationEval:
      m_Type = GL_TESS_EVALUATION_SHADER;
      break;
    case ShaderType::TesselationCtrl:
      m_Type = GL_TESS_CONTROL_SHADER;
      break;
    case ShaderType::Geometry:
      m_Type = GL_GEOMETRY_SHADER;
      break;
  }

  m_ID = glCreateShader(m_Type);
  glShaderSource(m_ID, 1, &srcArr, &sourceLen);
  glCompileShader(m_ID);
  glGetShaderiv(m_ID, GL_COMPILE_STATUS, &sourceLen);
  if (!sourceLen) {
    glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &sourceLen);
    if (!sourceLen) return;
    char *log = new char[sourceLen];
    GLsizei size;
    glGetShaderInfoLog(m_ID, sourceLen, &size, log);
    printf("%s\n", log);
  }
}

Shader::~Shader() 
{
  glDeleteShader(m_ID);
}

GLenum Shader::GetType() 
{
  return m_Type;
}

void Shader::Attach(GLuint programID) 
{
  glAttachShader(programID, m_ID);
}

std::string Shader::ReadShader(const std::string &filename) 
{
  std::string source;
  std::ifstream inStream(filename);

  if (inStream.is_open()) { // https://cplusplus.com/forum/beginner/151894/
    while (inStream.good())
      getline(inStream, source);
  }

  inStream.close();
  return source;
}
