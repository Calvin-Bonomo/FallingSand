import Cell

AIR_ID = 0 
SAND_ID = 1

class Particle:
  def __init__(self, id: int):
    self.id = id
  
  def update(self, cell: Cell, pos: int):
    raise NotImplemented

  def get(self) -> int:
    return self.id

class Air(Particle):
  def __init__(self):
    super().__init__(AIR_ID)

  def update(self, cell: Cell, pos: int):
    pass

class Sand(Particle):
  def __init__(self):
    super().__init__(SAND_ID)

  def update(self, cell: Cell, pos: int):
    if pos > 2: 
      pass
    if cell.isEmpty(pos + 2):
      cell.swap((pos, pos + 2))
    elif pos == 0 and cell.isEmpty(3):
      cell.swap((pos, 3))
    elif pos == 1 and cell.isEmpty(2):
      cell.swap((pos, 2))
