#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "graph.h"
#include "node.h"
#include "constants.h"

int file_read_graph_node(FILE *src, node_t **new_node, int total);

void free_graph(node_t **graph);

int file_read_graph(FILE *src, node_t **graph)
{
    int result = OK;
    int total = 0;
    int check = 0;
    check = fscanf(src, "%d", &total);
    if (check != 1 || total <= 0)
        return ERR_IO;
    int i = 0;
    node_t *new_node = NULL;
    while (result == OK && i < total)
    {
        result = file_read_graph_node(src, &new_node, total);
        if (result == OK)
            push_back(graph, new_node);
        new_node = NULL;
        i++;
    }
    if (result != OK)
    {
        printf("Ошибка в вершине %d\n", i);
        free_graph(graph);
        return result;
    }
    printf("Граф успешно считан!\n");
    return result;
}

int file_read_graph_node(FILE *src, node_t **new_node, int total)
{
    int bounded_to = 0;
    int check = 0;
    check = fscanf(src, "%d", &bounded_to);
    if (check != 1 || bounded_to < 0 || bounded_to > total)
        return ERR_IO;
    int previous = 0;
    int to = 0;
    int weight;
    graph_node_t *new_graph_node = NULL;
    for (int i = 0; i < bounded_to; i++)
    {
        check = fscanf(src, "%d%d", &to, &weight);
        if (check != 2 || to <= previous || to > total || weight <= 0 || weight >= MAX_WEIGHT)
        {
            if (to <= previous)
                printf("Ошибка в вершине!\n");
            printf("Ошибка ввода!\n");
            return ERR_IO;
        }
        new_graph_node = malloc(sizeof(graph_node_t));
        if (new_graph_node == NULL)
        {
            free(new_graph_node);
            return ERR_MEMORY;
        }
        new_graph_node->to = to;
        new_graph_node->weight = weight;
        push_back(new_node, new_graph_node);
    }
    return OK;
}

void free_graph(node_t **graph)
{
    if (graph)
    {
        node_t *tmp = *graph;
        node_t *next = NULL;
        while (tmp)
        {
            node_t *graph_tmp = tmp->data;
            node_t *graph_next = NULL;
            graph_node_t *graph_node = NULL;
            while (graph_tmp)
            {
                graph_next = graph_tmp->next;
                graph_node = graph_tmp->data;
                free(graph_node);
                free(graph_tmp);
                graph_tmp = graph_next;
            }
            next = tmp->next;
            free(tmp);
            tmp = next;
        }
    }
}

void print_graph_to_file(node_t *graph, FILE *file)
{
    if (graph)
    {
        int i = 1;
        node_t *tmp = graph;
        while (tmp)
        {
            node_t *graph_tmp = tmp->data;
            graph_node_t *graph_node = NULL;
            while (graph_tmp)
            {
                graph_node = graph_tmp->data;
                fprintf(file, "\"%d\" -> \"%d\" [label=%d];\n", i, graph_node->to, graph_node->weight);
                graph_tmp = graph_tmp->next;
            }
            tmp = tmp->next;
            i++;
        }
    }
}

void print_graph(node_t *graph)
{
    FILE *file = fopen("graphviz_graph.gv", "w");
    if (file)
    {
        fprintf(file, "digraph {\n");
        print_graph_to_file(graph, file);
        fprintf(file, "}\n");
        fclose(file);
        system("dot -Tjpg graphviz_graph.gv -o graph.jpg");
        system("feh graph.jpg");
    }
}

int find_way_between(int from, int to, node_t *graph)
{
    int i = 0;
    node_t *tmp = graph;
    while (tmp && i < from)
    {
        tmp = tmp->next;
        i++;
    }
    if (!tmp || i != from)
        return NO_WAY;
    node_t *way_tmp = tmp->data;
    graph_node_t *graph_node = NULL;
    while (way_tmp)
    {
        graph_node = way_tmp->data;
        if (graph_node->to == to + 1)
            return graph_node->weight;
        way_tmp = way_tmp->next;
    }
    return NO_WAY;
}

