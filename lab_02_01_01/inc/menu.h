#ifndef _MENU_H_

#define _MENU_H_

#include "book.h"

void print_menu();
int get_action_code();
void do_action(int code, book books[], key keys[], char *src_filename, char *dst_filename, int *book_amount);

#endif