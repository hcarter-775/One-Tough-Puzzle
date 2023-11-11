#include <vector>
#include <queue>
#include <stack>

class Piece {
    public:
        Piece() {}
        Piece(std::vector<int> edges, int piece_no);

        void PtrPlus();         
        void PtrMinus(); 
        void PtrForward();
        void PtrBackward(); 

        // Getters
        int GetPtrIdx();
        int GetPieceNo();
        int GetPieceDir();
        int GetEdgeValue();
        bool GetOnBoard();
        int GetPartOfWhichStack();
        bool GetContinueCheck();
        std::queue<int> GetRemainingOptions();
        std::stack<int> GetCheckedOptions();
        int GetLeftChild();
        int GetRightChild();
        int GetLeftParent();
        int GetRightParent();
        
        // Setters
        void SetPtrIdx(int i);
        void SetPieceDir(int dir);
        void SetOnBoard(bool ob);
        void SetPartOfWhichStack(int s);
        void SetContinueCheck(bool continue_check);
        void SetCheckedOptions(std::stack<int> checked_options);
        void SetRemainingOptions(std::queue<int> remaining_options);
        void SetLeftChild(int left_piece);
        void SetLeftParent(int left_piece);
        void SetRightParent(int right_piece);
        void SetRightChild(int right_piece);
        void SetPlaceHolderInfo(bool fully_checked, std::stack<int> checked, std::queue<int> remainder);

        // will segfault if I add getter/setter for this value
        bool on_a_liklihood_stack;

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
        
        bool on_board;
};