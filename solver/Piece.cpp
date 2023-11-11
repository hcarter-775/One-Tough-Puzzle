#include "Piece.h"

Piece::Piece(std::vector<int> edges, int piece_no) 
{
    for (int i = 0; i < 4; i++) 
    {
        this->edges[i] = edges[i];
    }

    this->piece_no = piece_no;

    left_child = -1; 
    right_child = -1;
    left_parent = -1;
    right_parent = -1;

    continue_check = false;
    on_a_liklihood_stack = true;
    on_board = false;
    idx_ptr = 0;
    dir = 1;
}

void Piece::PtrPlus() 
{
    if (idx_ptr == 3) { idx_ptr = 0; }
    else {idx_ptr += 1;}
}

void Piece::PtrMinus() 
{
    if (idx_ptr == 0) { idx_ptr = 3;}
    else {idx_ptr -=1;}
}

void Piece::PtrForward() 
{
    if (dir == 1) { PtrPlus(); }
    else { PtrMinus(); }
}

void Piece::PtrBackward() 
{
    if (dir == 1) { PtrMinus(); }
    else { PtrPlus(); }
}


// getters
int Piece::GetPtrIdx()                       { return idx_ptr; }
int Piece::GetPieceNo()                      { return piece_no; }
int Piece::GetPieceDir()                     { return dir; }
bool Piece::GetOnBoard()                     { return on_board; }
int Piece::GetEdgeValue()                    { return edges[idx_ptr]; }
bool Piece::GetContinueCheck()               { return this->continue_check; }
int Piece::GetPartOfWhichStack()             { return this->part_of_which_stack; }
std::stack<int> Piece::GetCheckedOptions()   { return checked_options; }
std::queue<int> Piece::GetRemainingOptions() { return remaining_options; }

int Piece::GetLeftChild()   { return left_child; }
int Piece::GetRightChild()  { return right_child; }
int Piece::GetLeftParent()  { return left_parent; }
int Piece::GetRightParent() { return right_parent; }

// setters
void Piece::SetPtrIdx(int i)                                       { this->idx_ptr = i; }
void Piece::SetOnBoard(bool ob)                                    { this->on_board = ob; }
void Piece::SetPieceDir(int dir)                                   { this->dir = dir; }
void Piece::SetPartOfWhichStack(int s)                             { this->part_of_which_stack = s; }
void Piece::SetContinueCheck(bool continue_check)                  { this->continue_check = continue_check; }
void Piece::SetCheckedOptions(std::stack<int> checked_options)     { this->checked_options = checked_options; }
void Piece::SetRemainingOptions(std::queue<int> remaining_options) { this->remaining_options = remaining_options; }

void Piece::SetLeftChild(int left_piece)    { left_child = left_piece; }
void Piece::SetLeftParent(int left_piece)   { left_parent = left_piece; }
void Piece::SetRightChild(int right_piece)  { right_child = right_piece; }
void Piece::SetRightParent(int right_piece) { right_parent = right_piece; }


void Piece::SetPlaceHolderInfo(bool fully_checked, std::stack<int> checked, std::queue<int> remainder) 
{
    SetCheckedOptions(checked);
    SetRemainingOptions(remainder);
    SetContinueCheck(fully_checked);
}