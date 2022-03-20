#ifndef QUICKSORT
#define QUICKSORT

#include <stdlib.h>
#include <stdio.h>
#include "../Decoder/Decoder.h"

/*
 * https://github.com/markwkm/quicksort/blob/master/recursive/quicksort.c
 * A implementacao original pode ser econtrada no repo acima. 
 * O codigo foi alterado para se adequar as estruturas do trabalho.
*/

void quicksort(ArrayList *array, int left, int right);

#endif