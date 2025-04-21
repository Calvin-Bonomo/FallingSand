#include "GLFWContext.hpp"

GLFWContext::GLFWContext() {
  if (glfwInit() == GLFW_FALSE) exit(1); // Unable to initialize glfw
}
GLFWContext::~GLFWContext() {
  glfwTerminate();
}

std::shared_ptr<GLFWContext> GLFWContext::GetInstance() {
  if (!m_Instance.get()) // Create instance
    m_Instance = std::make_shared<GLFWContext>();
  return m_Instance;
}
