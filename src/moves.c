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

int is_valid_pawn_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    // move only 1 square forward
    int move_direction = white_turn ? -8 : 8;
    if (dst_index == src_index + move_direction && is_square_empty(dst_index, board))
    {
        en_passant_square = -1;
        return 0;
    }

    // if at starting row, 2 squares moves are optional
    int src_row = src_index / 8;
    if ((white_turn && src_row == 6) || (!white_turn && src_row == 1))
    {
        if (dst_index == src_index + move_direction * 2 && is_square_empty(dst_index, board))
        {
            en_passant_square = dst_index;
            return 0;
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
            // board[en_passant_square] = EMPTY_SQUARE;
            en_passant_square = -1;
            return 1;
        }

        // normal capture validation
        if (is_opponent_piece(dst_index, white_turn, board))
            return 0;
    }

    return -1;
}

int is_valid_rook_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    if (!is_square_empty(dst_index, board) && !is_opponent_piece(dst_index, white_turn, board))
        return -1;

    // rook first moved check
    switch (src_index)
    {
        // black queenside rook
        case 0: printf("black queenside\n"); black_rook_queenside_moved = true; break;
        
        // black kingside rook
        case 7: printf("black kingside\n"); black_rook_kingside_moved = true; break;
        
        // white queenside rook
        case 56: printf("white queenside\n"); white_rook_queenside_moved = true; break;

        // white kingside rook
        case 63: printf("white kingside\n"); white_rook_kingside_moved = true; break;
        
        default: break;
    }

    // calculate row and column for source and destination
    int src_row = src_index / 8;
    int src_col = src_index % 8;
    int dst_row = dst_index / 8;
    int dst_col = dst_index % 8;

    // can only move in the same row or column
    if (src_row != dst_row && src_col != dst_col)
        return -1;

    // check for obstacles along the path
    if (src_row == dst_row) // move along the row
    {
        int col_step = (dst_col > src_col) ? 1 : -1;

        for (int col = src_col + col_step; col != dst_col; col += col_step)
        {
            int index = src_row * 8 + col;
            if (!is_square_empty(index, board))
                return -1; // obstacle found
        }
    }
    else // move along the column
    {
        int row_step = (dst_row > src_row) ? 1 : -1;

        for (int row = src_row + row_step; row != dst_row; row += row_step)
        {
            int index = row * 8 + src_col;
            if (!is_square_empty(index, board))
                return -1; // obstacle found
        }
    }

    return 0;
}

int is_valid_knight_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    if (!is_square_empty(dst_index, board) && !is_opponent_piece(dst_index, white_turn, board))
        return -1;
    
    // difference between source and destination in x and y axes
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    // can only move 2 squares in 1 direction and 1 in the other
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2) ? 0 : -1;
}

int is_valid_bishop_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    if (!is_square_empty(dst_index, board) && !is_opponent_piece(dst_index, white_turn, board))
        return -1;

    // difference between source and destination in x and y axes
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    int src_col = src_index % 8;
    int dst_col = dst_index % 8;

    // can only move diagonally, meaning equal dx and dy
    if (dx != dy)
        return -1;

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
            return -1; // obstacle found
    }

    return 0;
}

int is_valid_queen_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    // can move in any direction that the bishop and the knight can
    return (is_valid_bishop_move(src_index, dst_index, white_turn, board) == 0) || (is_valid_rook_move(src_index, dst_index, white_turn, board) == 0) ? 0 : -1;
}

int is_valid_king_move(int src_index, int dst_index, bool white_turn)
{
    if (!is_square_empty(dst_index, board) && !is_opponent_piece(dst_index, white_turn, board))
        return -1;
        
    // difference between source and destination in x and y axes
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    // can move in all direction, but only by 1 square
    if ((dx == 1 && dy == 1) || (dx == 1 && dy == 0) || (dx == 0 && dy == 1))
    {
        if (white_turn)
        {
            white_king_moved = true;
            white_king_pos = dst_index;
        }
        else
        {
            black_king_moved = true;
            black_king_pos = dst_index;
        }

        return 0;
    }

    return -1;
}

int is_valid_castling_move(int src_index, int dst_index, bool white_turn, wint_t* board)
{
    // kingside castling
    if (dst_index == src_index + 2)
    {
        // check if king or rook has been moved before
        if (white_turn && (white_king_moved || white_rook_kingside_moved))
            return -1;
        if (!white_turn && (black_king_moved || black_rook_kingside_moved))
            return -1;

        // check if path is clear
        if (!is_square_empty(src_index + 1, board) && !is_square_empty(src_index + 2, board))
            return -1;

        return 2;
    }
    else if (dst_index == src_index - 2)
    {
        // check if king or rook has been moved before
        if (white_turn && (white_king_moved || white_rook_queenside_moved))
            return -1;
        if (!white_turn && (black_king_moved || black_rook_queenside_moved))
            return -1;

        // check if path is clear
        if (!is_square_empty(src_index + 1, board) && !is_square_empty(src_index + 2, board) && !is_square_empty(src_index + 3, board))
            return -1;

        return 3;
    }

    return -1;
}

