#include <vector>
#include <queue>
#include <stack>
#include <iostream>

class Piece {
    public:
        Piece() {}
        Piece(int edges[4], int piece_no);

        void PtrPlus();         
        void PtrMinus(); 
        void PtrForward();
        void PtrBackward(); 

        int GetPtrIdx();
        int GetPieceNo();
        int GetPieceDir();
        int GetEdgeValue();
        std::queue<int> GetRemainingOptions();
        int GetPartOfWhichStack()                               { return this->part_of_which_stack; }

        bool GetContinueCheck()                                 { return this->continue_check; }

        void SetPtrIdx(int i) { this->idx_ptr = i; }
        void SetPieceDir(int dir);
        void SetRemainingOptions(std::queue<int> remaining_options);
        void SetContinueCheck(bool continue_check)              { this->continue_check = continue_check; }
        void SetPartOfWhichStack(int s)                         { this->part_of_which_stack = s; }
        void SetCheckedOptions(std::stack<int> checked_options) { this->checked_options = checked_options; }
        std::stack<int> GetCheckedOptions() { return checked_options; }


        void SetLeftChild(int left_piece);
        void SetLeftParent(int left_piece);
        void SetRightParent(int right_piece);
        void SetRightChild(int right_piece);

        int GetLeftChild();
        int GetRightChild();
        int GetLeftParent();
        int GetRightParent();

        void SetPlaceHolderInfo(bool fully_checked, std::stack<int> checked, std::queue<int> remainder);

        bool is_in_a_liklihood_stack;
        bool is_on_board;

    private:
        // [0, 1] <- order checked for top pieces. 
        // [3, 2] <- order checked for bottom pieces
        int edges[4]; 
        
        int left_child;
        int right_child;
        int left_parent;
        int right_parent;
        
        std::queue<int> remaining_options;
        std::stack<int> checked_options;

        int dir;
        int idx_ptr;
        int piece_no;
        bool continue_check;
        int part_of_which_stack;
};