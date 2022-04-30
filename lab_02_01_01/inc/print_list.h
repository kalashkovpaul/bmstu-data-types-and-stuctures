#ifndef _PRINT_LIST_H_

#define _PRINT_LIST_H_

#include "book.h"

void print_list(char *dst_filename, book books[], int book_amount);
void print_list_by_key(char *dst_name, book books[], key keys[], int book_amount);
void print_book(FILE *dst, book this_book);

#endif