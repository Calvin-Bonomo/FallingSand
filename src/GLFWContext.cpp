#include "GLFWContext.hpp"

GLFWContext::GLFWContext() 
{
  if (!glfwInit()) exit(1);
  glfwSetErrorCallback(GLFWContext::ErrorCallback);
}

GLFWContext::~GLFWContext() 
{
  glfwTerminate();
}

void GLFWContext::Init() 
{
  if (!GLFWContext::m_Instance) 
    m_Instance = new GLFWContext();
}

void GLFWContext::ErrorCallback(int error, const char* description) {
  printf("GLFW ERROR:\n\t%d: %s\n", error, description);
}