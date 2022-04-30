#ifndef _INFO_H_

#define _INFO_H_

typedef struct
{
    array_queue_t *array_queue;
    node_queue_t *node_queue;
    int interval_min;
    int interval_max;
    int process_min;
    int process_max;
} info;

#endif