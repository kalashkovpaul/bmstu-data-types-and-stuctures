#include <stdio.h>
#include <string.h>
#include "book.h"
#include "constants.h"
#include "read_list.h"

void read_list(char *src_filename, book books[], key keys[], int *book_amount)
{
    int check = OK;
    FILE *src = fopen(src_filename, "r");
    if (src == NULL)
        printf("Некорректное имя входного файла!\n");
    else
    {
        check = scan_books(src, books, keys, book_amount);
        if (check != OK)
            printf("Некорректные данные во входном файле!\n");
    }
    fclose(src);
}

int scan_books(FILE *src, book books[], key keys[], int *book_amount)
{
    int i = 0, check = OK;
    while (check == OK)
    {
        check = take_book_from_file(src, books + i);
        if (check == OK)
        {
            keys[i].index = i;
            keys[i].pages = books[i].pages;
            i++;
        }
        if (i > MAX_BOOKS_AMOUNT)
            check = ERR_LENGTH;
    }
    if (check == OK || check == END_STRUCT)
    {
        *book_amount = i;
        if (*book_amount == 0)
            check = ERR_LENGTH;
        else
            check = OK;
    }
    return check;
}

int check_for_error(FILE *file)
{
    int check = OK;
    if (feof(file))
        check = END_STRUCT;
    else
        check = ERR_READ;
    return check;
}

int check_for_ending_chars(FILE *file)
{
    int check;
    char ch;
    check = fscanf(file, "%c", &ch);
    if (check == 1 && ch == '\r')
        check = fscanf(file, "%c", &ch);
    return OK;
}

int check_type(FILE *f_src, book *this_book)
{
    char type[TYPE_MAX_LENGTH] = ""; // !!! TODO - length to change
    int check = file_read_line(f_src, type, TYPE_MAX_LENGTH + 1);
    if (check != OK)
        check = ERR_READ;
    else
    {
        if (strncmp(type, "Technical", TYPE_MAX_LENGTH) == 0)
            this_book->state = 0;
        else if (strncmp(type, "Fiction", TYPE_MAX_LENGTH) == 0)
            this_book->state = 1;
        else if (strncmp(type, "Children's", TYPE_MAX_LENGTH) == 0)
            this_book->state = 2;
        else
            check = ERR_READ;
    }
    return check;
}

int read_about_technical(FILE *f_src, book *this_book)
{
    char type[TYPE_MAX_LENGTH] = ""; // !!! TODO - length to change
    int check = OK;
    check = file_read_line(f_src, this_book->type.technical.sector, SECTOR_MAX_LENGTH);
    if (check != OK)
        check = ERR_READ;
    if (check == OK)
    {
        check = file_read_line(f_src, type, TYPE_MAX_LENGTH);
        if (check != OK)
            check = ERR_READ;
        else if (strncmp(type, "National", TYPE_MAX_LENGTH) == 0)
            this_book->type.technical.is_local = 1;
        else if (strncmp(type, "Foreign", TYPE_MAX_LENGTH) == 0)
            this_book->type.technical.is_local = 0;
        else
            check = ERR_READ;
    }
    if (check == OK)
    {
        check = file_read_line(f_src, type, TYPE_MAX_LENGTH);
        if (check != OK)
            check = ERR_READ;
        else if (strncmp(type, "Translated", TYPE_MAX_LENGTH) == 0)
            this_book->type.technical.is_translated = 1;
        else if (strncmp(type, "Untranslated", TYPE_MAX_LENGTH) == 0)
            this_book->type.technical.is_translated = 0;
        else
            check = ERR_READ;
    }
    if (check == OK)
    {
        check = fscanf(f_src, "%d", &this_book->type.technical.year_of_publication);
        if (check == 1 && this_book->type.technical.year_of_publication > 0)
            check = check_for_ending_chars(f_src);
        else
            check = ERR_READ;
    }
    return check;
}

int read_about_fiction(FILE *f_src, book *this_book)
{
    char type[TYPE_MAX_LENGTH] = ""; // !!! TODO - length to change
    int check = OK;
    if (this_book->state == 1)
    {
        check = file_read_line(f_src, type, TYPE_MAX_LENGTH);
        if (check != OK)
            check = ERR_READ;
        else if (strncmp(type, "Novel", TYPE_MAX_LENGTH) == 0)
            this_book->type.fiction.is_novel = 1;
        else if (strncmp(type, "Not novel", TYPE_MAX_LENGTH) == 0)
            this_book->type.technical.is_local = 0;
        else
            check = ERR_READ;
        if (check == OK)
        {
            check = file_read_line(f_src, type, TYPE_MAX_LENGTH);
            if (check != OK)
                check = ERR_READ;
            else if (strncmp(type, "Play", TYPE_MAX_LENGTH) == 0)
                this_book->type.fiction.is_play = 1;
            else if (strncmp(type, "Not play", TYPE_MAX_LENGTH) == 0)
                this_book->type.fiction.is_play = 0;
            else
                check = ERR_READ;
        }
        if (check == OK)
        {
            check = file_read_line(f_src, type, TYPE_MAX_LENGTH);
            if (check != OK)
                check = ERR_READ;
            else if (strncmp(type, "Poetry", TYPE_MAX_LENGTH) == 0)
                this_book->type.fiction.is_poetry = 1;
            else if (strncmp(type, "Prose", TYPE_MAX_LENGTH) == 0)
                this_book->type.fiction.is_poetry = 0;
            else
                check = ERR_READ;
        }
    }
    return check;
}

