#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#include "board.h"
#include "util.h"

int main(void)
{
    setlocale(LC_ALL, "en_US.UTF-8");

    initialize_board();
    print_board();

    char* coord = malloc(3);
    bool white_turn = true;

    while (true)
    {
        enter_coord(coord, false);
        int src_coord_index = coord_to_index(coord);
        // printf("Array position: %d\n", src_coord_index);

        fflush(stdin);

        wint_t selected_piece = select_piece(src_coord_index);
        if (selected_piece == ' ')
        {
            printf("Square is empty\n");
            continue;
        }
        else if (
                (selected_piece == WHITE_KING || selected_piece == WHITE_QUEEN ||
                 selected_piece == WHITE_ROOK || selected_piece == WHITE_BISHOP ||
                 selected_piece == WHITE_KNIGHT || selected_piece == WHITE_PAWN) &&
                 !white_turn
                )
        {
            printf("Black's turn. Can only choose black pieces\n");
            continue;
        }
        else if (
                (selected_piece == BLACK_KING || selected_piece == BLACK_QUEEN ||
                 selected_piece == BLACK_ROOK || selected_piece == BLACK_BISHOP ||
                 selected_piece == BLACK_KNIGHT || selected_piece == BLACK_PAWN) &&
                 white_turn
                )
        {
            printf("White's turn. Can only choose white pieces\n");
            continue;
        }
        else
        {
            while (true)
            {
                printf("Piece selected: %lc\n", selected_piece);
                enter_coord(coord, true);
                printf("Destination coordinate: %s\n", coord);
                int dst_coord_index = coord_to_index(coord);
                
                if (move_piece(src_coord_index, dst_coord_index, white_turn) == -1)
                    continue;

                print_board();
                white_turn = !white_turn;
                break;
            }
        }
    }

    free(coord);

    return 0;
}
