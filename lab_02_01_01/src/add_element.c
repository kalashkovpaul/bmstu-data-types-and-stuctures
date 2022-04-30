#include <stdio.h>
#include "read_list.h"
#include "constants.h"
#include "book.h"

void add_element(book books[], key keys[], int *book_amount)
{
    if (*book_amount >= MAX_BOOKS_AMOUNT)
        printf("Таблица заполнена! Очистите таблицу или удалите элементы для добавления новых!\n");
    else
    {
        printf("Введите данные добавляемого элемента:\n");
        int check = take_book(books + *book_amount);
        if (check == OK)
        {
            keys[*book_amount].index = *book_amount;
            keys[*book_amount].pages = books[*book_amount].pages;
            (*book_amount)++;
            printf("Сделано!\n\n");
        }
        else
        {
            printf("Данные некорректны!\n\n");
            char ch = 0;
            while (ch != '\n')
                scanf("%c", &ch);
        }
    }
}