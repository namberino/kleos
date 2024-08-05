#include "util.h"

void enter_coord(char* coord)
{
    while (true)
    {
        printf("Enter coordinate: ");
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
}
