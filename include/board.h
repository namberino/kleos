#ifndef BOARD_H
#define BOARD_H

#include <wctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>

#include "moves.h"
#include "pieces.h"

#define BOARD_SQUARE_NUM 64

extern wint_t board[BOARD_SQUARE_NUM];
extern char* valid_coords_str[64];

enum coordinate
{
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
    A2 = 8, B2, C2, D2, E2, F2, G2, H2,
    A3 = 16, B3, C3, D3, E3, F3, G3, H3,
    A4 = 24, B4, C4, D4, E4, F4, G4, H4,
    A5 = 32, B5, C5, D5, E5, F5, G5, H5,
    A6 = 40, B6, C6, D6, E6, F6, G6, H6,
    A7 = 48, B7, C7, D7, E7, F7, G7, H7,
    A8 = 56, B8, C8, D8, E8, F8, G8, H8
};

void initialize_board(void);
bool is_valid_coordinate(int x);
void print_board(void);
wint_t select_piece(int coord_index);
int move_piece(wint_t* board_in, int src_coord_index, int dst_coord_index, bool white_turn);
bool is_opponent_piece(int index, bool white_turn, wint_t* board_to_check);
bool is_square_empty(int index, wint_t* board_to_check);
void board_debug_print(void);

#endif
