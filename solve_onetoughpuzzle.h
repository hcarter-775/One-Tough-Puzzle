#include "puzzle_pieces.h"
#include <utility>
#include <math.h>

enum head_in_use { left, right, left_diag, right_diag };

class SolveOneToughPuzzle {
    public:
        
        // initialization function
        SolveOneToughPuzzle(Piece pieces[9]);

        // Check Edges on Pieces
        int CheckEdgeEdge(Piece pw_edge1, Piece pw_edge2);
        
        // if fail, should return piece_w idx to 0. else, should leave it where it is.
        int CheckInnerEdges(Piece left_edge, Piece right_edge, Piece* piece_w);

        // if fail, should return piece_w idx to 0. else, should leave it where it is
        // isFullyChecked should be changed to needs_further_check
        std::pair<int,int> CheckOuterEdge(Piece pw_edge, Piece* piece_w);

        // Connect and Disconnect Inner and Outer Pieces
        void ConnectOuterPieces(Piece* child, bool continue_check, std::queue<int> remaining);
        void DisconnectOuterPieces(Piece* child);
        void ConnectInnerPieces(Piece* child, std::queue<int> remaining);

        // should pop piece back onto its stack
        void DisconnectInnerPieces(Piece* child);

        // sorting the pieces by number of viable outer corners
        void SortPiecesIntoStacks();
        
        // setting the e0 position
        void SetE0Idx(int i);

        // build the solution
        std::stack<int> BuildSolution();

        // uses the for loops below to make a queue
        // uses the LocationType f() as well
        std::queue<int> SetOptimalQueue(int depth);

        // returns 0 if corner, 1 if side, 2 if inside
        int GetNextPieceLocationType(int depth);

        // These are a bunch of for loops
        std::queue<int> SetOptimalQueue_Corner();
        std::queue<int> SetOptimalQueue_Side();
        std::queue<int> SetOptimalQueue_Inner();

        void clear_remaining(std::queue<int>* remaining, int curr_p_no)
        {
            // std::cout << "clearing remaining: " << remaining->size() << "\n";

            int p_no; int s_no;
            while (!remaining->empty())
            {
                p_no = pieces[remaining->front()].GetPieceNo();
                s_no = pieces[remaining->front()].GetPartOfWhichStack();
                // std::cout << "attempting to push: " << p_no << " curr_p_no: " << curr_p_no << "\n";

                if ((!pieces[p_no].is_in_a_liklihood_stack) && !pieces[p_no].is_on_board && (p_no != curr_p_no))
                {
                    PushToLikelihoodStack(p_no, s_no);
                }
                remaining->pop();
            }
        }

        void clear_currently_checked(int curr_p_no) 
        {
            while (!currently_checked.empty())
            {
                int p_no = pieces[currently_checked.top()].GetPieceNo();
                int s_no = pieces[currently_checked.top()].GetPartOfWhichStack();
                // std::cout << "attempting to push: " << p_no << " curr_p_no: " << curr_p_no << "\n";

                if ((!pieces[p_no].is_in_a_liklihood_stack) && (!pieces[p_no].is_on_board) && (p_no != curr_p_no))
                {
                    PushToLikelihoodStack(p_no, s_no);
                }                
                currently_checked.pop();
            }
        }

        void PushToLikelihoodStack(int p_no, int stack_num)
        {
            // std::cout << "pushed: " << p_no << "\n";
            pieces[p_no].is_in_a_liklihood_stack = true;
            if (stack_num == 0)
            {
                likely_corner_pieces.push(p_no);
            }
            else if (stack_num == 1)
            {
                likely_side_pieces.push(p_no);
            }
            else if (stack_num == 2)
            {
                likely_inner_pieces.push(p_no);
            } 
            else if (stack_num == 3)
            {
                failed_corner_pieces.push(p_no);
            }
        }
        
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