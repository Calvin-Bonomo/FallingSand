#ifndef FALLING_SAND
#define FALLING_SAND

#define GL_GLEXT_PROTOTYPES
#include "GLFW/glfw3.h"
#include "GL/glu.h"
#include "GL/gl.h"

#include "Buffer.hpp"
#include "GLFWContext.hpp"
#include "ComputeProgram.hpp"
#include "ShaderProgram.hpp"
#include "VertexArrayObject.hpp"
#include "Texture2D.hpp"

#include <string>
#include <array>
#include <vector>
#include <memory>

typedef unsigned char cell_t;

struct point {
  float x, y;
};

class FallingSand
{
private: // constants
  static constexpr unsigned int DEFAULT_WINDOW_WIDTH = 650, DEFAULT_WINDOW_HEIGHT = 650, 
  DEFAULT_SIM_WIDTH = 65, DEFAULT_SIM_HEIGHT = 65;
  static constexpr double DEFAULT_TICK_SPEED = 1.0 / 60.0;
  static constexpr char WINDOW_NAME[18] = "Falling Sand Game";
  static constexpr unsigned int NUM_CELLS = 8;

private:
  GLFWwindow *m_Window;
  unsigned int m_Width, m_Height;

  std::unique_ptr<Texture2D> m_CellsTexture;
  std::unique_ptr<ComputeProgram> m_ComputeSim;
  std::unique_ptr<ShaderProgram> m_DisplayProgram;
  std::unique_ptr<VertexArrayObject> m_DrawQuad;

  unsigned int m_SimIterations = 0;
  int m_SimDim[2] = {DEFAULT_SIM_WIDTH, DEFAULT_SIM_HEIGHT}, m_RenderScale[2];

  bool m_MouseDown;
  double m_MousePos[2];

  int m_CellType = 0;

public:
  FallingSand(FallingSand &game) = delete;
  FallingSand(FallingSand &&game) = delete;
  FallingSand(unsigned int windowWidth, unsigned int windowHeight, std::string configPath);
  ~FallingSand();

  void Play();

private:
  void DoInteraction();
  void CreateRenderQuad();
  void SetDimensions(unsigned int width, unsigned int height);
  void LoadConfig(std::string path);
  void CreateWindow();
  void Display();

  // Callbacks
  static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void MouseMoveCallback(GLFWwindow *window, double xpos, double ypos);
  static void MouseDownCallback(GLFWwindow *window, int button, int action, int mods);
  static void WindowResizeCallback(GLFWwindow* window, int width, int height);
};

#endif