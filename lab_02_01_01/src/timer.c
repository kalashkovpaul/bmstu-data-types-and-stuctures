#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "constants.h"
#include "book.h"
#include "read_list.h"


void sort_list(book books[], int book_amount)
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

void measure_insection(book books[], int book_amount)
{
    int64_t time;
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    sort_list(books, book_amount);
    gettimeofday(&tv_stop, NULL);
    time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("time = %ld mcs\n", time);
}

int compare(const void *p_1, const void *p_2)
{
    const book *b_1 = p_1;
    const book *b_2 = p_2;
    return b_1->pages > b_2->pages;
}

void measure_qsort(book books[], int book_amount)
{
    int64_t time;
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    qsort(books, book_amount, sizeof(book), compare);
    gettimeofday(&tv_stop, NULL);
    time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("time = %ld mcs\n", time);
}

int main(int argc, char **argv)
{
    int check = OK;
    book books_1[MAX_BOOKS_AMOUNT] = { 0 };
    book books_2[MAX_BOOKS_AMOUNT] = { 0 };
    int book_amount = 0;
    read_list(argv[1], books_1, &book_amount);
    read_list(argv[1], books_2, &book_amount);
    if (argc == 2 && check == OK)
    {
        printf("insection: ");
        measure_insection(books_1, book_amount);
        printf("qsort: ");
        measure_qsort(books_2, book_amount); 
    }
    else
        check = OK;
    return check;
}


