#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "actions.h"
#include "node.h"


void print_information()
{
    printf("Лабораторная работа №7, ТиСД, Вариант 7. Обработка графов\n");
    printf("\n");
    printf("Данная программа предоставляет возможность, использовав данные из файла,\n");
    printf("построить граф (систему с двусторонними дорогами - путь между двумя \n");
    printf("городами в противоположные стороны может быть разным), а также\n");
    printf("для каждой пары вершин найти длину кратчайшего пути между ними\n");    
}

int file_read_line(FILE* src, char **str)
{
    int check = OK;
    int allocated_length = INIT_SIZE;
    *str = malloc(allocated_length * sizeof(char));
    if (*str)
    {
        char ch = 0;
        char *tmp = NULL;
        int i = 0;
        while (ch != '\n' && check != ERR_MEMORY && !feof(src))
        {
            fscanf(src, "%c", &ch);
            check = OK;
            if (i == allocated_length)
            {
                allocated_length *= ARRAY_COEF;
                tmp = realloc(*str, allocated_length * sizeof(char));
                if (tmp)
                    *str = tmp;
                else
                {
                    check = ERR_MEMORY;
                }
            }
            if (check == OK)
                (*str)[i++] = ch;
        }
        if (ch != '\n' || i == 1)
        {
            free(*str);
            *str = NULL;
            check = ERR_WITHOUT_END;
        }
        else if (check == OK)
            (*str)[i - 1] = 0;
    }
    else
        check = ERR_MEMORY;
    return check;
}

