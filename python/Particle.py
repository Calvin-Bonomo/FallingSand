from Cell import Cell

AIR_ID = 0 
SAND_ID = 1
WATER_ID = 2
SMOKE_ID = 3
WALL_ID = 4
OIL_ID = 5
WOOD_ID = 6
FIRE_ID = 7

PARTICLE_IDS = [AIR_ID, SAND_ID, WATER_ID, SMOKE_ID, WALL_ID, OIL_ID, WOOD_ID, FIRE_ID]

GAS_IDS = [AIR_ID, SMOKE_ID]

LIQUID_IDS = [WATER_ID, OIL_ID]

SOLID_IDS = [SAND_ID, WALL_ID, WOOD_ID]

FLAMMABLE_IDS = [OIL_ID, WOOD_ID]

class Particle:
  def __init__(self, id: int):
    self.id = id
  
  def update(self, cell: Cell, pos: int) -> None:
    raise NotImplementedError

  def get(self) -> int:
    return self.id

class Air(Particle):
  def __init__(self):
    super().__init__(AIR_ID)

  def update(self, cell: Cell, pos: int) -> None:
    pass

class Sand(Particle):
  def __init__(self):
    super().__init__(SAND_ID)

  def update(self, cell: Cell, pos: int) -> None:
    if pos > 2: 
      pass
    (_, _, bl, br) = cell.getCell()
    if pos == 0:
      if bl in LIQUID_IDS or bl in GAS_IDS:
        cell.swap(0, 2)
      elif br in LIQUID_IDS or br in GAS_IDS:
        cell.swap(0, 3)
    elif pos == 1:
      if br in LIQUID_IDS or br in GAS_IDS:
        cell.swap(1, 3)
      elif bl in LIQUID_IDS or bl in GAS_IDS:
        cell.swap(1, 2)

class Water(Particle):
  def __init__(self):
    super().__init__(WATER_ID)
  
  def update(self, cell: Cell, pos: int) -> None:
    (tl, tr, bl, br) = cell.getCell()
    if pos == 0:
      if br in GAS_IDS or br == WATER_ID:
        cell.swap((pos, 3))
      elif bl in GAS_IDS or bl == WATER_ID:
        cell.swap((pos, 2))
      elif tr in GAS_IDS:
        cell.swap((pos, 1))
    elif pos == 1:
      if bl in GAS_IDS or bl == WATER_ID:
        cell.swap((pos, 3))
      elif br in GAS_IDS or br == WATER_ID:
        cell.swap((pos, 2))
      elif tl in GAS_IDS:
        cell.swap((pos, 0))
    elif pos == 2:
      if br in GAS_IDS:
        cell.swap((pos, 3))
    elif pos == 3:
      if bl in GAS_IDS:
        cell.swap((pos, 2))

class Smoke(Particle):
  def __init__(self):
    super().__init__(SMOKE_ID)
  
  def update(self, cell: Cell, pos: int) -> None:
    (tl, tr, bl, br) = cell.getCell()
    if pos == 2:
      if tl == AIR_ID:
        cell.swap((pos, 0))
      elif tr == AIR_ID:
        cell.swap((pos, 1))
      elif br == AIR_ID:
        cell.swap((pos, 3))
    elif pos == 3:
      if tr == AIR_ID:
        cell.swap((pos, 1))
      elif tl == AIR_ID:
        cell.swap((pos, 0))
      elif bl == AIR_ID:
        cell.swap((pos, 2))

class Wall(Particle):
  def __init__(self):
    super().__init__(WALL_ID)
  
  def update(self, cell: Cell, pos: int) -> None:
    pass

class Oil(Particle):
  def __init__(self):
    super().__init__(OIL_ID)
  
  def update(self, cell: Cell, pos: int) -> None:
    (tl, tr, bl, br) = cell.getCell()
    if pos == 0:
      if bl in GAS_IDS:
        cell.swap((pos, 2))
      elif br in GAS_IDS:
        cell.swap((pos, 3))
      elif tr in GAS_IDS:
        cell.swap((pos, 1))
    elif pos == 1:
      if br in GAS_IDS:
        cell.swap((pos, 3))
      elif bl in GAS_IDS:
        cell.swap((pos, 2))
      elif tl in GAS_IDS:
        cell.swap((pos, 0))
    elif pos == 2:
      if br in GAS_IDS:
        cell.swap((pos, 3))
    elif pos == 3:
      if bl in GAS_IDS:
        cell.swap((pos, 2))

class Wood(Particle):
  def __init__(self):
    super().__init__(WOOD_ID)
  
  def update(self, cell: Cell, pos: int) -> None:
    pass

class Fire(Particle):
  def __init__(self):
    super().__init__(FIRE_ID)
  
  def update(self, cell: Cell, pos: int) -> None:
    (tl, tr, bl, br) = cell.getCell()
    if pos == 0:
      if tr in FLAMMABLE_IDS:
        cell.setCell(1, Fire())
      elif bl in FLAMMABLE_IDS:
        cell.setCell(2, Fire())
      elif tr in GAS_IDS and bl in GAS_IDS:
        cell.setCell(0, Smoke())
    elif pos == 1:
      if tl in FLAMMABLE_IDS:
        cell.setCell(0, Fire())
      elif br in FLAMMABLE_IDS:
        cell.setCell(3, Fire())
      elif tl in GAS_IDS and br in GAS_IDS:
        cell.setCell(1, Smoke())
    elif pos == 2:
      if tl in FLAMMABLE_IDS:
        cell.setCell(0, Fire())
      elif br in FLAMMABLE_IDS:
        cell.setCell(3, Fire())
      elif tl in GAS_IDS and bl in GAS_IDS:
        cell.setCell(2, Smoke())
    elif pos == 3:
      if tr in FLAMMABLE_IDS:
        cell.setCell(1, Fire())
      elif bl in FLAMMABLE_IDS:
        cell.setCell(2, Fire())
      elif tr in GAS_IDS and bl in GAS_IDS:
        cell.setCell(3, Smoke())

def makeParticle(id: int) -> Particle:
  match id:
    case 0: # AIR_ID
      return Air()
    case 1: # SAND_ID
      return Sand()
    case 2: # WATER_ID
      return Water()
    case 3: # SMOKE_ID
      return Smoke()
    case 4: # WALL_ID
      return Wall()
    case 5: # OIL_ID
      return Oil()
    case 6: # WOOD_ID
      return Wood()
    case 7: # FIRE_ID
      return Fire()
    case _:
      raise NotImplementedError