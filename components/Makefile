EXE=$(addsuffix .exe, $(basename $(wildcard *.cpp)))
CPPC=g++ -g
CPPC_FLAGS=-Wall -Wextra -pedantic -Ofast -march=native
BOOST_DIR=$(HOME)/CLionProjects/boost_1_77_0

BASE_DIR=$(HOME)/CLionProjects/fmt-simulator

all : $(EXE)
	./test.exe 3

%.exe : %.cpp
	$(CPPC) $(CPPC_FLAGS) -I$(BOOST_DIR) $< -o $@

clean :
	rm -fr $(EXE)
	rm -fr *.txt

.PHONY: all clean

