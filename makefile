CXX = g++
CXXFLAGS = -Wall -pthread # -g # for debugging
LINKERFLAGS = \
	-lcurses \
	-lncurses

main: build/main.o build/GameState.o
	$(CXX) $(CXXFLAGS) -o bin/main build/*.o $(LINKERFLAGS)

build/main.o: src/main.cpp src/GameState.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o build/main.o $(LINKERFLAGS)

build/GameState.o: src/GameState.h
	$(CXX) $(CXXFLAGS) -c src/GameState.cpp -o build/GameState.o $(LINKERFLAGS)
