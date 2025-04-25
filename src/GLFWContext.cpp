#include "GLFWContext.hpp"

GLFWContext::GLFWContext() 
{
  if (glfwInit() == GLFW_FALSE) exit(1); // Unable to initialize glfw
}
GLFWContext::~GLFWContext() 
{
  glfwTerminate();
}

void GLFWContext::MakeContext() 
{
  if (!m_Instance) m_Instance = new GLFWContext();
}
