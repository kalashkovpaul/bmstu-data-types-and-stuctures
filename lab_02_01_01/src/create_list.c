#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "book.h"

void write_new_book(FILE *dst, int i)
{
    char name[] = "Name";
    char house[] = "Publishing house";
    int pages = rand() % 1000;
    char *possible_sectors[] = {"Programming", "Math", "Linear algebra", "Geometry", "Calculus", "Data", "Web-development", "Testing"};
    int possible_sectors_amount = 8;
    fprintf(dst, "%s_%d\n", name, i);
    fprintf(dst, "%s_%d\n", house, i);
    fprintf(dst, "%d\n", pages);
    int type = rand() % 3;
    if (type == 0)
    {
        fprintf(dst, "Technical\n");
        type = rand() % possible_sectors_amount;
        fprintf(dst, "%s\n", possible_sectors[type]);
        type = rand() % 2;
        if (type == 1)
            fprintf(dst, "National\n");
        else
            fprintf(dst, "Foreign\n");
        type = rand() % 2;
        if (type == 1)
            fprintf(dst, "Translated\n");
        else
            fprintf(dst, "Untranslated\n");
        type = rand() % 230 + 1800;
        fprintf(dst, "%d\n", type);
    }
    else if (type == 1)
    {
        fprintf(dst, "Fiction\n");
        type = rand() % 2;
        if (type == 1)
            fprintf(dst, "Novel\n");
        else
            fprintf(dst, "Not novel\n");
        type = rand() % 2;
        if (type == 1)
            fprintf(dst, "Play\n");
        else
            fprintf(dst, "Not play\n");
        type = rand() % 2;
        if (type == 1)
            fprintf(dst, "Poetry\n");
        else
            fprintf(dst, "Prose\n");
    }
    else
    {
        fprintf(dst, "Children's\n");
        type = rand() % 2;
        if (type == 1)
            fprintf(dst, "Tales\n");
        else
            fprintf(dst, "Not tales\n");
        type = rand() % 2;
        if (type == 1)
            fprintf(dst, "Children's poetry\n");
        else
            fprintf(dst, "Children's prose\n");
    }
}

int main(int argc, char **argv)
{
    int check = OK;
    FILE *dst = fopen(argv[1], "w");
    if (dst == NULL && argc == 3)
        check = -1;
    if (check == OK)
    {
        int books_amount = atoi(argv[2]);
        for (int i = 0; i < books_amount; i++)
            write_new_book(dst, i);
    }
    return check;
}