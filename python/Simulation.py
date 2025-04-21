from Cell import Cell
from Particle import *
from SwapState import SwapState

def writeConfig():
  pass

def writeCell(cell: Cell, id: tuple[int, int, int, int]) -> None:
  pass

def main():
  writeConfig()
  for tL in PARTICLE_IDS:
    for tR in PARTICLE_IDS:
      for bL in PARTICLE_IDS:
        for bR in PARTICLE_IDS:
          cell = Cell(makeParticle(tL), makeParticle(tR), makeParticle(bL), makeParticle(bR))
          cell.update()
          writeCell(cell, (tL, tR, bL, bR))

if __name__ == "main":
  main()