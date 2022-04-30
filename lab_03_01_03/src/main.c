#include <stdio.h>
#include "menu.h"
#include "constants.h"
#include "matrix.h"
#include "info.h"

int main(void)
{
    setbuf(stdout, NULL);
    info information = { 0 };
    print_information();
    int answer = INCORRECT_CODE;
    do_action(CHANGE_SIZE, &information);
    while (answer != END_PROGRAM)
    {
        print_menu();
        answer = get_action_code();
        do_action(answer, &information);
    }
}