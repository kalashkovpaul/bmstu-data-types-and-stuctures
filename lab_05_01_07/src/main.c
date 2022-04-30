#include <stdio.h>
#include "menu.h"
#include "queue.h"
#include "constants.h"

int main(void)
{
    setbuf(stdout, NULL);
    print_information();
    int array[QUEUE_LENGTH] = { 0 };
    array_queue_t array_queue = { array, array, array, array + QUEUE_LENGTH};
    node_queue_t node_queue = { NULL, NULL };
    info information = { &array_queue, &node_queue, 0, 6, 0, 1};
    int answer = INCORRECT_CODE;
    while (answer != END_PROGRAM)
    {
        print_menu();
        answer = get_action_code();
        do_action(answer, &information);
    }
    return OK;
}