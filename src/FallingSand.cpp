#include "FallingSand.hpp"

GLFWContext *GLFWContext::m_Instance = nullptr;

FallingSand::FallingSand(unsigned int windowWidth, unsigned int windowHeight, std::string configPath)
  : m_Width(windowWidth), m_Height(windowHeight), m_Window(nullptr)
{
  m_RenderScale[0] = m_Width / DEFAULT_SIM_WIDTH;
  m_RenderScale[1] = m_Height / DEFAULT_SIM_HEIGHT;
  CreateWindow();
  LoadConfig(configPath);
  cell_t cells[DEFAULT_SIM_WIDTH * DEFAULT_SIM_HEIGHT];
  for (int i = 0; i < DEFAULT_WINDOW_WIDTH * DEFAULT_SIM_HEIGHT; i++)
    cells[i] = m_CellTypes[0];

  // m_CellBuffer = Buffer<cell_t>(cells, DEFAULT_SIM_WIDTH * DEFAULT_SIM_HEIGHT);

  Shader vert("res/shaders/default.vert", ShaderType::Vertex), 
    frag("res/shaders/finaldraw.frag", ShaderType::Fragment),
    comp("res/shaders/fallingsand.comp", ShaderType::Compute);
  m_DisplayProgram = std::make_unique<ShaderProgram>();
  m_ComputeSim = std::make_unique<ComputeProgram>(comp);
  m_DisplayProgram->AttachShader(vert);
  m_DisplayProgram->AttachShader(frag);
  m_DisplayProgram->Link();
}

FallingSand::~FallingSand() {
  glfwDestroyWindow(m_Window);
}

void FallingSand::LoadConfig(std::string path) {

}

void FallingSand::Play() {
  double deltaTime, currentTime, lastTickTime = glfwGetTime();
  while (!glfwWindowShouldClose(m_Window)) {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTickTime;
    if (deltaTime >= DEFAULT_TICK_SPEED) {
      lastTickTime = currentTime;
      m_ComputeSim->SetUniform("iteration", m_SimIterations);
      m_ComputeSim->SetUniform("simSize", m_SimDim);
      m_ComputeSim->SetUniform("buf", *m_SimSpaceTexture);
      m_ComputeSim->Dispatch(1, 1, 1);
    }

    Display();
  }
}

void FallingSand::CreateWindow() {
  GLFWContext::MakeContext();

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
  if (action == GLFW_REPEAT || action == GLFW_RELEASE) return;

  if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void FallingSand::MouseMoveCallback(GLFWwindow *window, double xpos, double ypos) {

}

void FallingSand::MouseDownCallback(GLFWwindow *window, int button, int action, int mods) {

}

void FallingSand::WindowResizeCallback(GLFWwindow* window, int width, int height) {

}
