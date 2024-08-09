#include <stdio.h>
#include <locale.h>

#include "board.h"
#include "util.h"

int main(void)
{
    setlocale(LC_ALL, "en_US.UTF-8");

    initialize_board();
    print_board();

    char* coord = malloc(3);

    while (true)
    {
        enter_coord(coord, false);
        int src_coord_index = coord_to_index(coord);
        printf("Array position: %d\n", src_coord_index);

        fflush(stdin);

        wint_t selected_piece = select_piece(src_coord_index);
        if (selected_piece == ' ')
        {
            printf("Square is empty\n");
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
                
                if (move_piece(src_coord_index, dst_coord_index) == -1)
                    continue;

                print_board();
                break;
            }
        }
    }

    free(coord);

    return 0;
}
