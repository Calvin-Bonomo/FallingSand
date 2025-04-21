class SwapState:
  def __init__(self, topLeft, topRight, botLeft, botRight):
    self.topLeft: int = topLeft
    self.topRight: int = topRight
    self.botLeft: int = botLeft
    self.botRight: int = botRight

  def get(self) -> int:
    return (self.topLeft << 9) | (self.topRight << 6) | (self.botLeft << 3) | self.botLeft
  
  def __eq__(self, other):
    if isinstance(other, SwapState):
      return self.get() == other.get()
    return False
  