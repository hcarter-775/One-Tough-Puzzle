#include "SolveOneToughPuzzle.h"

float sqrt(float n) {
    
    float x = n / 2.0;
    for (int i = 0; i < 5; ++i) 
    {
        x = 0.5 * (x + (n / x));
    }
    return x;
}

// Initializer
SolveOneToughPuzzle::SolveOneToughPuzzle(std::vector<Piece> pieces) 
{
    for (int i = 0; i < pieces.size(); i++) 
    {
        this->pieces.push_back(pieces[i]);
    }

    board_side_length = (int) sqrt(this->pieces.size());

    l_head = nullptr;
    r_head = nullptr;
    ld_head = nullptr;
    rd_head = nullptr;

    l_depth = 0;
    r_depth = 0;

    SortPiecesIntoStacks();
}

// Sorts all of the Pieces into stacks 
void SolveOneToughPuzzle::SortPiecesIntoStacks()
{
    int I0 = 0; int I1 = 0; int I2 = 0; int I3 = 0; // interior
    int E0 = 0; int E1 = 0; int E2 = 0; int E3 = 0; // exterior
    int T0 = 0; int T1 = 0; int T2 = 0; int T3 = 0; 

    for (int i=0;i<pieces.size();i++)
    {
        for (int j=0;j<2;j++)
        {
            if (pieces[i].GetEdgeValue() == 0) { E0 += 1; }
            else if (pieces[i].GetEdgeValue() == 1) { E1 += 1; }
            else if (pieces[i].GetEdgeValue() == 2) { E2 += 1; }
            else if (pieces[i].GetEdgeValue() == 3) { E3 += 1; }
            pieces[i].PtrForward();
        }

        for (int j=0;j<2;j++)
        {
            if (pieces[i].GetEdgeValue() == 0) { I0 += 1; }
            else if (pieces[i].GetEdgeValue() == 1) { I1 += 1; }
            else if (pieces[i].GetEdgeValue() == 2) { I2 += 1; }
            else if (pieces[i].GetEdgeValue() == 3) { I3 += 1; }
            pieces[i].PtrForward();
        }
    }

    T0 = E0 - I0; 
    T1 = E1 - I1;
    T2 = E2 - I2;
    T3 = E3 - I3;

    for (int i=0;i<pieces.size();i++)
    {
        int outer = 0;

        for (int j=0;j<2;j++)
        {
            if (pieces[i].GetEdgeValue() == 0) { if (T0 > 0) { outer += 1; } }
            else if (pieces[i].GetEdgeValue() == 1) { if (T1 > 0) { outer += 1; } }
            else if (pieces[i].GetEdgeValue() == 2) { if (T2 > 0) { outer += 1; } }
            else if (pieces[i].GetEdgeValue() == 3) { if (T3 > 0) { outer += 1; } }
            pieces[i].PtrForward();
        }

        for (int j=0;j<2;j++)
        {
            if (pieces[i].GetEdgeValue() == 0) { if (T0 < 0) { outer += 1; } }
            else if (pieces[i].GetEdgeValue() == 1) { if (T1 < 0) { outer += 1; } }
            else if (pieces[i].GetEdgeValue() == 2) { if (T2 < 0) { outer += 1; } }
            else if (pieces[i].GetEdgeValue() == 3) { if (T3 < 0) { outer += 1; } }
            pieces[i].PtrForward();
        }

        if (outer == 0) { pieces[i].SetPartOfWhichStack(2); }
        else if (outer == 1) { pieces[i].SetPartOfWhichStack(2); }
        else if (outer == 2) { pieces[i].SetPartOfWhichStack(1); }
        else if (outer == 3) { pieces[i].SetPartOfWhichStack(1); }
        else if (outer == 4) { pieces[i].SetPartOfWhichStack(0); }

    }

    for (int i=0;i<pieces.size();i++)
    {
        if (pieces[i].GetPartOfWhichStack() == 0)
        {
            likely_corner_pieces.push(pieces[i].GetPieceNo());
        }
        else if (pieces[i].GetPartOfWhichStack() == 1)
        {
            likely_side_pieces.push(pieces[i].GetPieceNo());
        }
        else if (pieces[i].GetPartOfWhichStack() == 2)
        {
            likely_inner_pieces.push(pieces[i].GetPieceNo());
        }
    }
}


