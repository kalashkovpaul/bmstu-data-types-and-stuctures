#ifndef _BOOK_H_

#define _BOOK_H_

#include "constants.h"

typedef struct
{
    char title[TITLE_MAX_LENGTH + 1];
    char publishing_house[PUBLISHER_MAX_LENGTH + 1];
    int pages;
    short state;
    union 
    {
        struct
        {
            char sector[SECTOR_MAX_LENGTH];
            int is_local;
            int is_translated;
            int year_of_publication;
        } technical;
        struct
        {
            int is_novel;
            int is_play;
            int is_poetry;
        } fiction;
        struct
        {
            int is_tales;
            int is_poetry;
        } childrens;
    } type;
} book;

typedef struct
{
    int index;
    int pages;
} key;


#endif