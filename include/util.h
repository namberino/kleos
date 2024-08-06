#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>

#include "board.h"

void enter_coord(char* coord);
int coord_to_index(char* coord);

#endif
