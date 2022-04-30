#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "constants.h"
#include "book.h"
#include "print_list.h"
#include "read_list.h"

void print_technical(book current_book)
{
    printf("%s\n", current_book.title);
    printf("%s\n", current_book.publishing_house);
    printf("%d\n", current_book.pages);
    printf("%s\n", current_book.type.technical.sector);
    if (current_book.type.technical.is_local)
        printf("National\n");
    else
        printf("Foreign\n");
    if (current_book.type.technical.is_translated)
        printf("Translated\n");
    else
        printf("Untranslated\n");
    printf("%d\n", current_book.type.technical.year_of_publication);
}

void find_element(book books[], int book_amount)
{
    printf("Введите отрасль: ");
    char str[SECTOR_MAX_LENGTH + 1] = "";
    int check = file_read_line(stdin, str, SECTOR_MAX_LENGTH + 1);
    int is_there_such_element = 0;
    char ch = 0;
    if (check == OK)
    {
        int i = 0;
        printf("Введите год: ");
        int year = 0;
        check = scanf("%d", &year);
        if (check == 1)
            while (i < book_amount)
            {
                if (books[i].state == 0 && books[i].type.technical.is_local && strncmp(str, books[i].type.technical.sector, SECTOR_MAX_LENGTH) == 0 \
                && books[i].type.technical.year_of_publication == year)
                {
                    print_technical(books[i]);
                    is_there_such_element = 1;
                }
                i++;
            }
        else
            while (ch != '\n')
                scanf("%c", &ch);

    }
    printf("\n");
    if (is_there_such_element)
        printf("Сделано!\n\n");
    else
        printf("Не найдено!\n\n");    
}



