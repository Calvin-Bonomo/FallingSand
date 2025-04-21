from Particle import Particle
from SwapState import SwapState

class Cell:
  def __init__(self, topLeft: Particle, topRight: Particle, botLeft: Particle, botRight: Particle):
    self.particles = [topLeft, topRight, botLeft, botRight]

  def update(self) -> None:
    for particle in self.particles:
      particle.update(self)

  def swap(self, swap: tuple[int, int]) -> None:
    if swap[0] < 0 or swap[0] > 3 or swap[1] < 0 and swap[1] > 3:
      raise RuntimeError
    temp = self.particles[swap[0]]
    self.particles[swap[0]] = self.particles[swap[1]]
    self.particles[swap[1]] = temp
  
  def getCell(self) -> tuple[int, int, int, int]:
    return (self.particles[0].get(), self.particles[1].get(), self.particles[2].get(), self.particles[3].get())
  
  def setCell(self, cellNum: int, particle: Particle) -> int:
    self.particles[cellNum] = particle
  
  def getSwapState(self) -> SwapState:
    return SwapState(self.particles[0].get(), self.particles[1].get(), self.particles[2].get(), self.particles[3].get())