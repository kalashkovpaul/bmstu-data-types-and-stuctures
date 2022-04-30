#include <stdio.h>

#include "actions.h"
#include "stack_array.h"
#include "stack_node.h"

void push_element(info *information)
{
    char answer = 0;
    int check = 0;
    printf("В какой стек добавляем элементы?\n");
    printf(" 1 - В стек-массив\n");
    printf(" 2 - В стек-список\n");
    printf("Введите действие: ");
    check = scanf("%c", &answer);
    if (check == 1)
    {
        switch (answer)
        {
        case '1':
            stack_array_push(information->stack_array);
            break;
        case '2':
            stack_node_push(information->stack_node);
            break;
        default:
            printf("Неверное действие! Возвращаемся в меню...\n");
            break;
        }
        printf("\n");
    }

}

void pop_element(info *information)
{
    char answer = 0;
    int check = 0;
    printf("Из какого стека вытаскиваем элемент?\n");
    printf(" 1 - Из стека-массива\n");
    printf(" 2 - Из стека-списка\n");
    printf("Введите действие: ");
    check = scanf("%c", &answer);
    if (check == 1)
    {
        switch (answer)
        {
        case '1':
            stack_array_pop(information->stack_array);
            break;
        case '2':
            stack_node_pop(information->stack_node);
            break;
        default:
            printf("Неверное действие! Возвращаемся в меню...\n");
            break;
        }
        printf("\n");
    }
}

void print(info *information)
{
    char answer = 0;
    int check = 0;
    printf("Какой стек выводим?\n");
    printf(" 1 - Стек-массив\n");
    printf(" 2 - Стек-список\n");
    printf("Введите действие: ");
    check = scanf("%c", &answer);
    if (check == 1)
    {
        switch (answer)
        {
        case '1':
            stack_array_print(information->stack_array);
            break;
        case '2':
            stack_node_print(information->stack_node);
            break;
        default:
            printf("Неверное действие! Возвращаемся в меню...\n");
            break;
        }
        while (answer != '\n' && answer != EOF)
        {
            scanf("%c", &answer);
        }
    }
}

void free_data(info *information)
{
    stack_array_free(information->stack_array);
    stack_node_free(information->stack_node);
    printf("\n");
}

void study_time(info *information)
{
    free_data(information);
    char answer = 0;
    int check = 0;
    printf("Время работы операций над каким стеком измеряем?\n");
    printf(" 1 - Над стеком-массивом\n");
    printf(" 2 - Над стеком-списком\n");
    printf("Введите действие: ");
    check = scanf("%c", &answer);
    if (check == 1)
    {
        switch (answer)
        {
        case '1':
            stack_array_study_time(information->stack_array);
            break;
        case '2':
            stack_node_study_time(information->stack_node);
            break;
        default:
            printf("Неверное действие! Возвращаемся в меню...\n");
            break;
        }
        while (answer != '\n' && answer != EOF)
        {
            scanf("%c", &answer);
        }
    }
}

void end_program(info *information)
{
    free_data(information);
    printf("Спасибо, что пользовались программой :)\n");
}