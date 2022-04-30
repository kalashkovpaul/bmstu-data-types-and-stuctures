#ifndef GRAPH_H_

#define GRAPH_H_

#include <stdio.h>

#include "node.h"

typedef struct graph_node graph_node_t;

struct graph_node
{
    int to;
    int weight;
};

int file_read_graph(FILE *src, node_t **graph);

void print_graph(node_t *graph);

int **find_ways(node_t *graph);

void print_graph_by_matrix(int **matrix, int total);

#endif