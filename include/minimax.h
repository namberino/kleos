#ifndef MINIMAX_H
#define MINIMAX_H

#pragma once
#include "board.h"
#include "moves.h"

#include <limits.h>

#define PAWN_VAL 1
#define KNIGHT_VAL 3
#define BISHOP_VAL 3
#define ROOK_VAL 5
#define QUEEN_VAL 9
#define KING_VAL 100

typedef struct
{
    wint_t* board_position;
    int src_index;
    int dst_index;
} Move;

int evaluate_board(wint_t* board);
Move* generate_possible_moves(wint_t* board, bool white_turn, int* num_moves);
int minimax(wint_t* board, int depth, bool max_player, int alpha, int beta, Move* best_position);
int get_best_move(wint_t* board, bool white_turn);

#endif

