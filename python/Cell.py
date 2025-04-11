from Particle import *
import SwapState

class Cell:
  def __init__(self, topLeft: Particle, topRight: Particle, botLeft: Particle, botRight: Particle):
    self.particles = [topLeft, topRight, botLeft, botRight]

  def update(self) -> None:
    for particle in self.particles:
      particle.update(self)

  def swap(self, swap: tuple[int, int]):
    if swap[0] < 0 or swap[0] > 3 or swap[1] < 0 and swap[1] > 3:
      raise RuntimeError
    temp = self.particles[swap[0]]
    self.particles[swap[0]] = self.particles[swap[1]]
    self.particles[swap[1]] = temp
  
  def isEmpty(self, cellNum: int) -> bool:
    return isinstance(self.particles[cellNum], Air)
  
  def getSwapState(self) -> SwapState:
    return SwapState(self.particles[0].get(), self.particles[1].get(), self.particles[2].get(), self.particles[3].get())