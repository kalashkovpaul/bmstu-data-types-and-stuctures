#include "constants.h"
#include "menu.h"
#include "book.h"

int main(void)
{   
    book books[MAX_BOOKS_AMOUNT] = { 0 };
    key keys[MAX_BOOKS_AMOUNT] = { 0 };
    char src_filename[SRC_MAX_LENGTH] = "src.txt";
    char dst_filename[DST_MAX_LENGTH] = "dst.txt";
    int book_amount = 0;
    int answer = INCORRECT_CODE;
    while (answer != END_PROGRAM)
    {
        print_menu();
        answer = get_action_code();
        do_action(answer, books, keys, src_filename, dst_filename, &book_amount);
    }
}