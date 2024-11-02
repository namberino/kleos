#include "moves.h"

bool is_valid_pawn_move(int src_index, int dst_index)
{
    return true;
}

bool is_valid_rook_move(int src_index, int dst_index)
{
    return true;
}

bool is_valid_knight_move(int src_index, int dst_index)
{
    // difference between source and destination in x and y axes
    int dx = abs((src_index % 8) - (dst_index % 8)); // column difference
    int dy = abs((src_index / 8) - (dst_index / 8)); // row difference

    // knight can move 2 squares in 1 direction and 1 in the other
    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}

bool is_valid_bishop_move(int src_index, int dst_index)
{
    return true;
}

bool is_valid_queen_move(int src_index, int dst_index)
{
    return true;
}

bool is_valid_king_move(int src_index, int dst_index)
{
    return true;
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
