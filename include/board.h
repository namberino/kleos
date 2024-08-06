#ifndef BOARD_H
#define BOARD_H

#include <wctype.h>
#include <stdbool.h>
#include <stdio.h>

#define BOARD_SQUARE_NUM 120

#define WHITE_KING   0x2654 // ♔
#define WHITE_QUEEN  0x2655 // ♕
#define WHITE_ROOK   0x2656 // ♖
#define WHITE_BISHOP 0x2657 // ♗
#define WHITE_KNIGHT 0x2658 // ♘
#define WHITE_PAWN   0x2659 // ♙
#define BLACK_KING   0x265A // ♚
#define BLACK_QUEEN  0x265B // ♛
#define BLACK_ROOK   0x265C // ♜
#define BLACK_BISHOP 0x265D // ♝
#define BLACK_KNIGHT 0x265E // ♞
#define BLACK_PAWN   0x265F // ♟
#define EMPTY_SQUARE ' '

extern wint_t board[BOARD_SQUARE_NUM];
extern char* valid_coords_str[64];

enum
{
    EMPTY,
    WK, WQ, WR, WB, WN, WP,
    BK, BQ, BR, BB, BN, BP,
};

enum coordinate
{
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8
};

void initialize_board(void);
bool is_valid_coordinate(int x);
void print_board(void);
void move_piece(char* coord);

#endif
