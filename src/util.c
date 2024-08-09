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
            printf("Error reading input");
        }
    }
}

int coord_to_index(char* coord)
{
    int x = 0;
    int y = 0;

    switch (coord[0])
    {
        case 'A': x = 1; break;
        case 'B': x = 2; break;
        case 'C': x = 3; break;
        case 'D': x = 4; break;
        case 'E': x = 5; break;
        case 'F': x = 6; break;
        case 'G': x = 7; break;
        case 'H': x = 8; break;

        default: break;
    }

    switch (coord[1])
    {
        case '1': y = 20; break;
        case '2': y = 30; break;
        case '3': y = 40; break;
        case '4': y = 50; break;
        case '5': y = 60; break;
        case '6': y = 70; break;
        case '7': y = 80; break;
        case '8': y = 90; break;
        
        default: break;
    }

    return x + y;
}
