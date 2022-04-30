#include <stdio.h>
#include <stdlib.h>

#include "actions.h"
#include "bst_node.h"
#include "avl_node.h"
#include "constants.h"
#include "node.h"
#include "hash.h"

int main(void)
{
    int result = OK;
    char *filename = NULL;
    FILE *src = NULL;
    bst_node_t *bst = NULL;
    avl_node_t *avl = NULL;
    node_t *hash_table[ARRAY_SIZE] = { NULL };
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
    result = file_read_bst(src, &bst);
    if (result != OK)
        return result;
    fclose(src);
    src = fopen(filename, "r");
    if (result != OK)
        return result;
    result = file_read_avl(src, &avl);
    balance(&avl);
    fclose(src);
    src = fopen(filename, "r");
    file_create_hash_table(src, hash_table, 17);
    print_hash_table(hash_table);
    print_bst(bst);
    print_avl(avl);
    fclose(src);
    src = fopen(filename, "r");
    study_time(bst, avl, hash_table, src, filename);
    free_bst(bst);
    free_avl(avl);
    free_hash_table(hash_table);
    return result;
}