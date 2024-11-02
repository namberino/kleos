#ifndef MOVES_H
#define MOVES_H

#include "board.h"

bool is_valid_pawn_move(int src, int dst);
bool is_valid_rook_move(int src, int dst);
bool is_valid_knight_move(int src, int dst);
bool is_valid_bishop_move(int src, int dst);
bool is_valid_queen_move(int src, int dst);
bool is_valid_king_move(int src, int dst);

bool validate_move(int src, int dst);

#endif
