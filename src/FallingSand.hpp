#pragma once

#include <string>
#include <vector>
#include <memory>

#include "GLFW/glfw3.h"

#include "Buffer.hpp"
#include "GLFWContext.hpp"
#include "ComputeProgram.hpp"

typedef unsigned char cell_t;
typedef unsigned int transition_t;

class FallingSand
{
private: // constants
  static constexpr unsigned int DEFAULT_WINDOW_WIDTH = 600, DEFAULT_WINDOW_HEIGHT = 600, 
  DEFAULT_SIM_WIDTH = 65, DEFAULT_SIM_HEIGHT = 65;
  static constexpr double DEFAULT_TICK_SPEED = 1.0 / 60.0;
  static constexpr char *WINDOW_NAME = "Falling Sand Game";

private:
  GLFWwindow *m_Window;
  unsigned int m_Width, m_Height;
  std::vector<cell_t> m_CellTypes;
  std::unique_ptr<Buffer<cell_t>> m_CellBuffer;
  std::unique_ptr<Buffer<transition_t>> m_TransitionBuffer; // IDK what to do with this
  std::unique_ptr<ComputeProgram> m_ComputeSim;

public:
  FallingSand() = delete;
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
