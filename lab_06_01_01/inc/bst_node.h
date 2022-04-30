#ifndef BST_NODE_H_

#define BST_NODE_H_

#include <stdio.h>

typedef struct bst_node bst_node_t;

struct bst_node
{
    char *value;
    bst_node_t *left;
    bst_node_t *right;
};

int file_read_bst(FILE *src, bst_node_t **root);

void free_bst(bst_node_t *root);

void print_bst(bst_node_t *root);

int find_bst(bst_node_t *root, char *searched, int *found);

#endif