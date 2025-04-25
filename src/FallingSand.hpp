#pragma once

#include "GLFW/glfw3.h"

#include "Buffer.hpp"
#include "GLFWContext.hpp"
#include "ComputeProgram.hpp"
#include "ShaderProgram.hpp"
#include "VertexArrayObject.hpp"
#include "TextureBuffer.hpp"

#include <string>
#include <vector>
#include <memory>

typedef unsigned char cell_t;
typedef unsigned short transition_t;

class FallingSand
{
private: // constants
  static constexpr unsigned int DEFAULT_WINDOW_WIDTH = 650, DEFAULT_WINDOW_HEIGHT = 650, 
  DEFAULT_SIM_WIDTH = 65, DEFAULT_SIM_HEIGHT = 65;
  static constexpr double DEFAULT_TICK_SPEED = 1.0 / 60.0;
  static constexpr char WINDOW_NAME[18] = "Falling Sand Game";

private:
  GLFWwindow *m_Window;
  unsigned int m_Width, m_Height;
  std::vector<cell_t> m_CellTypes;

  std::unique_ptr<Buffer> m_CellBuffer;
  std::unique_ptr<Buffer> m_TransitionBuffer; // IDK what to do with this
  std::unique_ptr<TextureBuffer> m_SimSpaceTexture;
  std::unique_ptr<ComputeProgram> m_ComputeSim;
  std::unique_ptr<ShaderProgram> m_DisplayProgram;
  std::unique_ptr<VertexArrayObject> m_DrawQuad;

  unsigned int m_SimIterations;
  int m_SimDim[2] = {DEFAULT_SIM_WIDTH, DEFAULT_SIM_HEIGHT}, m_RenderScale[2];

  bool m_MouseDown;
  double m_MousePos[2];

public:
  FallingSand(FallingSand &game) = delete;
  FallingSand(FallingSand &&game) = delete;
  FallingSand(unsigned int windowWidth, unsigned int windowHeight, std::string configPath);
  ~FallingSand();

  void Play();
private:
  void LoadConfig(std::string path);
  void CreateWindow();
  void Display();

  // Callbacks
  static void KeyPressCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void MouseMoveCallback(GLFWwindow *window, double xpos, double ypos);
  static void MouseDownCallback(GLFWwindow *window, int button, int action, int mods);
  static void WindowResizeCallback(GLFWwindow* window, int width, int height);
};
