#ifndef STACK_NODE_H_

#define STACK_NODE_H_

struct node_t
{
    struct node_t *value;
    struct node_t *next;
};

typedef struct
{
    struct node_t *pointer_stack;
    int length;
    struct node_t *free_space_list;
} stack_node_t;

void stack_node_push(stack_node_t *stack);

void stack_node_pop(stack_node_t *stack);

void stack_node_print(stack_node_t *stack);

void stack_node_free(stack_node_t *stack);

void stack_node_study_time(stack_node_t *stack);

#endif