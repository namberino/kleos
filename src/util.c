#include "util.h"

void enter_coord(char* coord, bool to_coord)
{
    while (true)
    {
        if (to_coord)
            printf("\nEnter destination coordinate: ");
        else
            printf("\nEnter source coordinate: ");

        fflush(stdin);

        if (fgets(coord, sizeof(coord), stdin) != NULL)
        {
            for (int i = 0; i < strlen(coord); i++)
                coord[i] = toupper(coord[i]);
            coord[strlen(coord) - 1] = '\0';

            bool is_valid_coord = false;

            for (int i = 0; i < sizeof(valid_coords_str) / sizeof(valid_coords_str[0]); i++)
            {
                if (strcmp(valid_coords_str[i], coord) == 0)
                {
                    // printf("You entered: %s\n", coord);
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
            printf("Error reading input\n");
        }
    }
}

int coord_to_index(char* coord)
{
    int x = 0;
    int y = 0;

    switch (coord[0]) // column selection
    {
        case 'A': x = 0; break;
        case 'B': x = 1; break;
        case 'C': x = 2; break;
        case 'D': x = 3; break;
        case 'E': x = 4; break;
        case 'F': x = 5; break;
        case 'G': x = 6; break;
        case 'H': x = 7; break;

        default: break;
    }

    switch (coord[1]) // rank selection
    {
        case '1': y = 0; break;
        case '2': y = 1; break;
        case '3': y = 2; break;
        case '4': y = 3; break;
        case '5': y = 4; break;
        case '6': y = 5; break;
        case '7': y = 6; break;
        case '8': y = 7; break;
        
        default: break;
    }

    return y * 8 + x;
}
