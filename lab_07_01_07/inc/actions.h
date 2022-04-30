#ifndef ACTIONS_H_

#define ACTIONS_H_

#include <stdio.h>

#include "bst_node.h"
#include "avl_node.h"
#include "node.h"

void print_information();

int file_read_line(FILE* src, char **str);

int file_read_word(FILE* src, char **str);

void print_goodbye();

void study_time(bst_node_t *bst, avl_node_t *avl, node_t *hash[], FILE *file, char *filename);

#endif