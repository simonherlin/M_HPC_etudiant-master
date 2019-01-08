SRC = $(shell ls *.cpp)
BIN = $(SRC:.cpp=.out)

CXXFLAGS += -std=c++11 -Wall -Wextra -Wno-ignored-attributes `pkg-config --cflags opencv` 
LIBS += -lOpenCL -fopenmp `pkg-config --libs opencv`

ifeq ($(DEBUG), 1)
	override CXXFLAGS += -O0 -g -DDEBUG
	export AMD_OCL_BUILD_OPTIONS="-g -O0"
else
	override CXXFLAGS += -O2 -DNDEBUG
	export AMD_OCL_BUILD_OPTIONS="-O2"
endif

MESSAGE = "make options: DEBUG=1"

all: $(BIN)

%.out: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS)
	@echo $(MESSAGE)

.PHONY: clean

clean:
	rm $(BIN)
	@echo $(MESSAGE)