int is_valid_promotion_move(int src_index, int dst_index, bool white_turn, wint_t* board, bool is_checking)
{
    if (is_checking)
        return -1;

    if (is_valid_pawn_move(src_index, dst_index, white_turn, board) == -1)
        return -1;

    char promotion_piece;

    while (1)
    {
        printf("Pick a piece (Q - Queen, K - Knight, R - Rook, B - Bishop): ");
        scanf("%s", &promotion_piece);
        fflush(stdin);

        switch (toupper(promotion_piece))
        {
            case 'Q': return 4;
            case 'K': return 5;
            case 'R': return 6;
            case 'B': return 7;
            
            default:
                printf("Invalid piece selection\n");
                continue;
        }
    }

    return -1;
}

bool check_for_checks(int src_index, int dst_index, wint_t* board, bool white_turn)
{
    // save current state of game
    int temp_en_passant_square = en_passant_square;
    int temp_black_king_pos = black_king_pos;
    int temp_white_king_pos = white_king_pos;
    bool temp_white_king_moved = white_king_moved;
    bool temp_black_king_moved = black_king_moved;
    bool temp_white_rook_kingside_moved = white_rook_kingside_moved;
    bool temp_white_rook_queenside_moved = white_rook_queenside_moved;
    bool temp_black_rook_kingside_moved = black_rook_kingside_moved;
    bool temp_black_rook_queenside_moved = black_rook_queenside_moved;

    int king_pos = white_turn ? white_king_pos : black_king_pos;
    wint_t* board_copy = malloc(sizeof(wint_t) * 64);
    copy_array(board, board_copy, 64);

    // make move and check for checks
    board_copy[dst_index] = board_copy[src_index];
    board_copy[src_index] = EMPTY_SQUARE;

    for (int i = 0; i < 64; i++)
    {
        if (is_opponent_piece(i, white_turn, board_copy) && validate_move(board_copy[i], i, king_pos, !white_turn, board_copy, true) == 0)
        {
            // check found
            free(board_copy);
            return true;
        }
    }

    // no check found
    free(board_copy);

    // reinstate state variables
    en_passant_square = temp_en_passant_square;
    black_king_pos = temp_black_king_pos;
    white_king_pos = temp_white_king_pos;
    white_king_moved = temp_white_king_moved;
    black_king_moved = temp_black_king_moved;
    white_rook_kingside_moved = temp_white_rook_kingside_moved;
    white_rook_queenside_moved = temp_white_rook_queenside_moved;
    black_rook_kingside_moved = temp_black_rook_kingside_moved;
    black_rook_queenside_moved = temp_black_rook_queenside_moved;

    return false;
}

bool check_for_mate(wint_t* board, bool white_turn)
{
    // loop through each starting position
    for (int src_index = 0; src_index < 64; src_index++)
    {
        // check if piece is player's piece
        if (!is_opponent_piece(src_index, white_turn, board) && board[src_index] != EMPTY_SQUARE)
        {
            // loop through each possible moves
            for (int dst_index = 0; dst_index < 64; dst_index++)
            {
                // validate move to dest index and check if move gets the king out of check, if yes then no checkmate
                if (validate_move(board[src_index], src_index, dst_index, white_turn, board, true) == 0 && !check_for_checks(src_index, dst_index, board, white_turn))
                    return false;
            }
        }
    }

    // checkmate
    return true;
}

int validate_move(wint_t piece, int src_index, int dst_index, bool white_turn, wint_t* board, bool is_checking)
{
    // multiplexer for the validation functions
    switch (piece)
    {
        case WHITE_PAWN: case BLACK_PAWN:
            // promotion condition
            if ((white_turn && dst_index / 8 == 0) || (!white_turn && dst_index / 8 == 7))
                return is_valid_promotion_move(src_index, dst_index, white_turn, board, is_checking);
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
            if (((white_turn && src_index / 8 == 7) || (!white_turn && src_index / 8 == 0)) && (abs(dst_index - src_index) == 2))
                return is_valid_castling_move(src_index, dst_index, white_turn, board);
            return is_valid_king_move(src_index, dst_index, white_turn);

        default:
            return false;
    }
}
