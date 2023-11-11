CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

SRC = solver/main.cpp solver/SolveOneToughPuzzle.cpp solver/Piece.cpp
OBJ_DIR = .o
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cpp=.o)))
EXEC = otp_solver

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: solver/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)