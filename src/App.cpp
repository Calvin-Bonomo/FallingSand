#include "GLFWContext.hpp"
#include "FallingSand.hpp"

int main() {
  GLFWContext::Init();
  FallingSand game(650, 650, "");
  game.Play();
  return 0;
}