#ifndef _NODE_H_

#define _NODE_H_

struct node;

typedef struct node
{
    int value;
    struct node *next;
} node;

void allocate_node(node **start, int length);
void scan_node(FILE *src, node *start, int length);

#endif
