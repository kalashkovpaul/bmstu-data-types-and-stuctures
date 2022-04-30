#ifndef _READ_LIST_H_

#define _READ_LIST_H_

#include "book.h"

void read_list(char *src_filename, book books[], key keys[], int *book_amount);
int take_book_from_file(FILE *f_src, book *this_book);
int file_read_line(FILE *file, char *str, int max_length);
int scan_books(FILE *src, book books[], key keys[], int *book_amount);
int take_book(book *this_book);

#endif