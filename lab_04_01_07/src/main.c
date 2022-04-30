#include <stdio.h>
#include "menu.h"
#include "info.h"
#include "constants.h"

int main(void)
{
    setbuf(stdout, NULL);
    print_information();
    stack_array_t stack_array = { NULL, NULL, 0 };
    stack_node_t stack_node = { NULL, 0, NULL };
    info information = { &stack_array, &stack_node };
    int answer = INCORRECT_CODE;
    while (answer != END_PROGRAM)
    {
        print_menu();
        answer = get_action_code();
        do_action(answer, &information);
    }
    return OK;
}