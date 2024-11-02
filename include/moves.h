#ifndef MOVES_H
#define MOVES_H

#include <wctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "pieces.h"

bool is_valid_pawn_move(int src_index, int dst_index);
bool is_valid_rook_move(int src_index, int dst_index);
bool is_valid_knight_move(int src_index, int dst_index);
bool is_valid_bishop_move(int src_index, int dst_index);
bool is_valid_queen_move(int src_index, int dst_index);
bool is_valid_king_move(int src_index, int dst_index);

bool validate_move(wint_t piece, int src_index, int dst_index);

#endif
