SRC = $(shell ls src/*.cpp)
BIN = $(SRC:.cpp=.out)

PKGS = opencv
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 `pkg-config --cflags $(PKGS)`
LIBS = `pkg-config --libs $(PKGS)`

.PHONY: all clean

all: $(BIN)

%.out: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(BIN)
