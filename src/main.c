#include <stdio.h>
#include <locale.h>
#include <strings.h>
#include <stdbool.h>

#include "board.h"

int main(void)
{
    setlocale(LC_ALL, "en_US.UTF-8");

    initialize_board();
    print_board();

    char coord[3];

    while (true)
    {
        printf("Enter coordinate: ");
        fflush(stdin);

        if (fgets(coord, sizeof(coord), stdin) != NULL)
        {
            for (int i = 0; i < sizeof(coord) / sizeof(coord[0]); i++)
                coord[i] = toupper(coord[i]);
            coord[(sizeof(coord) / sizeof(coord[0])) - 1] = '\0';

            int len = sizeof(valid_coords_str) / sizeof(valid_coords_str[0]);
            bool is_valid_coord = false;

            for (int i = 0; i < len; i++)
            {
                if (strcmp(valid_coords_str[i], coord) == 0)
                {
                    printf("You entered: %s\n", coord);
                    is_valid_coord = true;
                    break;
                }
            }

            if (is_valid_coord)
                break;
            
            printf("Invalid coordinate\n");
        }
        else
        {
            printf("Error reading input");
        }
    }

    return 0;
}
