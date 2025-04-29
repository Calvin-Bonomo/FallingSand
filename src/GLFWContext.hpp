#ifndef GLFW_CONTEXT
#define GLFW_CONTEXT

#include "GLFW/glfw3.h"

#include <cstdio>
#include <cstdlib>
#include <memory>

class GLFWContext
{
private:
  static GLFWContext *m_Instance;
  GLFWContext();
  GLFWContext(const GLFWContext &) = delete;
  GLFWContext(const GLFWContext &&) = delete;
  ~GLFWContext();

  static void ErrorCallback(int error, const char* description);
public:
  static void Init();
};

#endif