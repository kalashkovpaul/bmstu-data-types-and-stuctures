#ifndef AVL_NODE_H_

#define AVL_NODE_H_

typedef struct avl_node avl_node_t;

struct avl_node
{
    char *value;
    char height;
    avl_node_t *left;
    avl_node_t *right;
};

int file_read_avl(FILE *src, avl_node_t **root);

void free_avl(avl_node_t *root);

void balance(avl_node_t **root);

void print_avl(avl_node_t *root);

int find_avl(avl_node_t *root, char *searched, int *found);

#endif