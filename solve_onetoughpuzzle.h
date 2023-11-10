#include "puzzle_pieces.h"
#include <utility>
#include <math.h>

enum head_in_use { left, right, left_diag, right_diag };

class SolveOneToughPuzzle {
    public:
        
        // initialization function
        SolveOneToughPuzzle(std::vector<Piece> pieces);

        // Check Edges on Pieces
        int CheckEdgeEdge(Piece pw_edge1, Piece pw_edge2);
        int CheckInnerEdges(Piece left_edge, Piece right_edge, Piece* piece_w);
        std::pair<int,int> CheckOuterEdge(Piece pw_edge, Piece* piece_w);

        // Connect and Disconnect Inner and Outer Pieces
        void ConnectOuterPieces(Piece* child, bool continue_check, std::queue<int> remaining);
        void DisconnectOuterPieces(Piece* child);
        void ConnectInnerPieces(Piece* child, std::queue<int> remaining);
        void DisconnectInnerPieces(Piece* child);

        // Sorting the pieces by number of viable outer corners
        void SortPiecesIntoStacks();
        
        // Setting the e0 position
        void SetE0Idx(int i);

        // Build the solution
        std::stack<int> BuildSolution();

        // Uses the for loops below to make a queue
        // Uses the LocationType f() as well
        std::queue<int> SetOptimalQueue(int depth);

        // Returns 0 if corner, 1 if side, 2 if inside
        int GetNextPieceLocationType(int depth);

        // These are a bunch of for loops
        std::queue<int> SetOptimalQueue_Corner();
        std::queue<int> SetOptimalQueue_Side();
        std::queue<int> SetOptimalQueue_Inner();

        // Clearing info back onto liklihood stacks
        void ClearRemaining(std::queue<int>* remaining, int curr_p_no);
        void ClearCurrentlyChecked(int curr_p_no);
        void PushToLikelihoodStack(int p_no, int stack_num);

        // Prints and returns the ordered solution
        void PrintSolution(std::stack<int> solution);
        
    private:
        std::vector<Piece> pieces;
        std::stack<int> currently_checked;
        std::stack<int> current_board;

        std::stack<int> failed_corner_pieces;
        std::stack<int> likely_corner_pieces;
        std::stack<int> likely_side_pieces;
        std::stack<int> likely_inner_pieces;

        std::stack<int> ld_heads;
        std::stack<int> rd_heads;

        Piece* l_head;
        Piece* r_head;
        Piece* ld_head;
        Piece* rd_head;

        int l_depth;
        int r_depth;
        int board_side_length;

        head_in_use curr_head;
};