int **allocate_matrix(int n, int m)
{
    int **ptrs, *data;
    ptrs = malloc(n * sizeof(int *));
    data = calloc(n * m, sizeof(int));
    if (!data)
    {
        free(ptrs);
        ptrs = NULL;
    }
    if (ptrs != NULL)
    {
        for (int i = 0; i < n; i++)
            ptrs[i] = data + i * m;
    }
    return ptrs;
}


int **find_ways(node_t *graph)
{
    int total = get_length(graph);
    int **matrix = allocate_matrix(total, total);
    int *d = malloc(total * sizeof(int));
    int *v = malloc(total * sizeof(int));
    int min_index = 0;
    int min = 0;
    int tmp = 0;
    int cur_way = 0;
    double time = 0;
    struct timeval tv_start, tv_stop;
    printf("                     Матрица кратчайших путей \n");
    printf("                        Конечный пункт\n");
    printf("Начальный пункт      ");
    for (int i = 0; i < total; i++)
        printf("%5d ", i + 1);
    printf("\n");
    if (d == NULL || v == NULL)
    {
        free(d);
        free(v);
        return NULL;
    }
    gettimeofday(&tv_start, NULL);
    for (int index = 0; index < total; index++)
    {
        for (int i = 0; i < total; i++)
        {
            d[i] = MAX_WEIGHT;
            v[i] = 1; 
        }
        d[index] = 0;
        do
        {
            min_index = MAX_WEIGHT;
            min = MAX_WEIGHT;
            for (int i = 0; i < total; i++)
            {
                if (v[i] == 1 && d[i] < min)
                {
                    min = d[i];
                    min_index = i;
                }
            }
            if (min_index != MAX_WEIGHT)
            {
                for (int i = 0; i < total; i++)
                {
                    if ((cur_way = find_way_between(min_index, i, graph)) != NO_WAY)
                    {
                        tmp = min + cur_way;
                        if (tmp < d[i])
                            d[i] = tmp;
                    }
                }
                v[min_index] = 0;
            }
        }
        while (min_index < MAX_WEIGHT);
        printf("                %5d", index + 1);
        for (int i = 0; i < total; i++)
        {
            matrix[index][i] = d[i];
            if (d[i] == MAX_WEIGHT)
                printf("%5s ", "-");
            else
                printf("%5d ", d[i]);
        }
        printf("\n");
    }
    gettimeofday(&tv_stop, NULL);
    time += (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    size_t data = sizeof(node_t) * total;
    node_t *temp = graph;
    node_t *node;
    for (int i = 0; i < total; i++)
    {
        node = temp->data;
        data += (get_length(node) * (sizeof(node_t) + sizeof(graph_node_t)));
        temp = temp->next;
    }
    printf("Поиск кратчайшего пути: время поиска %lf нс, памяти использовано %ld байт\n", \
        (time * 1000) / STUDY_TIME_ITERATIONS, data * sizeof(char));
    return matrix;
}

void print_matrix_to_file(int **matrix, FILE *file, int total)
{
    for (int i = 0; i < total; i++)
    {
        for (int j = 0; j < total; j++)
        {
            if (matrix[i][j] != 0 && matrix[i][j] != MAX_WEIGHT)
            fprintf(file, "\"%d\" -> \"%d\" [label=%d];\n", i + 1, j + 1, matrix[i][j]);
        }
    }

}

void print_graph_by_matrix(int **matrix, int total)
{
    FILE *file = fopen("graphviz_graph.gv", "w");
    if (file)
    {
        fprintf(file, "digraph {\n");
        print_matrix_to_file(matrix, file, total);
        fprintf(file, "}\n");
        fclose(file);
        system("dot -Tjpg graphviz_graph.gv -o graph_ways.jpg");
        system("feh graph_ways.jpg");
    }
}
