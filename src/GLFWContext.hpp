#pragma once

#include <stdlib.h>
#include <memory>
#include <GLFW/glfw3.h>

class GLFWContext
{
private:
  static std::shared_ptr<GLFWContext> m_Instance;
private:
  GLFWContext();
  ~GLFWContext();
public:
  GLFWContext(const GLFWContext &) = delete;
  GLFWContext(const GLFWContext &&) = delete;

  static std::shared_ptr<GLFWContext> GetInstance();
};