// Check Edges on Pieces
int SolveOneToughPuzzle::CheckEdgeEdge(Piece pw_edge1, Piece pw_edge2)
{
    int edge_no1 = pw_edge1.GetEdgeValue();
    int edge_no2 = pw_edge2.GetEdgeValue();
    if (edge_no1 == edge_no2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int SolveOneToughPuzzle::CheckInnerEdges(Piece left_edge, Piece right_edge, Piece* piece_w)
{
    int el = left_edge.GetPtrIdx();
    int er = right_edge.GetPtrIdx();

    int vl = left_edge.GetEdgeValue();
    int vr = right_edge.GetEdgeValue();

    if (el == 0 || el == 1)
    {
        if (er == 0 || er == 1)
        {
            piece_w->SetPtrIdx(3);
            int wr = piece_w->GetEdgeValue();
            piece_w->PtrBackward();
            int wl = piece_w->GetEdgeValue();
            if ((wl == vl) && (wr == vr)) { return 1; }
            else { piece_w->SetPtrIdx(0); }   
        }
        else if (er == 2 || er == 3)
        {
            piece_w->SetPtrIdx(0);
            int wr = piece_w->GetEdgeValue();
            piece_w->PtrBackward();
            int wl = piece_w->GetEdgeValue();
            if ((wl == vl) && (wr == vr)) { return 1; }
            else { piece_w->SetPtrIdx(0); }   
        }
    }
    else if (el == 2 || el == 3)
    {
        if (er == 0 || er == 1)
        {
            piece_w->SetPtrIdx(2);
            int wr= piece_w->GetEdgeValue();
            piece_w->PtrBackward();
            int wl = piece_w->GetEdgeValue();
            if ((wl == vl) && (wr == vr)) { return 1; }
            else { piece_w->SetPtrIdx(0); }   
        }
        else if (er == 2 || er == 3)
        {
            piece_w->SetPtrIdx(1);
            int wr = piece_w->GetEdgeValue();
            piece_w->PtrBackward();
            int wl = piece_w->GetEdgeValue();
            if ((wl == vl) && (wr == vr)) { return 1; } 
            else { piece_w->SetPtrIdx(0); }   
        }
    }
    return 0;
}

std::pair<int,int> SolveOneToughPuzzle::CheckOuterEdge(Piece pw_edge, Piece* piece_w)
{
    int i = pw_edge.GetPtrIdx();
    if (i == 0 || i == 1)
    {
        if (piece_w->GetContinueCheck())
        {
            piece_w->SetContinueCheck(false);
            piece_w->SetPtrIdx(2); // 3 back to 2 
            if (CheckEdgeEdge(pw_edge, *piece_w)) 
            {
                return std::make_pair(1,0);
            }
        }
        else
        {
            piece_w->SetPtrIdx(3); // 0 back to 3
            if (CheckEdgeEdge(pw_edge, *piece_w)) 
            {
                return std::make_pair(1,1);
            }
            piece_w->SetPtrIdx(2); // 3 back to 2
            if (CheckEdgeEdge(pw_edge, *piece_w)) 
            {
                return std::make_pair(1,0);
            }
        }
    }
    else if (i == 2 || i == 3)
    {
        if (piece_w->GetContinueCheck())
        {
            piece_w->SetContinueCheck(false);
            piece_w->SetPtrIdx(1);
            if (CheckEdgeEdge(pw_edge, *piece_w)) 
            {
                return std::make_pair(1,0);
            }
        }
        else 
        {
            if (CheckEdgeEdge(pw_edge, *piece_w)) 
            {
                return std::make_pair(1,1);
            }
            piece_w->PtrForward(); // 0 to 1
            if (CheckEdgeEdge(pw_edge, *piece_w)) 
            {
                return std::make_pair(1,0);
            }
        }
    }
    piece_w->SetPtrIdx(0);
    return std::make_pair(0,0); // no connection found.
}



// Connecting and Disconnecting the Inner and Outer Pieces
void SolveOneToughPuzzle::ConnectOuterPieces(Piece* child, bool continue_check, std::queue<int> remaining)
{
    // connecting pointers
    if (curr_head == left || curr_head == left_diag)
    {
        l_head->SetLeftChild(child->GetPieceNo());
        child->SetRightParent(l_head->GetPieceNo());

        // set l_head, l_head increment, increment l_depth;
        l_head->PtrForward();
        l_head = child;
        ld_head = child;
        l_depth += 1;
    }
    else if (curr_head == right || curr_head == right_diag)
    {
        
        r_head->SetRightChild(child->GetPieceNo());
        child->SetLeftParent(r_head->GetPieceNo());

        // set dir
        child->SetPieceDir(-1);

        // set r_head, r_head increment, increment r_depth;
        r_head->PtrForward();
        r_head = child;
        rd_head = child;
        r_depth += 1;
    }

    // increment child
    child->PtrForward();

    // pushing to board
    current_board.push(child->GetPieceNo());
    child->SetOnBoard(true);

    // setting information
    child->SetPlaceHolderInfo(continue_check, currently_checked, remaining);
    ClearCurrentlyChecked(child->GetPieceNo());
    ClearRemaining(&remaining, child->GetPieceNo());
}

void SolveOneToughPuzzle::DisconnectOuterPieces(Piece* child)
{
    // disconnecting pointers
    if (curr_head == left || curr_head == left_diag)
    {
        // set l_head
        l_head = &pieces[child->GetRightParent()];
        ld_head = &pieces[ld_heads.top()];
        child->SetRightParent(-1);
        l_head->SetLeftChild(-1);

        l_depth -= 1;
        if (current_board.size() != 1)
        {
            l_head->PtrBackward();
        }

    }
    else if (curr_head == right || curr_head == right_diag)
    {
        // set r_head
        r_head = &pieces[child->GetLeftParent()];
        rd_head = &pieces[rd_heads.top()];

        child->SetLeftParent(-1);
        r_head->SetRightChild(-1);


        r_depth -= 1;
        r_head->PtrBackward();
    }

    // set dir and idx
    child->SetPieceDir(1);
    child->SetPtrIdx(0);

    // popping from board
    if (!pieces[current_board.top()].GetContinueCheck())
    {
        int p_no = pieces[current_board.top()].GetPieceNo();
        // int s_no = pieces[current_board.top()].GetPartOfWhichStack();
        // PushToLikelihoodStack(p_no, s_no);
        currently_checked.push(p_no);
    }
    pieces[current_board.top()].SetOnBoard(false);
    current_board.pop();

}

void SolveOneToughPuzzle::ConnectInnerPieces(Piece* child, std::queue<int> remaining)
{
    // connecting pointers
    int c_no = child->GetPieceNo();
    if (curr_head == left_diag)
    {
        child->SetLeftParent(ld_head->GetPieceNo());
        child->SetRightParent(pieces[ld_head->GetRightParent()].GetRightChild());
        pieces[pieces[ld_head->GetRightParent()].GetRightChild()].SetLeftChild(c_no);
        ld_head->SetRightChild(c_no);

        // increment ptr
        ld_head->PtrForward();
        pieces[pieces[ld_head->GetRightParent()].GetRightChild()].PtrForward();

        // set ld_head
        ld_head = child;
        ld_head->PtrForward();
        ld_head->PtrForward();
    }
    else if (curr_head == right_diag)
    {
        child->SetRightParent(rd_head->GetPieceNo());
        child->SetLeftParent(pieces[rd_head->GetLeftParent()].GetLeftChild());
        pieces[pieces[rd_head->GetLeftParent()].GetLeftChild()].SetRightChild(c_no);
        rd_head->SetLeftChild(c_no);

        // icnrement ptr
        rd_head->PtrForward();
        pieces[pieces[rd_head->GetLeftParent()].GetLeftChild()].PtrForward();

        // set dir
        child->SetPieceDir(-1);

        // set rd_head
        rd_head = child;
        rd_head->PtrForward();
        // rd_head->PtrForward();
    }

    // // increment child
    // child->PtrForward();

    // pushing to board
    current_board.push(c_no);
    pieces[c_no].SetOnBoard(true);

    // setting information
    child->SetPlaceHolderInfo(true, currently_checked, remaining);
    ClearCurrentlyChecked(c_no);
    ClearRemaining(&remaining, c_no);
}

void SolveOneToughPuzzle::DisconnectInnerPieces(Piece* child)
{
    // disconnecting pointers
    if (curr_head == left_diag)
    {
        int parent_right = child->GetRightParent();
        
        child->SetRightParent(-1);
        child->SetLeftParent(-1);
        ld_head->SetRightChild(-1);
        pieces[parent_right].SetLeftChild(-1);

        // decrement parents
        ld_head->PtrBackward();
        pieces[parent_right].PtrBackward();
    }
    else if (curr_head == right_diag)
    {
        int parent_left = child->GetLeftParent();

        child->SetRightParent(-1);
        child->SetLeftParent(-1);
        pieces[parent_left].SetRightChild(-1);
        rd_head->SetLeftChild(-1);

        // decrement parents
        pieces[parent_left].PtrBackward();
        rd_head->PtrBackward();
    }

    // set dir and idx
    child->SetPieceDir(1);
    child->SetPtrIdx(0);

    // popping from board
    currently_checked.push(current_board.top());
    pieces[current_board.top()].SetOnBoard(false);
    current_board.pop();
}


// Clearing info back onto liklihood stacks
void SolveOneToughPuzzle::PushToLikelihoodStack(int p_no, int stack_num)
{
    pieces[p_no].on_a_liklihood_stack = true;
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

void SolveOneToughPuzzle::ClearCurrentlyChecked(int curr_p_no) 
{
    while (!currently_checked.empty())
    {
        int p_no = pieces[currently_checked.top()].GetPieceNo();
        int s_no = pieces[currently_checked.top()].GetPartOfWhichStack();

        if ((!pieces[p_no].on_a_liklihood_stack) && (!pieces[p_no].GetOnBoard()) && (p_no != curr_p_no))
        {
            PushToLikelihoodStack(p_no, s_no);
        }                
        currently_checked.pop();
    }
}

void SolveOneToughPuzzle::ClearRemaining(std::queue<int>* remaining, int curr_p_no)
{
    int p_no; int s_no;
    while (!remaining->empty())
    {
        p_no = pieces[remaining->front()].GetPieceNo();
        s_no = pieces[remaining->front()].GetPartOfWhichStack();

        if ((!pieces[p_no].on_a_liklihood_stack) && !pieces[p_no].GetOnBoard() && (p_no != curr_p_no))
        {
            PushToLikelihoodStack(p_no, s_no);
        }
        remaining->pop();
    }
}

// setting the e0 position
void SolveOneToughPuzzle::SetE0Idx(int i)
{
    if (l_head->GetPtrIdx() != 0)
    {
        l_head->SetPtrIdx(0);
    }

    if (i == 0)
    {
        // do nothing
    }
    else if (i == 1)
    {
        l_head->SetPtrIdx(2);
    }
    else if (i == 2)
    {
        l_head->SetPtrIdx(1);
    }
    else if (i == 3)
    {
        l_head->SetPtrIdx(3);
    }
}

// build the solution
std::stack<int> SolveOneToughPuzzle::BuildSolution()
{

    // initialize all variables at the start (for goto to work)
    std::queue<int> rq; std::queue<int> rdq; std::queue<int> lq; std::queue<int> ldq;
    int prev_r_depth; int prev_l_depth; int rdq_front; int ldq_front;
    bool right_diag_checks_complete; bool left_diag_checks_complete;
    bool l_branch_is_failed; bool r_branch_is_failed;
    bool rd_branch_is_failed; bool ld_branch_is_failed; std::pair<int,int> checked_piece_info;
    int is_connected; bool use_remaining_options; std::queue<int> eoq;       

    // f() begins
    eoq = SetOptimalQueue(0);

    // originally a while loop. while loop removed for easier reading (fewer indentations)
    begin_building:
    
    current_board.push(eoq.front()); 
    pieces[eoq.front()].SetOnBoard(true);
    eoq.pop();
    pieces[current_board.top()].SetPlaceHolderInfo(false, current_board, eoq);
    pieces[current_board.top()].SetPieceDir(-1);
    l_head = &pieces[current_board.top()];
    r_head = &pieces[current_board.top()];
    ld_head = l_head;
    rd_head = r_head;
    int e0_pos = 0;
    ClearRemaining(&eoq, current_board.top());

    // originally a for loop. for loop removed for easier reading (fewer indentations)
    incremented_e0_pos:
    ld_heads.push(current_board.top());
    rd_heads.push(current_board.top());    

    SetE0Idx(e0_pos);
    bool e0_pos_checks_complete = false;

    e0_pos_checks_incomplete:

    
    if (l_depth <= r_depth)
    {
        curr_head = left;
        lq = SetOptimalQueue(l_depth);
        
        if (lq.empty()) // success
        {
            e0_pos_checks_complete = true;
            if (l_depth != 0) { l_depth = 0; }
        }
        
        prev_l_depth = l_depth;
        while ((prev_l_depth == l_depth) && !e0_pos_checks_complete)
        {
            checked_piece_info = CheckOuterEdge(*l_head, &pieces[lq.front()]);
            // currently_checked.push(lq.front()); lq.pop();
            
            if (checked_piece_info.first == 0) // no connection found
            {
                currently_checked.push(lq.front()); 
                lq.pop();
                if (lq.empty()) { l_branch_is_failed = true; }
            }
            else
            {
                ConnectOuterPieces(&pieces[lq.front()], checked_piece_info.second, lq);
                if (checked_piece_info.second == 0) { lq.pop(); } // does not need further checking

                if (pieces[l_head->GetRightParent()].GetRightParent() == -1) // special case for first l_head connection
                { 
                   ld_heads.push(l_head->GetPieceNo());
                    break; 
                }

                // else
                curr_head = left_diag;
                use_remaining_options = false;
                while (pieces[ld_head->GetRightParent()].GetRightChild() != -1)
                {
                    if (!use_remaining_options) { ldq = SetOptimalQueue(l_depth); }
                    
                    l_branch_is_failed = false;
                    ld_branch_is_failed = false;
                    left_diag_checks_complete = false;
                    while (!left_diag_checks_complete)
                    {
                        ldq_front = ldq.front();
                        is_connected = CheckInnerEdges(*ld_head, pieces[pieces[ld_head->GetRightParent()].GetRightChild()], &pieces[ldq_front]);
                        currently_checked.push(ldq.front()); 
                        ldq.pop();

                        if (is_connected)
                        {
                            ConnectInnerPieces(&pieces[ldq_front], ldq);
                            use_remaining_options = false;
                            left_diag_checks_complete = true;
                        }
                        else if (ldq.empty())
                        {
                            if (ld_head->GetLeftParent() != -1) 
                            { ld_branch_is_failed = true; } // ld_head is not equal to l_head.
                            else
                            { l_branch_is_failed = true; }
                            left_diag_checks_complete = true;
                        }
                    } // while (!left_diag_checks_complete)
                    
                    if (ld_branch_is_failed) // we need to pop off the last ld_head
                    {
                        prev_ld_head:
                        curr_head = left_diag;

                        if (ld_heads.size() != 1) // anything other than the special case
                        {
                            use_remaining_options = true;
                            ldq = ld_head->GetRemainingOptions();
                            ld_head = &pieces[ld_head->GetLeftParent()];
                            DisconnectInnerPieces(&pieces[ld_head->GetRightChild()]); 
                        }
                        else // use the special case
                        { 
                            DisconnectOuterPieces(ld_head); 
                            prev_l_depth = l_depth;
                            l_branch_is_failed = true; 
                            curr_head = left; 
                            if (l_depth != 0) { l_depth = 0; }
                            break; 
                        }

                    }
                    else if (l_branch_is_failed) // we need to pop off the last l_head
                    {
                        DisconnectOuterPieces(&pieces[l_head->GetPieceNo()]);
                        break;
                    }
                    else if (pieces[ld_head->GetRightParent()].GetRightChild() == -1)
                    {
                        ld_heads.push(ld_head->GetPieceNo());
                        break;
                    }
                } // while (pieces[ld_head->GetRightParent()].GetRightChild() != -1)
            }

            if (lq.empty() && l_branch_is_failed)
            {
                if (current_board.size() == 1)
                {
                    e0_pos_checks_complete = true;
                    ClearCurrentlyChecked(-1);
                    break;
                }
                else
                {
                    rd_head = &pieces[rd_heads.top()]; rd_heads.pop();
                    prev_r_depth = r_depth;
                    goto prev_rd_head;
                }
            }
        }
        // while (prev_l_depth != l_depth)
    }
    else if (l_depth > r_depth)
    {
        curr_head = right;
        rq = SetOptimalQueue(r_depth);
        
        // start current right path check
        prev_r_depth = r_depth;
        while (prev_r_depth == r_depth)
        {
            checked_piece_info = CheckOuterEdge(*r_head, &pieces[rq.front()]);

            if (checked_piece_info.first == 0) // no connection found 
            {
                currently_checked.push(rq.front()); 
                rq.pop();
                if (rq.empty()) { r_branch_is_failed = true;  }
            }
            else
            {
                ConnectOuterPieces(&pieces[rq.front()], checked_piece_info.second, rq); 
                if (checked_piece_info.second == 0) { rq.pop(); } // does not need further checking
                
                curr_head = right_diag;
                use_remaining_options = false;
                while (pieces[rd_head->GetLeftParent()].GetLeftChild() != -1)
                {
                    if (!use_remaining_options) { rdq = SetOptimalQueue(l_depth); }
                    
                    r_branch_is_failed = false;
                    rd_branch_is_failed = false;
                    right_diag_checks_complete = false;
                    while (!right_diag_checks_complete)
                    {
                        rdq_front = rdq.front();
                        is_connected = CheckInnerEdges(pieces[pieces[rd_head->GetLeftParent()].GetLeftChild()], *rd_head, &pieces[rdq_front]);
                        currently_checked.push(rdq.front()); 
                        rdq.pop();

                        if (is_connected)
                        {
                            ConnectInnerPieces(&pieces[rdq_front], rdq);
                            use_remaining_options = false;
                            right_diag_checks_complete = true;
                        }
                        else if (rdq.empty())
                        {
                            if (rd_head->GetRightParent() != -1) 
                            { rd_branch_is_failed = true; } // rd_head is not equal to r_head already.
                            else 
                            { r_branch_is_failed = true; }
                            right_diag_checks_complete = true;
                        }
                    } 
                    // while (!left_diag_checks_complete)
                    
                    if (rd_branch_is_failed) // we need to pop off the last rd_head
                    {
                        prev_rd_head:
                        curr_head = right_diag;
                        use_remaining_options = true;
                        rdq = rd_head->GetRemainingOptions();
                        rd_head = &pieces[rd_head->GetRightParent()];
                        DisconnectInnerPieces(&pieces[rd_head->GetLeftChild()]); 
                    }
                    else if (r_branch_is_failed)
                    {
                        DisconnectOuterPieces(&pieces[r_head->GetPieceNo()]);
                        break;
                    }
                    else if (pieces[rd_head->GetLeftParent()].GetLeftChild() == -1)
                    {
                        rd_heads.push(rd_head->GetPieceNo());
                        break;
                    }
                }
                // while (pieces[rd_head->GetLeftParent()].GetLeftChild() != -1)
            }
            
            if (rq.empty() && r_branch_is_failed)
            {
                ld_head = &pieces[ld_heads.top()]; ld_heads.pop();
                prev_l_depth = l_depth;
                goto prev_ld_head;
            }
        }   
        // while (prev_r_depth == r_depth)
    }
    

    if (!e0_pos_checks_complete)
    {
        goto e0_pos_checks_incomplete;
    }
                    
    if (!likely_inner_pieces.empty() || !likely_side_pieces.empty() || !likely_corner_pieces.empty() || !failed_corner_pieces.empty())
    {
        if (e0_pos < 3)
        {
            e0_pos++;
            goto incremented_e0_pos;
        }
        else 
        {
            failed_corner_pieces.push(current_board.top());
            pieces[current_board.top()].SetPartOfWhichStack(3);
            pieces[current_board.top()].SetOnBoard(false);
            current_board.pop();

            goto begin_building;
        }
    }
    
    // end of function
    return current_board;
}

// Prints the solution
void SolveOneToughPuzzle::PrintSolution(std::stack<int> solution)
{
    int board_size = board_side_length * board_side_length;
    int complete_board[board_size];

    int length_used = board_side_length - 1;
    int p_no;
    while (length_used > 0)
    {
        // vertical info
        p_no = length_used;
        for (int j=length_used;j>=0;j--)
        {
            if (length_used != board_side_length-1)
            {
                pieces[solution.top()].PtrBackward(); 
            }
            else if ((p_no + board_side_length*j) == board_size-1)
            {
                pieces[solution.top()].PtrForward(); 
            }
            complete_board[p_no + board_side_length*j] = solution.top();
            solution.pop(); 
        }
        
        // horizontal info
        p_no = (length_used*board_side_length) + (length_used-1);
        for (int j=length_used;j>0;j--)
        {
            if (length_used != board_side_length-1)
            {
                pieces[solution.top()].PtrBackward(); 
            }
            pieces[solution.top()].PtrBackward();
            complete_board[p_no] = solution.top();
            solution.pop();
            p_no -= 1;
        }

        length_used -= 1;
    }

    // leftmost corner piece
    pieces[solution.top()].PtrBackward(); 
    complete_board[0] = solution.top();
    solution.pop();

    // printing information to a newly created file
    std::ofstream outputFile("solution.txt");
    outputFile << "Note: Parenthesized numbers describe the right-pointing edge.\nThis is the solution:\n";
    int k = 0;
    for (int i=0;i<board_size;i++)
    {
        if (k == board_side_length-1) 
        {
            outputFile << complete_board[i] << "(" << pieces[complete_board[i]].GetPtrIdx() << ")\n";
            k = 0;
        }
        else 
        {
            outputFile << complete_board[i] << "(" << pieces[complete_board[i]].GetPtrIdx() << ") ";
            k++;
        }   
    }
    outputFile.close();
}

// uses the for loops below to make a queue
// uses the LocationType f() as well
std::queue<int> SolveOneToughPuzzle::SetOptimalQueue(int depth)
{
    int loc_type = GetNextPieceLocationType(depth);
    std::queue<int> optimal_queue;
    
    if (loc_type == 0)
    {
        optimal_queue = SetOptimalQueue_Corner();
    } 
    else if (loc_type == 1)
    {
        optimal_queue = SetOptimalQueue_Side();
    } 
    else if (loc_type == 2)
    {
        optimal_queue = SetOptimalQueue_Inner();
    }

    return optimal_queue;
}

// returns 0 if corner, 1 if side, 2 if inside
int SolveOneToughPuzzle::GetNextPieceLocationType(int depth)
{
    if (current_board.empty())
    {
        // first piece, first corner
        return 0;
    }
    else if (depth == board_side_length) // on one of the end rows/columns.
    {
        // always a corner
        if ((curr_head == left) || (curr_head == right))
        {
            return 0;
        }
        else if ((curr_head == right_diag) && (pieces[rd_head->GetLeftParent()].GetLeftChild() == ld_head->GetPieceNo()))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else if ((curr_head == left_diag) || (curr_head == right_diag))
    {
        return 2;
    }
    else if ((curr_head == left) || (curr_head == right))
    {
        return 1;
    }

    return -1;
}

// These are a bunch of for loops 
std::queue<int> SolveOneToughPuzzle::SetOptimalQueue_Corner()
{
    std::queue<int> optimal_queue;
    
    // pushes corner pieces, then side pieces, then inner pieces to the queue (LIFO)
    // for(int i=0;i<likely_corner_pieces.size();i++)
    while (!likely_corner_pieces.empty())
    {
        optimal_queue.push(likely_corner_pieces.top());
        pieces[likely_corner_pieces.top()].on_a_liklihood_stack = false;
        likely_corner_pieces.pop();
    }
    while (!likely_side_pieces.empty())
    {
        optimal_queue.push(likely_side_pieces.top());
        pieces[likely_side_pieces.top()].on_a_liklihood_stack = false;
        likely_side_pieces.pop();
    }
    while (!likely_inner_pieces.empty())
    {
        optimal_queue.push(likely_inner_pieces.top());
        pieces[likely_inner_pieces.top()].on_a_liklihood_stack = false;
        likely_inner_pieces.pop();
    }

    return optimal_queue;
}

std::queue<int> SolveOneToughPuzzle::SetOptimalQueue_Side()
{
    std::queue<int> optimal_queue;

    // pushes side pieces, then f_pieces; then corner pieces, then inner pieces to the queue (LIFO)
    while (!likely_side_pieces.empty())
    {
        optimal_queue.push(likely_side_pieces.top());
        pieces[likely_side_pieces.top()].on_a_liklihood_stack = false;
        likely_side_pieces.pop();
    }
    while (!failed_corner_pieces.empty())
    {
        optimal_queue.push(failed_corner_pieces.top());
        pieces[failed_corner_pieces.top()].on_a_liklihood_stack = false;
        failed_corner_pieces.pop();
    }
    while (!likely_corner_pieces.empty())
    {
        optimal_queue.push(likely_corner_pieces.top());
        pieces[likely_corner_pieces.top()].on_a_liklihood_stack = false;
        likely_corner_pieces.pop();
    }
    while (!likely_inner_pieces.empty())
    {
        optimal_queue.push(likely_inner_pieces.top());
        pieces[likely_inner_pieces.top()].on_a_liklihood_stack = false;
        likely_inner_pieces.pop();
    }

    return optimal_queue;

}

std::queue<int> SolveOneToughPuzzle::SetOptimalQueue_Inner()
{
    std::queue<int> optimal_queue;

    // pushes side pieces, then corner pieces, then inner pieces to the queue (LIFO)
    while (!likely_inner_pieces.empty())
    {
        optimal_queue.push(likely_inner_pieces.top());
        pieces[likely_inner_pieces.top()].on_a_liklihood_stack = false;
        likely_inner_pieces.pop();
    }
    while (!likely_side_pieces.empty())
    {
        optimal_queue.push(likely_side_pieces.top());
        pieces[likely_side_pieces.top()].on_a_liklihood_stack = false;
        likely_side_pieces.pop();
    }
    while (!failed_corner_pieces.empty())
    {
        optimal_queue.push(failed_corner_pieces.top());
        pieces[failed_corner_pieces.top()].on_a_liklihood_stack = false;
        failed_corner_pieces.pop();
    }
    while (!likely_corner_pieces.empty())
    {
        optimal_queue.push(likely_corner_pieces.top());
        pieces[likely_corner_pieces.top()].on_a_liklihood_stack = false;
        likely_corner_pieces.pop();
    }

    return optimal_queue;

}
