#ifndef MOVES_H
#define MOVES_H

#include <wctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "pieces.h"
#include "board.h"

bool is_valid_pawn_move(int src_index, int dst_index, bool white_turn, wint_t* board);
bool is_valid_rook_move(int src_index, int dst_index, bool white_turn);
bool is_valid_knight_move(int src_index, int dst_index, bool white_turn);
bool is_valid_bishop_move(int src_index, int dst_index, bool white_turn);
bool is_valid_queen_move(int src_index, int dst_index, bool white_turn);
bool is_valid_king_move(int src_index, int dst_index, bool white_turn);
bool is_valid_castling_move(int src_index, int dst_index, bool white_turn, wint_t* board);

bool validate_move(wint_t piece, int src_index, int dst_index, bool white_turn, wint_t* board);

#endif
