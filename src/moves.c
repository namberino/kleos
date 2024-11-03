#include "moves.h"

bool is_valid_pawn_move(int src_index, int dst_index)
{
    return true;
}

bool is_valid_rook_move(int src_index, int dst_index)
{
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
            if (!is_square_empty(index))
                return false; // obstacle found
        }
    }
    else // move along the column
    {
        int row_step = (dst_row > src_row) ? 1 : -1;

        for (int row = src_row + row_step; row != dst_row; row += row_step)
        {
            int index = row * 8 + src_col;
            if (!is_square_empty(index))
                return false; // obstacle found
        }
    }

    return true;
}

bool is_valid_knight_move(int src_index, int dst_index)
{
    // difference between source and destination in x and y axes
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    // can only move 2 squares in 1 direction and 1 in the other
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

bool is_valid_bishop_move(int src_index, int dst_index)
{
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
        if (!is_square_empty(index))
            return false; // obstacle found
    }

    return true;
}

bool is_valid_queen_move(int src_index, int dst_index)
{
    // can move in any direction that the bishop and the knight can
    return is_valid_bishop_move(src_index, dst_index) || is_valid_rook_move(src_index, dst_index);
}

bool is_valid_king_move(int src_index, int dst_index)
{
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    return ((dx == 1 && dy == 1) || (dx == 1 && dy == 0) || (dx == 0 && dy == 1));
}

bool validate_move(wint_t piece, int src_index, int dst_index)
{
    switch (piece)
    {
        case WHITE_PAWN: case BLACK_PAWN:
            return is_valid_pawn_move(src_index, dst_index);

        case WHITE_KNIGHT: case BLACK_KNIGHT:
            return is_valid_knight_move(src_index, dst_index);

        case WHITE_BISHOP: case BLACK_BISHOP:
            return is_valid_bishop_move(src_index, dst_index);

        case WHITE_ROOK: case BLACK_ROOK:
            return is_valid_rook_move(src_index, dst_index);

        case WHITE_QUEEN: case BLACK_QUEEN:
            return is_valid_queen_move(src_index, dst_index);

        case WHITE_KING: case BLACK_KING:
            return is_valid_king_move(src_index, dst_index);

        default:
            return false;
    }
}
