#pragma once

#include <stdlib.h>
#include <memory>
#include <GLFW/glfw3.h>


class GLFWContext
{
private:
  static GLFWContext *m_Instance;
  GLFWContext();
  ~GLFWContext();
public:
  GLFWContext(const GLFWContext &) = delete;
  GLFWContext(const GLFWContext &&) = delete;

  static void MakeContext();
};
