#ifndef _MENU_H_

#define _MENU_H_

#include "queue.h"

void print_information();
void print_menu();
int get_action_code();
void do_action(int code, info *information);

#endif