#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stack_array.h"
#include "constants.h"

static int stack_array_push_single_element(stack_array_t *stack);

static int add(stack_array_t *stack, int element);

static int initialize_stack(stack_array_t *stack);

static int expand_stack(stack_array_t *stack);

static void append(stack_array_t *stack, int element);

static int stack_array_pop_single_element(stack_array_t *stack);

static void pop(stack_array_t *stack);

static void study_push_time(stack_array_t *stack);

static void study_pop_time(stack_array_t *stack);

void stack_array_push(stack_array_t *stack)
{
    int additional_amount = 0, check = 0;
    char end = 0;
    printf("Введите количество добавляемых элементов: ");
    check = scanf("%d%c", &additional_amount, &end);
    if (check == 2 && additional_amount > 0)
    {
        check = OK;
        for (int i = 0; i < additional_amount && check == OK; i++)
            check = stack_array_push_single_element(stack);
        printf("Сделано!\n");
    }
    else
        printf("Некорректный ввод!\n");
}

static int stack_array_push_single_element(stack_array_t *stack)
{
    printf("Введите добавляемый элемент (адрес): ");
    int element = 0, check = 0;
    char end = 0;
    check = scanf("%d%c", &element, &end);
    if (check == 2 && element >= 0)
        check = add(stack, element);
    else
    {
        printf("Некорректный ввод!\n");
        check = ERR_READ;
    }
    while (end != '\n' && end != EOF)
        scanf("%c", &end);
    return check;
}

static int add(stack_array_t *stack, int element)
{
    int check = OK;
    if (stack == NULL || stack->beginning == NULL || stack->length <= 0)
        check = initialize_stack(stack);
    if (stack->pointer_stack == stack->beginning + stack->length - 1)
        check = expand_stack(stack);
    if (check == OK)
        append(stack, element);
    else
        printf("Не удалось выделить память!\n");
    return check;
}

static int initialize_stack(stack_array_t *stack)
{
    int check = OK;
    int *array = malloc(STACK_ARRAY_INIT_SIZE * sizeof(int));
    if (array)
    {
        stack->beginning = array;
        stack->length = STACK_ARRAY_INIT_SIZE;
        stack->pointer_stack = array - 1;
    }
    else
        check = ERR_MEMORY;
    return check;
}

static int expand_stack(stack_array_t *stack)
{
    int check = OK;
    int *changed_array = realloc(stack->beginning, stack->length * STACK_ARRAY_COEF * sizeof(int));
    if (changed_array)
    {
        stack->beginning = changed_array;
        stack->pointer_stack = stack->beginning + stack->length - 1;
        stack->length *= STACK_ARRAY_COEF;
    }
    else
        check = ERR_MEMORY;
    return check;
}

static void append(stack_array_t *stack, int element)
{
    stack->pointer_stack++;
    *(stack->pointer_stack) = element;
}

void stack_array_pop(stack_array_t *stack)
{
    int popped_amount = 0, check = 0;
    char end = 0;
    if (stack == NULL || stack->beginning == stack->pointer_stack + 1 || stack->length == 0)
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
        if (check == 2 && popped_amount > 0 && popped_amount <= stack->pointer_stack - stack->beginning + 1)
        {
            check = OK;
            for (int i = 0; i < popped_amount && check == OK; i++)
                check = stack_array_pop_single_element(stack);
            printf("Сделано!\n");
        }
        else
            printf("Некорректный ввод!\n");
    }
}

static int stack_array_pop_single_element(stack_array_t *stack)
{
    int check = OK;
    if (stack->beginning == NULL || stack->length <= 0 || stack->beginning == stack->pointer_stack + 1)
        check = ERR_EMPTY_STACK;
    if (check == OK)
        pop(stack);
    return check;
}

static void pop(stack_array_t *stack)
{
    printf("Извлечённый элемент: %d\n", *(stack->pointer_stack));
    stack->pointer_stack--;
}

void stack_array_print(stack_array_t *stack)
{
    if (stack == NULL || stack->beginning == NULL || stack->beginning == stack->pointer_stack + 1 || stack->length == 0)
    {
        printf("Не получится, стек пуст!\n");
    }
    else
    {
        printf("Содержание стека:\n");
        int *current = stack->pointer_stack;
        while (current >= stack->beginning)
        {
            printf("Элемент: %d\n", *current);
            current--;
        }
        printf("Сделано!\n");
    }
}

void stack_array_free(stack_array_t *stack)
{
    free(stack->beginning);
    stack->length = 0;
    stack->beginning = NULL;
}

void stack_array_study_time(stack_array_t *stack)
{
    study_push_time(stack);
    study_pop_time(stack);
    printf("Нам %d элементов памяти использовано: %ld байт\n", STUDY_TIME_ITERATIONS, stack->length * sizeof(int));
}

static void study_push_time(stack_array_t *stack)
{
    clock_t time = 0;
    for (int i = 0; i < STUDY_TIME_ITERATIONS; i++)
    {
        clock_t begin = clock();
        add(stack, i);
        time += clock() - begin;
    }
    printf("Время работы добавление элемента в стек-массив = %ld нс\n", (time * 1000000000 / CLOCKS_PER_SEC) / STUDY_TIME_ITERATIONS);
}

static void study_pop_time(stack_array_t *stack)
{
    clock_t time = 0;
    for (int i = 0; i < STUDY_TIME_ITERATIONS; i++)
    {
        clock_t begin = clock();
        stack->pointer_stack--;
        time += clock() - begin;
    }
    printf("Время работы исключения элемента из стек-массив = %ld нс\n", (time * 1000000000 / CLOCKS_PER_SEC) / STUDY_TIME_ITERATIONS);
}