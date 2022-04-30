#ifndef _DYNAMIC_MATRIX_H_

#define _DYNAMIC_MATRIX_H_

#include "info.h"
void myflush();
int **allocate_matrix(int n, int m);
void free_matrix(int **ptrs);
void read_data(info *information);
void generate_data(info *information);
void multiply(info *information);
void change_size(info *information);
void clean_data(info *information);
void study_time(info *information);
void end_program(info *information);

#endif