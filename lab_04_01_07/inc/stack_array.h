#ifndef STACK_ARRAY_H_

#define STACK_ARRAY_H_

typedef struct
{
    int *pointer_stack;
    int *beginning;
    int length;
} stack_array_t;

void stack_array_push(stack_array_t *stack);

void stack_array_pop(stack_array_t *stack);

void stack_array_print(stack_array_t *stack);

void stack_array_free(stack_array_t *stack);

void stack_array_study_time(stack_array_t *stack);

#endif