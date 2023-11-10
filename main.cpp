#include "solver/SolveOneToughPuzzle.h"

int main()
{ 
    std::vector<Piece> pieces;

    // 1, 2
    int edges0[4] = {0,0,3,1};
    Piece new_piece0(edges0, 0);
    pieces.push_back(new_piece0);

    int edges1[4] = {2,1,1,2};
    Piece new_piece1(edges1, 1);
    pieces.push_back(new_piece1);

    // 3,

    int edges2[4] = {3,2,1,1};
    Piece new_piece2(edges2, 2);
    pieces.push_back(new_piece2);

    // 4,5

    int edges3[4] = {3,2,2,3};
    Piece new_piece3(edges3, 3);
    pieces.push_back(new_piece3);

    int edges4[4] = {1,3,0,3};
    Piece new_piece4(edges4, 4);
    pieces.push_back(new_piece4);

    // 6,7
 
    int edges5[4] = {1, 3, 2, 1};
    Piece new_piece5(edges5, 5);
    pieces.push_back(new_piece5);

    int edges6[4] = {0, 2, 0, 3};
    Piece new_piece6(edges6, 6);
    pieces.push_back(new_piece6);


    // 8, 9

    int edges7[4] = {3,0,0,1};
    Piece new_piece7(edges7, 7);
    pieces.push_back(new_piece7);

    int edges8[4] = {0, 2, 3, 2};
    Piece new_piece8(edges8, 8);
    pieces.push_back(new_piece8);
    
    SolveOneToughPuzzle solver(pieces);
    std::stack<int> solution = solver.BuildSolution();
    solver.PrintSolution(solution);

    return 1;
}