int file_read_word(FILE* src, char **str)
{
    int check = OK;
    int allocated_length = INIT_SIZE;
    *str = malloc(allocated_length * sizeof(char));
    if (*str)
    {
        char ch = 0;
        char *tmp = NULL;
        int i = 0;
        while (ch != '\n' && ch != ' ' && check != ERR_MEMORY && !feof(src))
        {
            fscanf(src, "%c", &ch);
            check = OK;
            if (i == allocated_length)
            {
                allocated_length *= ARRAY_COEF;
                tmp = realloc(*str, allocated_length * sizeof(char));
                if (tmp)
                    *str = tmp;
                else
                {
                    check = ERR_MEMORY;
                }
            }
            if (check == OK)
                (*str)[i++] = ch;
        }
        if (i == 1)
        {
            free(*str);
            *str = NULL;
            check = NOTHING;
        }
        else if (check == OK)
        {
            (*str)[i - 1] = 0;
            if (feof(src))
                check = END_READ;
        }
    }
    else
        check = ERR_MEMORY;
    return check;
}
/*
void study_time(bst_node_t *bst, avl_node_t *avl, node_t *hash[], FILE *file, char *filename)
{
    double bst_time = 0, avl_time = 0, hash_time = 0, file_time = 0;
    struct timeval tv_start, tv_stop;
    char *searched = NULL;
    int found  = 0;
    int compare_amount = 0;
    int elements_amount = hash_find_elements(hash);
    int critical = 0;
    int simple_amount = 5;
    int simple[] = { 17, 13, 17, 19, 23 };
    printf("Всего элементов: %d\n", elements_amount);
    printf("Введите слово, которое будем искать: ");
    if (file_read_word(stdin, &searched) == OK)
    {
        printf("Принято. Введите число сравнений, при превышении которого будем \nреструктуризировать хеш-таблицу: ");
        if (scanf("%d", &critical) != 1)
        {
            printf("Нехорошо вводить некорректные данные. Завершение...\n");
            return ;
        }
        for (int i = 0; i < STUDY_TIME_ITERATIONS; i++)
        {
            gettimeofday(&tv_start, NULL);
            compare_amount = find_bst(bst, searched, &found);
            gettimeofday(&tv_stop, NULL);
            bst_time += (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }
        if (found)
            printf("Двоичное дерево поиска: найдено, сделано %d сравнений\n", compare_amount);
        else
            printf("Двоичное дерево поиска: не найдено, сделано %d сравнений\n", compare_amount);
        found = 0;
        for (int i = 0; i < STUDY_TIME_ITERATIONS; i++)
        {
            gettimeofday(&tv_start, NULL);;
            compare_amount = find_avl(avl, searched, &found);
            gettimeofday(&tv_stop, NULL);
            avl_time += (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }
        if (found)
            printf("АВЛ дерево: найдено, сделано %d сравнений\n", compare_amount);
        else
            printf("АВЛ дерево: не найдено, сделано %d сравнений\n", compare_amount);
        found = 0;
        int i = 0;
        node_t *tmp = hash[i];
        char *word = NULL;
        compare_amount = 0;
        int try = 0;
        while ((compare_amount == 0 || compare_amount > critical) && try < simple_amount)
        {
            hash_time = 0;
            for (int j = 0; j < STUDY_TIME_ITERATIONS; j++)
            {
                gettimeofday(&tv_start, NULL);
                compare_amount = 0;
                found = 0;
                i = str_hash(searched, simple[try]) % ARRAY_SIZE;
                tmp = hash[i];
                while (tmp && !found)
                {
                    word = tmp->data;
                    if (strcmp(word, searched) == 0)
                    {
                        compare_amount++;
                        found = 1;
                        break;
                    }
                    else
                    {
                        compare_amount++;
                        tmp = tmp->next;
                    }
                }
                gettimeofday(&tv_stop, NULL);
                hash_time += (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            }
            if (compare_amount > critical)
            {
                try++;  
                free_hash_table(hash);
                for (int i = 0; i < ARRAY_SIZE; i++)
                    hash[i] = NULL;
                file_create_hash_table(file, hash, simple[try]);
                printf("Реструтурировали таблицу. \n");
                print_hash_table(hash);
                fclose(file);
                file = fopen(filename, "r");  
            }
        }
        if (found)
            printf("Хеш-таблица: найдено, сделано %d сравнений\n", compare_amount);
        else
            printf("Хеш-таблица: не найдено, сделано %d сравнений\n", compare_amount);
        found = 0;
        int check = OK;
        size_t file_data = 0;
        for (int i = 0; i < STUDY_TIME_ITERATIONS; i++)
        {
            file_time = 0;
            compare_amount = 0;
            found = 0;
            gettimeofday(&tv_start, NULL);
            do
            {
                check = file_read_word(file, &word);
                if (check == OK || check == END_READ)
                {
                    compare_amount++;
                    if (strcmp(word, searched) == 0)
                    {
                        found = 1;
                    }
                }
                free(word);
                word = NULL;
            }
            while ((check == OK) && !found);
            fclose(file);
            file = fopen(filename, "r");  
            gettimeofday(&tv_stop, NULL);
            file_time += (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }
        fclose(file);
        file = fopen(filename, "r");
        do
        {
            check = file_read_word(file, &word);
            file_data += strlen(word);
            free(word);
            word = NULL;
        }
        while (check == OK);
        if (found)
            printf("Поиск по файлу: найдено, сделано %d сравнений\n", compare_amount);
        else
            printf("Поиск по файлу: не найдено, сделано %d сравнений\n", compare_amount);
        printf("\n");
        printf("Сравнение структур данных:\n");
        printf("ДДП: время поиска %lf нс, памяти использовано %ld байт\n", \
        (bst_time * 1000) / STUDY_TIME_ITERATIONS, elements_amount * sizeof(bst_node_t));
        printf("АВЛ дерево: время поиска %lf нс, памяти использовано %ld байт\n", \
        (avl_time * 1000) / STUDY_TIME_ITERATIONS, elements_amount * sizeof(avl_node_t));
        printf("Хеш-таблица: время поиска %lf нс, памяти использовано %ld байт\n", \
        (hash_time * 1000) / STUDY_TIME_ITERATIONS, elements_amount * sizeof(bst_node_t *));
        printf("Файл: время поиска %lf нс, памяти использовано %ld байт\n", \
        (file_time * 1000) / STUDY_TIME_ITERATIONS, file_data * sizeof(char));
    }
}
*/

void print_goodbye()
{
    printf("\n");
    printf("Спасибо, что пользовались данной программой...)\n");
    printf("\n");
}
