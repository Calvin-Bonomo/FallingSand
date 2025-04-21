#include "FallingSand.hpp"

FallingSand::FallingSand(unsigned int windowWidth, unsigned int windowHeight, std::string configPath)
  : m_Width(windowWidth), m_Height(windowHeight), m_Window(nullptr)
{
  CreateWindow();
  LoadConfig(configPath);
  cell_t cells[DEFAULT_SIM_WIDTH * DEFAULT_SIM_HEIGHT];
  for (int i = 0; i < DEFAULT_WINDOW_WIDTH * DEFAULT_SIM_HEIGHT; i++)
    cells[i] = m_CellTypes[0];

  m_CellBuffer = std::make_unique<Buffer<cell_t>>(cells, DEFAULT_SIM_WIDTH * DEFAULT_SIM_HEIGHT);
}

FallingSand::~FallingSand() {
  glfwDestroyWindow(m_Window);
}

void FallingSand::LoadConfig(std::string path) {

}

void FallingSand::Play() {
  while (!glfwWindowShouldClose(m_Window)) {
    
    Display();
  }
}

void FallingSand::CreateWindow() {
  GLFWContext::GetInstance(); // Initialize GLFW

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  m_Window = glfwCreateWindow(m_Width, m_Height, WINDOW_NAME, NULL, NULL);
  if (!m_Window) exit(1); // Window creation failed

  glfwSetMouseButtonCallback(m_Window, FallingSand::MouseDownCallback);
  glfwSetCursorPosCallback(m_Window, FallingSand::MouseMoveCallback);
  glfwSetKeyCallback(m_Window, FallingSand::KeyPressCallback);
  glfwSetWindowUserPointer(m_Window, this);
  glfwMakeContextCurrent(m_Window);
}

void FallingSand::Display() {

}

void FallingSand::KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void FallingSand::MouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {

}

void FallingSand::MouseDownCallback(GLFWwindow *window, int button, int action, int mods) {

}

void FallingSand::WindowResizeCallback(GLFWwindow* window, int width, int height) {

}
