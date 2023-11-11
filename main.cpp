#include "solver/SolveOneToughPuzzle.h"

std::vector<Piece> TxtFileToPiecesVector() {
    
    std::vector<Piece> pieces;
    const std::string file_path = "pieces.txt";

    try {
        std::ifstream inputFile(file_path);

        if (!inputFile.is_open()) {
            std::cerr << "Error opening file: " << file_path << std::endl;
            return pieces;
        }

        std::string line;
        std::vector<int> edges;
        int k = 0;
        while (std::getline(inputFile, line)) {
            edges.push_back(line[0] - 48);
            edges.push_back(line[2] - 48);
            edges.push_back(line[4] - 48);
            edges.push_back(line[6] - 48);
            pieces.push_back(Piece(edges,k));
            edges.clear();
            k += 1;
        }

        inputFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return pieces;
    }

    return pieces;
}


int main()
{
    std::vector<Piece> pieces = TxtFileToPiecesVector();
    SolveOneToughPuzzle solver(pieces);
    std::stack<int> solution = solver.BuildSolution();
    solver.PrintSolution(solution);
    return 1;
}