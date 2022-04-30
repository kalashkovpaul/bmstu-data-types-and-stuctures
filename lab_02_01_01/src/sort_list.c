#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "print_list.h"
#include "constants.h"
#include "book.h"

void myflush()
{
    char ch = 0;
    while (ch != '\n')
        scanf("%c", &ch);
}

void sort(book books[], int book_amount)
{
    book t = { 0 };
    for (int i = 1; i < book_amount; i++)
        for (int j = i; j > 0; j--)
            if (books[j - 1].pages > books[j].pages)
            {
                t = books[j - 1];
                books[j - 1] = books[j];
                books[j] = t;
            }
}

void sort_keys(key keys[], int book_amount)
{
    key t = { 0 };
    for (int i = 1; i < book_amount; i++)
        for (int j = i; j > 0; j--)
            if (keys[j - 1].pages > keys[j].pages)
            {
                t = keys[j - 1];
                keys[j - 1] = keys[j];
                keys[j] = t;
            }
}

void sort_insection(key keys[], int book_amount)
{
    sort_keys(keys, book_amount);
}

int compare(const void *p1, const void *p2)
{
    const key *k1 = p1;
    const key *k2 = p2;
    return (k1->pages - k2->pages);
}

int compare_books(const void *p1, const void *p2)
{
    const book *b1 = p1;
    const book *b2 = p2;
    return (b1->pages - b2->pages);
}

void sort_with_key(key keys[], int book_amount)
{
    printf(" 1 - Сортировка вставками\n");
    printf(" 2 - Быстрая сортировка\n");
    printf("Введите номер действия: ");
    char ch = 0;
    scanf("%c", &ch);
    switch (ch)
    {
    case '1':
        sort_insection(keys, book_amount);
        break;
    case '2':
        qsort(keys, book_amount, sizeof(key), compare);
        break;
    default:
        printf("Некорректный ввод!\n");
        break;
    while (ch != '\n')
        scanf("%c", &ch);
    }   
}


void sort_without_key(book books[], int book_amount)
{
    printf(" 1 - Сортировка вставками\n");
    printf(" 2 - Быстрая сортировка\n");
    printf("Введите номер действия: ");
    char ch = 0;
    scanf("%c", &ch);
    switch (ch)
    {
    case '1':
        myflush();
        sort(books, book_amount);
        break;
    case '2':
        myflush();
        qsort(books, book_amount, sizeof(book), compare_books);
        break;
    default:
        printf("Некорректный ввод!\n");
        break;
    while (ch != '\n')
        scanf("%c", &ch);
    }   
}

void measure_sort(book books[], key keys[], int book_amount)
{
    int64_t time_1, time_2;
    long memory_1 = sizeof(book) * book_amount;
    long memory_2 = sizeof(key) * book_amount;
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    sort(books, book_amount);
    gettimeofday(&tv_stop, NULL);
    time_1 = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("Вставками: %ld мкс, %ld байт\n", time_1, memory_1);
    gettimeofday(&tv_start, NULL);
    sort_keys(keys, book_amount);
    gettimeofday(&tv_stop, NULL);
    time_2 = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("Вставками по ключам: %ld мкс, %ld байт\n", time_2, memory_1 + memory_2);
    printf("Итого: с использованием доп.таблицы с ключами ");
    if (time_1 > time_2 && time_2 != 0)
        printf("+%ld%% по времени и ", time_1 / time_2 * 100);
    else
        printf("-%ld%% по времени и ", time_1 / time_2 * 100);
    printf("+%ld%% по памяти.\n", memory_2 / memory_1 * 100);  
}

void measure_qsort(book books[], key keys[], int book_amount)
{
    int64_t time_1, time_2;
    long memory_1 = sizeof(book) * book_amount;
    long memory_2 = sizeof(key) * book_amount;
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    qsort(books, book_amount, sizeof(book), compare_books);
    gettimeofday(&tv_stop, NULL);
    time_1 = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("Быстрой: %ld мкс, %ld байт\n", time_1, memory_1);
    gettimeofday(&tv_start, NULL);
    qsort(keys, book_amount, sizeof(key), compare);
    gettimeofday(&tv_stop, NULL);
    time_2 = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("Быстрой по ключам: %ld мкс, %ld байт\n", time_2, memory_1 + memory_2);
    printf("Итого: с использованием доп.таблицы с ключами ");
    if (time_1 > time_2 && time_2 != 0)
        printf("+%ld%% по времени и ", time_1 / time_2 * 100);
    else
        printf("-%ld%% по времени и ", time_1 / time_2 * 100);
    printf("+%ld%% по памяти.\n", memory_2 / memory_1 * 100);    
}

void compare_sort(book books[], key keys[], int book_amount)
{
    printf(" 1 - Сортировка вставками\n");
    printf(" 2 - Быстрая сортировка\n");
    printf("Введите номер действия: ");
    char ch = 0;
    scanf("%c", &ch);
    switch (ch)
    {
    case '1':
        myflush();
        measure_sort(books, keys, book_amount);
        break;
    case '2':
        myflush();
        measure_qsort(books, keys, book_amount);
        break;
    default:
        printf("Некорректный ввод!\n");
        break;
    while (ch != '\n')
        scanf("%c", &ch);
    }   
}

void syncronize_keys(book books[], key keys[], int book_amount)
{
    for (int i = 0; i < book_amount; i++)
    {
        keys[i].index = i;
        keys[i].pages = books[i].pages;
    }
}

void sort_list(char *dst, book books[], key keys[], int book_amount)
{
    printf(" 1 - Сортировка c ключом + вывод\n");
    printf(" 2 - Сортировка без ключа\n");
    printf(" 3 - Сравнение 1 и 2\n");
    printf("Введите номер действия: ");
    char ch = 0;
    scanf("%c", &ch);
    switch (ch)
    {
    case '1':
        myflush();
        sort_with_key(keys, book_amount);
        print_list_by_key(dst, books, keys, book_amount);
        break;
    case '2':
        myflush();
        sort_without_key(books, book_amount);
        syncronize_keys(books, keys, book_amount);
        break;
    case '3':
        myflush();
        compare_sort(books, keys, book_amount);
        break;
    default:
        printf("Некорректный ввод!\n");
        break;
    while (ch != '\n')
        scanf("%c", &ch);
    }   
}