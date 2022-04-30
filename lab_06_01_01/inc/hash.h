#ifndef HASH_H_

#define HASH_H_

int file_create_hash_table(FILE *src, node_t *array[], int simple);

void print_hash_table(node_t *array[]);

int hash_find_elements(node_t *array[]);

int str_hash(const char *data, int simple);

void free_hash_table(node_t *array[]);

#endif