#include <stdio.h>
#include "book.h"

void print_title(FILE *dst);
void print_book(FILE *dst, book this_book);
void print_base(FILE *dst, book this_book);
void print_about_technical(FILE *dst, book this_book);
void print_if_not_technical(FILE *dst);
void print_about_fiction(FILE *dst, book this_book);
void print_if_not_fiction(FILE *dst);
void print_about_children(FILE *dst, book this_book);
void print_if_not_children(FILE *dst);

void print_list_by_key(char *dst_filename, book books[], key keys[], int book_amount)
{
    FILE *dst = fopen(dst_filename, "w");
    if (dst == NULL)
        printf("Некорректное имя выходного файла!\n");
    else
    {
        print_title(dst);
        for (int i = 0; i < book_amount; i++)
            print_book(dst, books[keys[i].index]);
        fprintf(dst, "----------------------------------------------------------------------------------------------");
        fprintf(dst, "------------------------------------------------------------------------------------------------------------------\n");
        fprintf(dst, "\n");
        printf("Сделано!\n\n");
    }
    fclose(dst);
}

void print_list(char *dst_filename, book books[], int book_amount)
{
    FILE *dst = fopen(dst_filename, "w");
    if (dst == NULL)
        printf("Некорректное имя выходного файла!\n");
    else
    {
        print_title(dst);
        for (int i = 0; i < book_amount; i++)
            print_book(dst, books[i]);
        fprintf(dst, "----------------------------------------------------------------------------------------------");
        fprintf(dst, "------------------------------------------------------------------------------------------------------------------\n");
        fprintf(dst, "\n");
        printf("Сделано!\n\n");
    }
    fclose(dst);
}

void print_book(FILE *dst, book this_book)
{
    print_base(dst, this_book);
    if (this_book.state == 0)
        print_about_technical(dst, this_book);
    else 
        print_if_not_technical(dst);
    if (this_book.state == 1)
        print_about_fiction(dst, this_book);
    else 
        print_if_not_fiction(dst);
    if (this_book.state == 2)
        print_about_children(dst, this_book);
    else
        print_if_not_children(dst);
    fprintf(dst, "|\n");
}

void print_base(FILE *dst, book this_book)
{
    fprintf(dst, "|%25s|%25s|%24d", this_book.title, this_book.publishing_house, this_book.pages);
    if (this_book.state == 0)
        fprintf(dst, "|   Техническая  ");
    else if (this_book.state == 1)
        fprintf(dst, "| Художественная ");
    else
        fprintf(dst, "|     Детская    ");
}

void print_about_technical(FILE *dst, book this_book)
{
    fprintf(dst, "|%20s", this_book.type.technical.sector);
    if  (this_book.type.technical.is_local == 1)
        fprintf(dst, "|      Да       ");
    else
        fprintf(dst, "|      Нет      ");
    if  (this_book.type.technical.is_translated == 1)
        fprintf(dst, "|     Да     ");
    else
        fprintf(dst, "|     Нет    ");
    fprintf(dst, "|%13d", this_book.type.technical.year_of_publication);
}

void print_if_not_technical(FILE *dst)
{
    fprintf(dst, "|          -         ");
    fprintf(dst, "|       -       ");
    fprintf(dst, "|      -     ");
    fprintf(dst, "|      -      ");
}

void print_about_fiction(FILE *dst, book this_book)
{
    if (this_book.type.fiction.is_novel == 1)
        fprintf(dst, "|   Да  ");
    else
        fprintf(dst, "|  Нет  ");
    if (this_book.type.fiction.is_play == 1)
        fprintf(dst, "|   Да  ");
    else
        fprintf(dst, "|  Нет  ");
    if (this_book.type.fiction.is_poetry == 1)
        fprintf(dst, "|   Да  ");
    else
        fprintf(dst, "|  Нет  ");
}

void print_if_not_fiction(FILE *dst)
{
    fprintf(dst, "|   -   ");
    fprintf(dst, "|   -   ");
    fprintf(dst, "|   -   ");
}

void print_about_children(FILE *dst, book this_book)
{
    if (this_book.type.childrens.is_tales == 1)
        fprintf(dst, "|   Да   ");
    else
        fprintf(dst, "|   Нет  ");
    if (this_book.type.childrens.is_poetry == 1)
        fprintf(dst, "|       Да      ");
    else
        fprintf(dst, "|       Нет     ");
}

void print_if_not_children(FILE *dst)
{
    fprintf(dst, "|   -    ");
    fprintf(dst, "|       -       ");
}

void print_title(FILE *dst)
{
    fprintf(dst, "----------------------------------------------------------------------------------------------");
    fprintf(dst, "------------------------------------------------------------------------------------------------------------------\n");
    fprintf(dst, "|      Название книги     |       Издательство      |   Количество страниц   | Вид литературы ");
    fprintf(dst, "|       Отрасль      | Отечественная | Переводная | Год издания | Роман | Пьеса | Стихи | Сказки | Детские стихи |\n");
    fprintf(dst, "----------------------------------------------------------------------------------------------");
    fprintf(dst, "------------------------------------------------------------------------------------------------------------------\n");
}