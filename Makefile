CXX := g++
CXXFLAGS := 
LIBS := -lglfw -lGL -lm -lGLU
objects := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
headers := $(wildcard src/*.hpp)

.PHONY: final

all: final

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -DDEBUG -c -o $@ $?

final: $(objects) $(headers)
	$(CXX) $(CXXFLAGS) -o $@ $? $(LIBS)

clean:
	rm -f src/*.o final