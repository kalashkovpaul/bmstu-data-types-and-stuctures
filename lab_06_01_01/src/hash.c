#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"
#include "actions.h"
#include "constants.h"

int str_hash(const char *data, int simple)
{
    int hash = 0;
    while (data && *data)
        hash = hash * simple + *(data++);
    return hash;
}

int str_comparator(const void *l, const void *r)
{
    const char *str_l = l;
    const char *str_r = r;
    return strcmp(str_l, str_r);
}

int file_create_hash_table(FILE *src, node_t *array[], int simple)
{
    int result = OK;
    char *word = NULL;
    int index = 0;
    do
    {
        result = file_read_word(src, &word);
        if (result != NOTHING && result != ERR_MEMORY)
        {
            index = str_hash(word, simple) % ARRAY_SIZE;
            if (index < 0)
                index *= -1;
            if (!find(array[index], word, str_comparator))
                push_front(array + index, word);
        }
    }
    while (result == OK);
    if (result != OK && result != NOTHING && result != END_READ)
    {
        printf("Не удалось создать хеш-таблицу... завершение...\n");
    }
    else
        result = OK;
    return result;
}

void print_hash_table(node_t *array[])
{
    printf("Хеш-таблица (индекс - значения):\n");
    node_t *tmp = NULL;
    char *word = NULL;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        tmp = array[i];
        word = NULL;
        printf("%3d: ", i);
        while (tmp)
        {
            word = tmp->data;
            printf("%s ", word);
            tmp = tmp->next;
        }
        printf("\n");
    }
}

int hash_find_elements(node_t *array[])
{
    int result = 0;
    node_t *tmp = NULL;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        tmp = array[i];
        while (tmp)
        {
            result++;
            tmp = tmp->next;
        }
    }
    return result;
}

void free_hash_table(node_t *array[])
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        node_t *tmp = array[i];
        node_t *tmp_next = NULL;
        char *word = 0;
        while (tmp)
        {
            tmp_next = tmp->next;
            word = tmp->data;
            free(word);
            free(tmp);
            tmp = tmp_next;
        }
        array[i] = NULL;
    }
}