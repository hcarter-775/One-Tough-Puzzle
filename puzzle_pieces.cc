#include "puzzle_pieces.h"

Piece::Piece(int edges[4], int piece_no) 
{
    this->piece_no = piece_no;
    this->dir = 1;         
    for (int i = 0; i < 4; i++) 
    {
        this->edges[i] = edges[i];
    }

    left_child = -1; 
    right_child = -1;
    left_parent = -1;
    right_parent = -1;

    continue_check = false;
    is_in_a_liklihood_stack = true;
    is_on_board = false;
    idx_ptr = 0;
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

// Getters for Piece
int Piece::GetPtrIdx()        { return idx_ptr; }
int Piece::GetPieceNo()       { return piece_no; }
int Piece::GetPieceDir()      { return dir; }
int Piece::GetEdgeValue()     { return edges[idx_ptr]; }
std::queue<int> Piece::GetRemainingOptions() { return remaining_options; }

// Setters for Piece
void Piece::SetPieceDir(int dir)              { this->dir = dir; }
void Piece::SetRemainingOptions(std::queue<int> remaining_options) { this->remaining_options = remaining_options; }

void Piece::SetLeftChild(int left_piece) { left_child = left_piece; }
void Piece::SetLeftParent(int left_piece) { left_parent = left_piece; }
void Piece::SetRightParent(int right_piece) { right_parent = right_piece; }
void Piece::SetRightChild(int right_piece) { right_child = right_piece; }

int Piece::GetLeftChild() { return left_child; }
int Piece::GetRightChild() { return right_child; }
int Piece::GetLeftParent() { return left_parent; }
int Piece::GetRightParent() { return right_parent; }

void Piece::SetPlaceHolderInfo(bool fully_checked, std::stack<int> checked, std::queue<int> remainder) 
{
    SetCheckedOptions(checked);
    SetRemainingOptions(remainder);
    SetContinueCheck(fully_checked);
}