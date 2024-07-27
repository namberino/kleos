#include <stdio.h>
#include <locale.h>

#include "board.h"

int main(void)
{
    setlocale(LC_ALL, "en_US.UTF-8");

    initialize_board();
    print_board();

    return 0;
}
