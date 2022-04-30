#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void allocate_node(node **start, int length)
{
    node *data = calloc(length, sizeof(node));
    if (data != NULL)
    {
        *start = data;
        node *n = *start;
        int i = 1;
        while (i < length)
        {
            n->next = n + 1;
            n = n->next;
            i++;
        }
        n->next = NULL;
    }
}

void scan_node(FILE *src, node *start, int length)
{
    node *p = start;
    int check = 1;
    for (int i = 0; i < length && p != NULL && check == 1; i++)
    {
        check = fscanf(src, "%d", &(p->value));
        if (check != 1)
        {
            printf("Неверное указание массива IA!\n");
        }
        p = p->next;
    }
}