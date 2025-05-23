#include "FallingSand.hpp"

GLFWContext *GLFWContext::m_Instance = nullptr;

#ifdef DEBUG
void GLAPIENTRY debugCallback( GLenum source,
  GLenum type,
  GLuint id,
  GLenum severity,
  GLsizei length,
  const GLchar* message,
  const void* userParam )
{
  if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
    ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
    type, severity, message );
}
#endif

FallingSand::FallingSand(unsigned int windowWidth, unsigned int windowHeight, std::string configPath)
  : m_Width(windowWidth), m_Height(windowHeight), m_Window(nullptr)
{
  m_RenderScale[0] = m_Width / DEFAULT_SIM_WIDTH;
  m_RenderScale[1] = m_Height / DEFAULT_SIM_HEIGHT;
  CreateWindow();
  #ifdef DEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(debugCallback, 0);
  #endif
  unsigned int cells[DEFAULT_SIM_WIDTH][DEFAULT_SIM_HEIGHT];
  for (int i = 0; i < DEFAULT_SIM_WIDTH; i++) 
  {
    for (int j = 0; j < DEFAULT_SIM_HEIGHT; j++) 
    {
      cells[i][j] = 0;
      if (!i || !j || i == DEFAULT_SIM_WIDTH - 1 || j == DEFAULT_SIM_HEIGHT - 1) cells[i][j] = 6;
    }
  }

  CreateRenderQuad();

  m_CellsTexture = std::make_unique<Texture2D>(cells, 1, GL_R32UI, GL_RED_INTEGER);

  Shader vert("res/shaders/default.vert", ShaderType::Vertex), 
    frag("res/shaders/finaldraw.frag", ShaderType::Fragment),
    comp("res/shaders/fallingsand.comp", ShaderType::Compute);
  m_DisplayProgram = std::make_unique<ShaderProgram>();
  m_ComputeSim = std::make_unique<ComputeProgram>(comp);
  m_DisplayProgram->AttachShader(vert);
  m_DisplayProgram->AttachShader(frag);
  m_DisplayProgram->Link();
}

FallingSand::~FallingSand() 
{
  glfwDestroyWindow(m_Window);
}

void FallingSand::CreateRenderQuad() 
{
  point points[4] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
  Buffer pointBuf(points);
  m_DrawQuad = std::make_unique<VertexArrayObject>(pointBuf);
  m_DrawQuad->AddAttribute<float>(false, 0, 2);
}

void FallingSand::LoadConfig(std::string path) 
{

}

void FallingSand::Play() 
{
  double deltaTime, currentTime, lastTickTime = glfwGetTime();
  while (!glfwWindowShouldClose(m_Window)) {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTickTime;
    if (deltaTime >= DEFAULT_TICK_SPEED) {
      DoInteraction();
      lastTickTime = currentTime;
      m_ComputeSim->Use();
      m_ComputeSim->SetUniform("iteration", m_SimIterations++);
      m_ComputeSim->SetUniform("simSize", m_SimDim);
      m_CellsTexture->BindAsImage(0, 0, true, 0, GL_READ_WRITE);
      m_ComputeSim->SetUniform("buf", 0);
      m_ComputeSim->Dispatch(1, 1, 1);
    }

    Display();
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }
}

void FallingSand::CreateWindow() 
{
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef DEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
  #endif
  m_Window = glfwCreateWindow(m_Width, m_Height, WINDOW_NAME, NULL, NULL);
  if (!m_Window) exit(1); // Window creation failed
  glfwMakeContextCurrent(m_Window);

  // Setup callbacks
  glfwSetMouseButtonCallback(m_Window, FallingSand::MouseDownCallback);
  glfwSetCursorPosCallback(m_Window, FallingSand::MouseMoveCallback);
  glfwSetKeyCallback(m_Window, FallingSand::KeyPressCallback);
  glfwSetWindowUserPointer(m_Window, this);

  SetDimensions(m_Width, m_Height);
}

void FallingSand::Display() 
{
  glClear(GL_COLOR_BUFFER_BIT);
  m_DrawQuad->Bind();
  m_DisplayProgram->Use();
  m_CellsTexture->Bind();
  m_DisplayProgram->SetUniform("texelSize", 1 / 65.0, 1 / 65.0);
  m_DisplayProgram->SetUniform("buf", 0);
  m_DrawQuad->DrawStrip();
  glFlush();
}

void FallingSand::DoInteraction() 
{
  unsigned int cellBuf[3][3], 
    xOffset = m_MousePos[0] / m_RenderScale[0] - 1, 
    yOffset = (m_Height - m_MousePos[1]) / m_RenderScale[1] - 1;

  if (!m_MouseDown 
    || xOffset < 1 || xOffset > m_SimDim[0] - 3 
    || yOffset < 1 || yOffset > m_SimDim[1] - 3) return;

  m_CellsTexture->Bind();
  m_CellsTexture->Get(cellBuf, 0, xOffset, yOffset);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (!cellBuf[i][j]) { 
        cellBuf[i][j] = m_CellType;
      } else if (!m_CellType) {
        cellBuf[i][j] = m_CellType;
      }
    }
  }
  
  m_CellsTexture->Update(cellBuf, 0, xOffset, yOffset);
  m_CellsTexture->Unbind();
}

void FallingSand::SetDimensions(unsigned int width, unsigned int height) 
{
  m_Width = width;
  m_Height = height;
  glViewport(0, 0, m_Width, m_Height);
}

void FallingSand::KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
  if (action == GLFW_REPEAT || action == GLFW_RELEASE) return;
  FallingSand *game = (FallingSand *)glfwGetWindowUserPointer(window);

  if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE);
  else if (key == GLFW_KEY_SPACE) game->m_CellType = (game->m_CellType + 1) % FallingSand::NUM_CELLS;
}

void FallingSand::MouseMoveCallback(GLFWwindow *window, double xpos, double ypos) 
{
  FallingSand *game = (FallingSand *)glfwGetWindowUserPointer(window);
  game->m_MousePos[0] = xpos;
  game->m_MousePos[1] = ypos;
}

void FallingSand::MouseDownCallback(GLFWwindow *window, int button, int action, int mods) 
{
  FallingSand *game = (FallingSand *)glfwGetWindowUserPointer(window);
  if (button != GLFW_MOUSE_BUTTON_LEFT) return;
  game->m_MouseDown = action != GLFW_RELEASE;
}

void FallingSand::WindowResizeCallback(GLFWwindow* window, int width, int height) 
{
  FallingSand *game = (FallingSand *)glfwGetWindowUserPointer(window);
  game->SetDimensions(width, height);
}
