#include "board.h"

wint_t board[BOARD_SQUARE_NUM];

void initialize_board(void)
{
    for (int i = 0; i < BOARD_SQUARE_NUM; i++)
    {
        board[i] = BLACK_PAWN;

        if (is_valid_coordinate(i))
        {
            board[i] = WHITE_KING;
        }
    }
}

bool is_valid_coordinate(int x)
{
    int coords[] = {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8
    };

    int num_coord = sizeof(coords) / sizeof(coords[0]);

    for (int i = 0; i < num_coord; i++)
    {
        if (x == coords[i])
            return true;
    }

    return false;
}

void print_board(void)
{
    printf("\n             ┌───────────────────┐          \n");
    printf("             │       CHESS       │          \n");
    printf("             └───────────────────┘          \n\n");
    printf("         a   b   c   d   e   f   g   h     \n");
    printf("       ┌───┬───┬───┬───┬───┬───┬───┬───┐   \n");
    printf("     1 │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ 1 \n", board[A1], board[B1], board[C1], board[D1], board[E1], board[F1], board[G1], board[H1]);
    printf("       ├───┼───┼───┼───┼───┼───┼───┼───┤   \n");
    printf("     2 │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ 2 \n", board[A2], board[B2], board[C2], board[D2], board[E2], board[F2], board[G2], board[H2]);
    printf("       ├───┼───┼───┼───┼───┼───┼───┼───┤   \n");
    printf("     3 │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ 3 \n", board[A3], board[B3], board[C3], board[D3], board[E3], board[F3], board[G3], board[H3]);
    printf("       ├───┼───┼───┼───┼───┼───┼───┼───┤   \n");
    printf("     4 │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ 4 \n", board[A4], board[B4], board[C4], board[D4], board[E4], board[F4], board[G4], board[H4]);
    printf("       ├───┼───┼───┼───┼───┼───┼───┼───┤   \n");
    printf("     5 │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ 5 \n", board[A5], board[B5], board[C5], board[D5], board[E5], board[F5], board[G5], board[H5]);
    printf("       ├───┼───┼───┼───┼───┼───┼───┼───┤   \n");
    printf("     6 │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ 6 \n", board[A6], board[B6], board[C6], board[D6], board[E6], board[F6], board[G6], board[H6]);
    printf("       ├───┼───┼───┼───┼───┼───┼───┼───┤   \n");
    printf("     7 │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ 7 \n", board[A7], board[B7], board[C7], board[D7], board[E7], board[F7], board[G7], board[H7]);
    printf("       ├───┼───┼───┼───┼───┼───┼───┼───┤   \n");
    printf("     8 │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ %lc │ 8 \n", board[A8], board[B8], board[C8], board[D8], board[E8], board[F8], board[G8], board[H8]);
    printf("       └───┴───┴───┴───┴───┴───┴───┴───┘   \n");
    printf("         a   b   c   d   e   f   g   h     \n\n");
}
