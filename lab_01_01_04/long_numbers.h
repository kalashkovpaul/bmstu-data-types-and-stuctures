#include "constants.h"

#ifndef _LONG_NUMBERS_H_

#define _LONG_NUMBERS_H_

typedef struct 
{
    int is_significand_negative;
    int significand[MAX_SIGNIFICAND_LENGTH + 1];
    int significand_length;
    int dot_index;
    int base;
    int is_base_negative;
    int start_index, end_index;
} long_float;

typedef struct
{
    int is_negative;
    int number[MAX_INT_LENGTH + 1];
    int length;
    int start_index, end_index;
} long_int;

#endif