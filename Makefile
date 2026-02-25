CXX := g++
CXXFLAGS := -O3
LIBS := -lglfw -lGL -lm -lGLU
objects := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
headers := $(wildcard src/*.hpp)

.PHONY: falling_sand clean

all: falling_sand

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -DDEBUG -c -o $@ $?

falling_sand: $(objects) $(headers)
	$(CXX) $(CXXFLAGS) -o $@ $? $(LIBS)

clean:
	rm -f src/*.o falling_sand
