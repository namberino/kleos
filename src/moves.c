#include "moves.h"

int en_passant_square = -1;

int black_king_pos = E1;
int white_king_pos = E8;

bool white_king_moved = false;
bool black_king_moved = false;
bool white_rook_kingside_moved = false;
bool white_rook_queenside_moved = false;
bool black_rook_kingside_moved = false;
bool black_rook_queenside_moved = false;

bool is_valid_pawn_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    // move only 1 square forward
    int move_direction = white_turn ? -8 : 8;
    if (dst_index == src_index + move_direction && is_square_empty(dst_index, board))
    {
        en_passant_square = -1;
        return true;
    }

    // if at starting row, 2 squares moves are optional
    int src_row = src_index / 8;
    if (src_row == 6 || src_row == 1)
    {
        if (dst_index == src_index + move_direction * 2 && is_square_empty(dst_index, board))
        {
            en_passant_square = dst_index;
            return true;
        }
    }

    // capture logic (capture diagonally or en passant)
    int src_col = src_index % 8;
    int dst_col = dst_index % 8;
    int dst_row = dst_index / 8;
    if (dst_row == src_row + move_direction / 8 && abs(dst_col - src_col) == 1)
    {
        // en passant validation
        if (dst_index == en_passant_square + move_direction)
        {
            board[en_passant_square] = EMPTY_SQUARE;
            en_passant_square = -1;
            return true;
        }

        // normal capture validation
        if (is_opponent_piece(dst_index, white_turn, board))
            return true;
    }

    return false;
}

bool is_valid_rook_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    if (!is_square_empty(dst_index, board) && !is_opponent_piece(dst_index, white_turn, board))
        return false;

    // rook first moved check
    switch (src_index)
    {
        // black queenside rook
        case 0: black_rook_queenside_moved = true; break;
        
        // black kingside rook
        case 7: black_rook_kingside_moved = true; break;
        
        // white queenside rook
        case 56: white_rook_queenside_moved = true; break;

        // white kingside rook
        case 63: white_rook_kingside_moved = true; break;
        
        default: break;
    }

    // calculate row and column for source and destination
    int src_row = src_index / 8;
    int src_col = src_index % 8;
    int dst_row = dst_index / 8;
    int dst_col = dst_index % 8;

    // can only move in the same row or column
    if (src_row != dst_row && src_col != dst_col)
        return false;

    // check for obstacles along the path
    if (src_row == dst_row) // move along the row
    {
        int col_step = (dst_col > src_col) ? 1 : -1;

        for (int col = src_col + col_step; col != dst_col; col += col_step)
        {
            int index = src_row * 8 + col;
            if (!is_square_empty(index, board))
                return false; // obstacle found
        }
    }
    else // move along the column
    {
        int row_step = (dst_row > src_row) ? 1 : -1;

        for (int row = src_row + row_step; row != dst_row; row += row_step)
        {
            int index = row * 8 + src_col;
            if (!is_square_empty(index, board))
                return false; // obstacle found
        }
    }

    return true;
}

bool is_valid_knight_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    if (!is_square_empty(dst_index, board) && !is_opponent_piece(dst_index, white_turn, board))
        return false;
    
    // difference between source and destination in x and y axes
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    // can only move 2 squares in 1 direction and 1 in the other
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

bool is_valid_bishop_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    if (!is_square_empty(dst_index, board) && !is_opponent_piece(dst_index, white_turn, board))
        return false;

    // difference between source and destination in x and y axes
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    int src_col = src_index % 8;
    int dst_col = dst_index % 8;

    // can only move diagonally, meaning equal dx and dy
    if (dx != dy)
        return false;

    // determine step based on move direction
    int step = 0;
    if (src_index > dst_index)
        step = src_col > dst_col ? -9 : -7;
    else
        step = src_col > dst_col ? 7 : 9;

    // move through each squares
    for (int index = src_index + step; index != dst_index; index += step)
    {
        if (!is_square_empty(index, board))
            return false; // obstacle found
    }

    return true;
}

