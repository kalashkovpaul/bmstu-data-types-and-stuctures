#ifndef NODE_H_

#define NODE_H_

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *));

void *pop_front(node_t **head);

void *pop_back(node_t **head);

int push_back(node_t  **head, void *const data);

int push_front(node_t **head, void *const data);

void insert(node_t **head, node_t *elem, node_t *before);

void remove_element(node_t **head, node_t *elem);

int copy(node_t *head, node_t **new_head);

void append(node_t **head_a, node_t **head_b);

void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *));

node_t *reverse(node_t *head);

void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *));

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

void free_list(node_t **head);

#endif
