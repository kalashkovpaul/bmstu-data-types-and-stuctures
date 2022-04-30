#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "read_list.h"
#include "book.h"

int get_index_of_book(book books[], int book_amount, char *str)
{
    int i = 0;
    while (i < book_amount && strncmp(books[i].title, str, TITLE_MAX_LENGTH) != 0)
        i++;
    if (i == book_amount)
        i = -1;
    return i; 
}

void delete_book(book books[], int *book_amount, int index)
{
    while (index < *book_amount - 1)
    {
        books[index] = books[index + 1];
        index++;
    }
    (*book_amount)--;
}

void delete_element(book books[], int *book_amount)
{
    printf("Введите название удаляемого элемента: ");
    char str[TITLE_MAX_LENGTH + 1] = "";
    int check = file_read_line(stdin, str, TITLE_MAX_LENGTH + 1);
    int index = -1;
    if (check == OK)
        index = get_index_of_book(books, *book_amount, str);
    if (index >= 0)
    {
        delete_book(books, book_amount, index);
        printf("Сделано!\n\n");
    }
    else
        printf("Не найдено!\n\n");
}