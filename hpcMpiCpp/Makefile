SRC = $(shell find . -name "*.cpp")
BIN = $(SRC:.cpp=.out)

.PHONY: all clean

all: $(BIN)
	@echo "run with: mpirun -n <nb_thread> <program> [args]"

%.out: %.cpp
	mpic++ -std=c++11 -Wall -Wextra -Wno-literal-suffix -O2 -o $@ $<

clean:
	rm -f $(BIN)
