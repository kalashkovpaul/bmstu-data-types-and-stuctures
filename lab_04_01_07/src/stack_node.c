#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "stack_node.h"

static int stack_node_push_single_element(stack_node_t *stack);

static int stack_node_pop_single_element(stack_node_t *stack);

static int initialize_stack(stack_node_t *stack);

static void delete_from_free_space(stack_node_t *stack, struct node_t *new_node);

static void free_node(struct node_t **node);

static void study_push_time(stack_node_t *stack);
 
static void study_pop_time(stack_node_t *stack);

static void pop(stack_node_t *stack);

void stack_node_push(stack_node_t *stack)
{
    int additional_amount = 0, check = 0;
    char end = 0;
    printf("Введите количество добавляемых элементов: ");
    check = scanf("%d%c", &additional_amount, &end);
    if (check == 2 && additional_amount > 0)
    {
        check = OK;
        for (int i = 0; i < additional_amount && check == OK; i++)
            check = stack_node_push_single_element(stack);
        printf("Сделано!\n");
    }
    else
        printf("Некорректный ввод!\n");
}

static int stack_node_push_single_element(stack_node_t *stack)
{
    int check = OK;
    if (stack == NULL || stack->pointer_stack == NULL || stack->length <= 0)
        check = initialize_stack(stack);
    else
    {
        struct node_t *new_node = calloc(1, sizeof(struct node_t));
        if (new_node && check == OK)
        {
            new_node->next = stack->pointer_stack;
            new_node->value = new_node;
            stack->pointer_stack = new_node;
            stack->length++;
            delete_from_free_space(stack, new_node);
        }
        else
        {
            check = ERR_MEMORY;
            printf("Не удалось выделить память!\n");
        }
    }
    return check;
}

static int initialize_stack(stack_node_t *stack)
{
    int check = OK;
    struct node_t *new_node = calloc(1, sizeof(struct node_t));
    if (new_node)
    {
        stack->pointer_stack = new_node;
        stack->pointer_stack->next = NULL;
        stack->pointer_stack->value = new_node;
        stack->length = 1;
    }
    else
    {
        check = ERR_MEMORY;
        printf("Не удалось выделить память!\n");
    }
    return check;
}

static void delete_from_free_space(stack_node_t *stack, struct node_t *new_node)
{
    if (stack->free_space_list != NULL && stack->free_space_list->value == new_node)
        stack->free_space_list = stack->free_space_list->next;

    struct node_t *tmp = stack->free_space_list;
    struct node_t *next = NULL;

    while (tmp != NULL && tmp->next != NULL)
    {
        next = tmp->next;
        if (next->value == new_node)
            tmp->next = next->next;
        tmp = tmp->next;
    }
}

void stack_node_pop(stack_node_t *stack)
{
    int popped_amount = 0, check = 0;
    char end = 0;
    if (stack == NULL || stack->pointer_stack == NULL || stack->length <= 0)
    {
        printf("Не получится, стек пуст!\n");
        char ch = 0;
        while (ch != '\n')
            scanf("%c", &ch);
    }
    else
    {
        printf("Введите количество доставаемых элементов: ");
        check = scanf("%d%c", &popped_amount, &end);
        if (check == 2 && popped_amount > 0 && popped_amount <= stack->length)
        {
            check = OK;
            for (int i = 0; i < popped_amount && check == OK; i++)
                check = stack_node_pop_single_element(stack);
            printf("Сделано!\n");
        }
        else
            printf("Некорректный ввод!\n");
    }
}

static int stack_node_pop_single_element(stack_node_t *stack)
{
    int check = OK;
    printf("Извлечённый элемент: значение %lld, адрес %lld\n", ((long long int)(stack->pointer_stack->value)), (long long int)(stack->pointer_stack));
    struct node_t *new_node = calloc(1, sizeof(struct node_t));
    if (new_node)
    {
        if (stack->free_space_list == NULL)
        {
            stack->free_space_list = new_node;
            stack->free_space_list->value = stack->pointer_stack->value;
            stack->free_space_list->next = NULL;
        }
        else
        {
            new_node->value = stack->pointer_stack->value;
            new_node->next = (struct node_t *) stack->free_space_list;
            stack->free_space_list = new_node;
        }
    }
    else
    {
        check = ERR_MEMORY;
        printf("Не удалось выделить память!\n");
    }
    struct node_t *tmp = stack->pointer_stack->next;
    free_node(&(stack->pointer_stack));
    stack->pointer_stack = tmp;  
    return check;
}

void stack_node_print(stack_node_t *stack)
{
    struct node_t *tmp = NULL;
    printf("Стек:\n");
    if (stack->pointer_stack == NULL)
    {
        printf("Пуст\n");
    }
    else
    {
        tmp = stack->pointer_stack;
        while (tmp != NULL)
        {
            printf("Элемент: значение %lld, адрес %lld\n", (long long int)(tmp->value), (long long int)(tmp));
            tmp = tmp->next;
        }
    }
    printf("\n");
    printf("Список свободных областей:\n");
    if (stack->free_space_list == NULL)
    {
        printf("Пуст\n");
    }
    else
    {
        tmp = stack->free_space_list;
        while (tmp != NULL)
        {
            printf("Адрес: %lld\n", (long long int)(tmp->value));
            tmp = tmp->next;
        }
    }
    printf("\n");
}

void stack_node_free(stack_node_t *stack)
{
    if (stack != NULL)
    {
        stack->length = 0;
        struct node_t *tmp = stack->pointer_stack;
        while (tmp != NULL)
        {
            tmp = stack->pointer_stack->next;
            free_node(&(stack->pointer_stack));
            stack->pointer_stack = tmp;
        }
        tmp = stack->free_space_list;
        while (tmp != NULL)
        {
            tmp = stack->free_space_list->next;
            free_node(&(stack->free_space_list));
            stack->free_space_list = tmp;
        }
        printf("Сделано!\n");
    }
}

static void free_node(struct node_t **node)
{
    (*node)->next = NULL;
    (*node)->value = NULL;
    free(*node);
    *node = NULL;
}

void stack_node_study_time(stack_node_t *stack)
{
    study_push_time(stack);
    study_pop_time(stack);
    printf("Нам %d элементов памяти использовано: %ld байт\n", STUDY_TIME_ITERATIONS, stack->length * sizeof(struct node_t));
}

static void study_push_time(stack_node_t *stack)
{
    clock_t time = 0;
    for (int i = 0; i < STUDY_TIME_ITERATIONS; i++)
    {
        clock_t begin = clock();
        stack_node_push_single_element(stack);
        time += clock() - begin;
    }
    printf("Время работы добавление элемента в стек-список = %ld нс\n", (time * 1000000000 / CLOCKS_PER_SEC) / STUDY_TIME_ITERATIONS);
}

static void study_pop_time(stack_node_t *stack)
{
    clock_t time = 0;
    for (int i = 0; i < STUDY_TIME_ITERATIONS; i++)
    {
        clock_t begin = clock();
        pop(stack);
        time += clock() - begin;
    }
    printf("Время работы исключения элемента из стека-списка = %ld нс\n", (time * 1000000000 / CLOCKS_PER_SEC) / STUDY_TIME_ITERATIONS);
}

static void pop(stack_node_t *stack)
{    
    struct node_t *tmp = stack->pointer_stack->next;
    free_node(&(stack->pointer_stack));
    stack->pointer_stack = tmp;  
}