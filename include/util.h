#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include <wctype.h>

#include "board.h"

void enter_coord(char* coord, bool to_coord);
int coord_to_index(char* coord);
void copy_array(wint_t* arr1, wint_t* arr2, int n);

#endif
