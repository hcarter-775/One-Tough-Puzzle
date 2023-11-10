CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

SRC = main.cpp SolveOneToughPuzzle.cpp Piece.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = otp_solver

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)