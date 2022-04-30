#ifndef QUEUE_H_

#define QUEUE_H_

typedef struct node node_t;

struct node
{
    int value;
    node_t *next;
};

typedef struct
{
    node_t *p_in;
    node_t *p_out;
} node_queue_t;

typedef struct
{
    int *p_in;
    int *p_out;
    int *p_start;
    int *p_end;
} array_queue_t;

typedef struct
{
    array_queue_t *array_queue;
    node_queue_t *node_queue;
    int interval_min;
    int interval_max;
    int process_min;
    int process_max;
} info;

void process_array(info *information);

void process_node(info *information, int with_info);

void free_node_queue(node_queue_t *node_queue);

void study_time_array(array_queue_t *array_queue);

void study_time_node(node_queue_t *node_queue);

void study_average_time(info *information);

#endif