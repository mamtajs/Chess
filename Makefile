PATH = /Users/mshah/Desktop/Wave
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

all: Board

Board: Board.cpp Piece.cpp Board.h Piece.h
	$(CXX) $(CXXFLAGS) -o chess $(PATH)/Board.cpp $(PATH)/Piece.cpp

clean:
	rm $(PATH)/chess