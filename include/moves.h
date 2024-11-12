#ifndef MOVES_H
#define MOVES_H

#include <wctype.h>
#include <stdbool.h>
#include <stdlib.h>

#include "pieces.h"
#include "board.h"
#include "util.h"

extern int en_passant_square;
extern bool white_rook_kingside_moved;
extern bool white_rook_queenside_moved;
extern bool black_rook_kingside_moved;
extern bool black_rook_queenside_moved;

int is_valid_pawn_move(int src_index, int dst_index, bool white_turn, wint_t* board);
int is_valid_rook_move(int src_index, int dst_index, bool white_turn, wint_t* board);
int is_valid_knight_move(int src_index, int dst_index, bool white_turn, wint_t* board);
int is_valid_bishop_move(int src_index, int dst_index, bool white_turn, wint_t* board);
int is_valid_queen_move(int src_index, int dst_index, bool white_turn, wint_t* board);
int is_valid_king_move(int src_index, int dst_index, bool white_turn);
int is_valid_castling_move(int src_index, int dst_index, bool white_turn, wint_t* board);
int is_valid_promotion_move(int src_index, int dst_index, bool white_turn, wint_t* board, bool is_checking);
bool check_for_checks(int src_index, int dst_index, wint_t* board, bool white_turn);
bool check_for_mate(wint_t* board, bool white_turn);

int validate_move(wint_t piece, int src_index, int dst_index, bool white_turn, wint_t* board, bool is_checking);

#endif
