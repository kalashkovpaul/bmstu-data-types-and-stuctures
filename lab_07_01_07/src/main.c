#include <stdio.h>
#include <stdlib.h>

#include "actions.h"
#include "constants.h"
#include "node.h"
#include "graph.h"

int main(void)
{
    int result = OK;
    char *filename = NULL;
    FILE *src = NULL;
    node_t *graph = NULL;
    print_information();
    printf("Введите название файла с исходными данными: ");
    result = file_read_line(stdin, &filename);
    if (result != OK)
    {
        printf("Вы не ввели строку...\n");
        return result;
    }
    src = fopen(filename, "r");
    if (src == NULL)
    {
        printf("Неверное название файла... завершение программы...\n");
        free(filename);
        result = ERR_FILE;
        return result;
    }
    result = file_read_graph(src, &graph);
    if (result != OK)
    {
        printf("Не удалось считать граф... Завершение... %d\n", result);
        return result;
    }
    print_graph(graph);
    int total = get_length(graph);
    int **matrix = find_ways(graph);
    print_graph_by_matrix(matrix, total);
    print_goodbye();
    return result;
}