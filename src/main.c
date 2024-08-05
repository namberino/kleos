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
    enter_coord(coord);
    free(coord);

    return 0;
}
