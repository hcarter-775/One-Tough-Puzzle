CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

SRC = main.cpp SolveOneToughPuzzle.cpp Piece.cpp
OBJ_DIR = o_files
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cpp=.o)))
EXEC = otp_solver

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(EXEC)