int read_about_children(FILE *f_src, book *this_book)
{
    char type[TYPE_MAX_LENGTH] = ""; // !!! TODO - length to change
    int check = OK;
    if (this_book->state == 2)
    {
        check = file_read_line(f_src, type, TYPE_MAX_LENGTH);
        if (check != OK)
            check = ERR_READ;
        else if (strncmp(type, "Tales", TYPE_MAX_LENGTH) == 0)
            this_book->type.childrens.is_tales = 1;
        else if (strncmp(type, "Not tales", TYPE_MAX_LENGTH) == 0)
            this_book->type.childrens.is_tales = 0;
        else
            check = ERR_READ;
        if (check == OK)
        {
            check = file_read_line(f_src, type, TYPE_MAX_LENGTH);
            if (check != OK)
                check = ERR_READ;
            else if (strncmp(type, "Children's poetry", TYPE_MAX_LENGTH) == 0)
                this_book->type.childrens.is_poetry = 1;
            else if (strncmp(type, "Children's prose", TYPE_MAX_LENGTH) == 0)
                this_book->type.childrens.is_tales = 0;
            else
                check = ERR_READ;
        }
    }
    return check;
}

int take_book_from_file(FILE *f_src, book *this_book)
{
    int check;
    check = file_read_line(f_src, this_book->title, TITLE_MAX_LENGTH + 1);
    if (check != OK)
        check = check_for_error(f_src);
    else
    {
        check = file_read_line(f_src, this_book->publishing_house, PUBLISHER_MAX_LENGTH + 1);
        if (check != OK)
            check = ERR_READ;
        else
        {
            check = fscanf(f_src, "%d", &this_book->pages);
            if (check == 1 && this_book->pages > 0)
                check = check_for_ending_chars(f_src);
            else
                check = ERR_READ;
            if (check == OK)
                check = check_type(f_src, this_book);
        }
    }
    if (check == OK && this_book->state == 0)
        check = read_about_technical(f_src, this_book);
    if (check == OK && this_book->state == 1)
        check = read_about_fiction(f_src, this_book);
    if (check == OK && this_book->state == 2)
        check = read_about_children(f_src, this_book);
    return check;
}

void print_info_about_base()
{
    printf("Введите название книги, издательство и количество страниц и тип литературы\n");
}

void print_info_about_technical()
{
    printf("Введите информацию:\n");
    printf("Отрасли\n");
    printf("Отечественная / Зарубежная\n");
    printf("Переводная / Непереводная\n");
    printf("Год публикации\n");
}

void print_info_about_fiction()
{
    printf("Введите информацию:\n");
    printf("Роман / нет\n");
    printf("Пьеса / нет\n");
    printf("Стихи / Проза\n");
}

void print_info_about_children()
{
    printf("Введите информацию:\n");
    printf("Сказки / нет\n");
    printf("Стихи / Проза\n");
}

int take_book(book *this_book)
{
    int check;
    FILE *f_src = stdin;
    print_info_about_base();
    check = file_read_line(f_src, this_book->title, TITLE_MAX_LENGTH + 1);
    if (check != OK)
        check = check_for_error(f_src);
    else
    {
        check = file_read_line(f_src, this_book->publishing_house, PUBLISHER_MAX_LENGTH + 1);
        if (check != OK)
            check = ERR_READ;
        else
        {
            check = fscanf(f_src, "%d", &this_book->pages);
            if (check == 1 && this_book->pages > 0)
                check = check_for_ending_chars(f_src);
            else
                check = ERR_READ;
            if (check == OK)
                check = check_type(f_src, this_book);
        }
    }
    if (check == OK && this_book->state == 0)
    {
        print_info_about_technical();
        check = read_about_technical(f_src, this_book);
    }
    if (check == OK && this_book->state == 1)
    {
        print_info_about_fiction();
        check = read_about_fiction(f_src, this_book);
    }
    if (check == OK && this_book->state == 2)
    {
        print_info_about_children();
        check = read_about_children(f_src, this_book);
    }
    return check;
}

int file_read_line(FILE *file, char *str, int max_length)
{
    int check = OK;
    char ch = 0;
    int i = 0;
    fscanf(file, "%c", &ch);
    while (check == OK && ch != '\n' && ch != '\r' && ch != EOF && !feof(file))
        if (ch < 0)
            check = ERR_READ;
        else if (i < max_length - 1)
        {
            str[i++] = ch;
            fscanf(file, "%c", &ch);
        }
        else
            check = ERR_READ;
    if (ch == '\r')
        fscanf(file, "%c", &ch);
    str[i] = '\0';
    if (i <= 0)
        check = ERR_READ;
    return check;
}