bool is_valid_queen_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    // can move in any direction that the bishop and the knight can
    return is_valid_bishop_move(src_index, dst_index, white_turn, board) || is_valid_rook_move(src_index, dst_index, white_turn, board);
}

bool is_valid_king_move(int src_index, int dst_index, bool white_turn)
{
    if (white_turn)
        white_king_moved = true;
    else
        black_king_moved = true;

    // difference between source and destination in x and y axes
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    // can move in all direction, but only by 1 square
    if ((dx == 1 && dy == 1) || (dx == 1 && dy == 0) || (dx == 0 && dy == 1))
    {
        if (white_turn)
            white_king_pos = dst_index;
        else
            black_king_pos = dst_index;

        return true;
    }

    return false;
}

bool is_valid_castling_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    // kingside castling
    if (dst_index == src_index + 2)
    {
        // check if king or rook has been moved before
        if (white_turn && (white_king_moved || white_rook_kingside_moved))
            return false;
        if (!white_turn && (black_king_moved || black_rook_kingside_moved))
            return false;

        // check if path is clear
        if (!is_square_empty(src_index + 1, board) && !is_square_empty(src_index + 2, board))
            return false;

        // move pieces
        board[src_index + 1] = board[dst_index + 1];
        board[dst_index + 1] = EMPTY_SQUARE;

        return true;
    }
    else if (dst_index == src_index - 2)
    {
        // check if king or rook has been moved before
        if (white_turn && (white_king_moved || white_rook_queenside_moved))
            return false;
        if (!white_turn && (black_king_moved || black_rook_queenside_moved))
            return false;

        // check if path is clear
        if (!is_square_empty(src_index + 1, board) && !is_square_empty(src_index + 2, board) && !is_square_empty(src_index + 3, board))
            return false;
        
        // move pieces
        board[src_index - 1] = board[dst_index - 2];
        board[dst_index - 2] = EMPTY_SQUARE;

        return true;
    }

    return false;
}

bool check_for_checks(int src_index, int dst_index, wint_t* board, bool white_turn)
{
    int king_position = white_turn ? white_king_pos : black_king_pos;
    wint_t* board_copy = malloc(sizeof(wint_t) * 64);
    copy_array(board, board_copy, 64);

    // make move and check for checks
    board_copy[dst_index] = board_copy[src_index];
    board_copy[src_index] = EMPTY_SQUARE;

    for (int i = 0; i < 64; i++)
    {
        if (is_opponent_piece(i, white_turn, board_copy) && validate_move(board_copy[i], i, king_position, !white_turn, board_copy))
        {
            // check found
            free(board_copy);
            return true;
        }
    }

    // no check found
    free(board_copy);
    return false;
}

bool validate_move(wint_t piece, int src_index, int dst_index, bool white_turn, wint_t* board)
{
    // multiplexer for the validation functions
    switch (piece)
    {
        case WHITE_PAWN: case BLACK_PAWN:
            return is_valid_pawn_move(src_index, dst_index, white_turn, board);

        case WHITE_KNIGHT: case BLACK_KNIGHT:
            return is_valid_knight_move(src_index, dst_index, white_turn, board);

        case WHITE_BISHOP: case BLACK_BISHOP:
            return is_valid_bishop_move(src_index, dst_index, white_turn, board);

        case WHITE_ROOK: case BLACK_ROOK:
            return is_valid_rook_move(src_index, dst_index, white_turn, board);

        case WHITE_QUEEN: case BLACK_QUEEN:
            return is_valid_queen_move(src_index, dst_index, white_turn, board);

        case WHITE_KING: case BLACK_KING:
            // castling condition
            if ((src_index / 8 == 7 || src_index / 8 == 0) && (abs(dst_index - src_index) == 2))
                return is_valid_castling_move(src_index, dst_index, white_turn, board);
            return is_valid_king_move(src_index, dst_index, white_turn);

        default:
            return false;
    }
}
