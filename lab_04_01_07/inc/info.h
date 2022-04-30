#ifndef _INFO_H_

#define _INFO_H_

#include "stack_array.h"
#include "stack_node.h"

typedef struct
{
    stack_array_t *stack_array;
    stack_node_t *stack_node;
} info;

#endif