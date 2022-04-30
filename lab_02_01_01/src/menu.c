#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"
#include "book.h"
#include "print_list.h"
#include "read_list.h"
#include "add_element.h"
#include "delete_element.h"
#include "find_element.h"
#include "sort_list.h"

void clean_list(book books[], key keys[], int *book_amount);    
void sort_list(char *dst, book books[], key keys[], int book_amount);
void set_io(char *src, char *dst);
void print_settings(char *src, char *dst);
void end_program();

void print_menu()
{
    printf("Возможные действия: \n");
    printf(" 1 - Вывести список литературы\n");
    printf(" 2 - Прочитать список литературы\n");
    printf(" 3 - Добавить запись\n");
    printf(" 4 - Удалить запись\n");
    printf(" 5 - Поиск технической литературы по отрасли и году\n");
    printf(" 6 - Удалить все записи\n");
    printf(" 7 - Упорядочить по количеству страниц\n");
    printf(" 8 - Настроить файлы ввода и вывода\n");
    printf(" 9 - Посмотреть текущие параметры программы\n");
    printf(" 0 - Выйти из программы\n");
}

int get_action_code()
{
    printf("Введите номер действия: ");
    char code;
    int result;
    scanf("%c", &code);
    printf("\n");
    switch (code)
    {
    case '1':
        result = PRINT_LIST;
        break;
    case '2':
        result = READ_LIST;
        break;
    case '3':
        result = ADD_ELEMENT;
        break;
    case '4':
        result = DELETE_ELEMENT;
        break;
    case '5':
        result = FIND_ELEMENT;
        break;
    case '6':
        result = CLEAN_LIST;
        break;
    case '7':
        result = SORT_LIST;
        break;
    case '8':
        result = SET_IO;
        break;
    case '9':
        result = PRINT_SETTINGS;
        break;
    case '0':
        result = END_PROGRAM;
        break;
    case '\n':
        result = INCORRECT_CODE;
        break;
    default:
        result = INCORRECT_CODE;
        break;
    }
    myflush();
    return result;
}

void do_action(int code, book books[], key keys[], char *src_filename, char *dst_filename, int *book_amount)
{
    switch (code)
    {
    case 1:
        print_list(dst_filename, books, *book_amount);
        break;
    case 2:
        clean_list(books, keys, book_amount);
        read_list(src_filename, books, keys, book_amount);
        break;
    case 3:
        add_element(books, keys, book_amount);
        break;
    case 4:
        delete_element(books, book_amount);
        break;
    case 5:
        find_element(books, *book_amount);
        break;
    case 6:
        clean_list(books, keys, book_amount);
        break;
    case 7:
        sort_list(dst_filename, books, keys, *book_amount);
        break;
    case 8:
        set_io(src_filename, dst_filename);
        break;
    case 9:
        print_settings(src_filename, dst_filename);
        break;
    case 0:
        end_program();
        break;
    default:
        printf("Действие некорректно!\n\n");
        break;
    }
}

void clean_list(book books[], key keys[], int *book_amount)
{
    memset(keys, 0, sizeof(key) * (*book_amount));
    memset(books, 0, sizeof(book) * (*book_amount));
    (*book_amount) = 0;
    printf("Сделано!\n\n");
}

void set_io(char *src, char *dst)
{
    printf("Введите название файла с исходными данными: ");
    int check = file_read_line(stdin, src, SRC_MAX_LENGTH);
    if (check != OK)
    {
        strncpy(src, "src.txt", SRC_MAX_LENGTH);
        printf("Некорректное название файла!\n");
    }
    else
    {
        printf("Введите название файла с результирующими данными:\n");
        check = file_read_line(stdin, dst, DST_MAX_LENGTH);
        if (check != OK)
        {
            strncpy(dst, "dst.txt", DST_MAX_LENGTH);
            printf("Некореетное название файла!\n");
        }
        else
            printf("Данные сохранены!\n");
    }
    printf("Сделано!\n\n");    
}

void print_settings(char *src, char *dst)
{
    printf("Текущие настройки программы:\n");
    printf("Название файла с исходными данными: %s\n", src);
    printf("Название файла с результирующими данными: %s\n", dst);
    printf("Максимальное количество элементов: %d\n", MAX_BOOKS_AMOUNT);
    printf("Максимальная длина названия: %d\n", TITLE_MAX_LENGTH);
    printf("Максимальная длина навзания исходного файла: %d\n", SRC_MAX_LENGTH);
    printf("Максимальная длина названия файла с результатом: %d\n", DST_MAX_LENGTH);
    printf("Максимальная длина отрасли технической книги: %d\n", SECTOR_MAX_LENGTH);
    printf("Сделано!\n\n");
}

void end_program()
{
    printf("Спасибо, что пользовались этой программой :)\n");
}
