#ifndef _INFO_H_

#define _INFO_H_

#include "node.h"

typedef struct
{
    short are_sizes_defined;
    short is_a_defined;
    short is_a_crs_defined;
    short is_b_defined;
    short is_b_ccs_defined;
    short is_c_defined;
    short is_c_ccs_defined;
    int **matrix;
    int n;
    int m;
    int matrix_meaning;
    int ia_length;
    int *a;
    int *ja;
    node *ia;
    int *column;
    int column_length;
    int column_meaning;
    int *b;
    int *jb;
    int *c_column;
    int c_column_length;
    int *c;
    int *jc;
    int c_meaning;
} info;

#endif