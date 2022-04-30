#include <stdlib.h>

#include "node.h"
#include "constants.h"

int insert_by_index(node_t **head, node_t *elem, int index)
{
    int result = OK;
    if (head == NULL || elem == NULL || index < 0)
        result = ERR_ARGS;
    if ((*head == NULL || index == 0) && result == OK)
    {
        elem->next = *head;
        *head = elem;
    }
    else if (result == OK)
    {
        node_t *tmp = *head;
        int i = 0;
        while (tmp->next != NULL && i < index - 1)
        {
            tmp = tmp->next;
            i++;
        }
        if (tmp->next == NULL && i != index - 1)
            result = ERR_ARGS;
        else if (tmp->next == NULL)
        {
            elem->next = NULL;
            tmp->next = elem;
        }
        else
        {
            elem->next = tmp->next->next;
            tmp->next = elem;
        }
    }
    return result;
}

void free_node(node_t **node)
{
    free(*node);
    *node = NULL;
}

void free_list(node_t **head)
{
    if (head != NULL && *head != NULL)
    {
        node_t *tmp = *head;
        node_t *tmp_next = tmp->next;
        do
        {
            tmp_next = tmp->next;
            free_node(&(tmp));
            tmp = tmp_next;
        }
        while (tmp_next != NULL);
        *head = NULL;
    }
}

int get_length(node_t *head)
{
    int result = 0;
    node_t *tmp = head;
    while (tmp)
    {
        tmp = tmp->next;
        result++;
    }
    return result;
}

node_t *find(node_t *head, const void *data, int (*comparator)(const void *, const void *))
{
    node_t *result = NULL;
    node_t *tmp = head;
    while (tmp && comparator(data, tmp->data) != 0)
        tmp = tmp->next;
    if (tmp != NULL)
        result = tmp;
    return result;
}

void *pop_front(node_t **head)
{
    void *result = NULL;
    if (head != NULL && *head != NULL)
    {
        result = (*head)->data;
        remove_element(head, *head);
    }
    return result;
}

void *pop_back(node_t **head)
{
    void *result = NULL;
    if (head != NULL && *head != NULL)
    {
        if ((*head)->next == NULL)
        {
            result = (*head)->data;
            free_node(head);
            *head = NULL;
        }
        else
        {
            node_t *tmp = *head;
            while (tmp->next->next != NULL)
            {
                tmp = tmp->next;
            }
            result = tmp->next->data;
            free_node(&(tmp->next));
            tmp->next = NULL;
        }
    }
    return result;
}

int push_back(node_t  **head, void *const data)
{
    int result = OK;
    node_t *new_node = NULL;
    if (head == NULL)
        result = ERR_ARGS;
    else
        new_node = malloc(sizeof(node_t));
    if (new_node && result == OK)
    {
        new_node->data = data;
        new_node->next = NULL;
        result = insert_by_index(head, new_node, get_length(*head));
    }
    else if (result == OK)
        result = ERR_MEMORY;
    return result;
}

int push_front(node_t **head, void *const data)
{
    int result = OK;
    node_t *new_node = NULL;
    if (head == NULL)
        result = ERR_ARGS;
    else
        new_node = malloc(sizeof(node_t));
    if (new_node && result == OK)
    {
        new_node->data = data;
        new_node->next = *head;
        result = insert_by_index(head, new_node, 0);
    }
    else if (result == OK)
        result = ERR_MEMORY;
    return result;
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    if (head != NULL && elem != NULL)
    {
        if ((*head == NULL && before == NULL) || *head == before)
        {
            *head = elem;
            elem->next = before;
        }
        else if (*head != NULL)
        {
            node_t *tmp = *head;
            while (tmp->next != NULL && tmp->next != before)
                tmp = tmp->next;
            if (tmp->next == before)
            {
                elem->next = before;
                tmp->next = elem;
            }
        }
    }
}

void remove_element(node_t **head, node_t *elem)
{
    if (head != NULL && *head != NULL && elem != NULL)
    {
        node_t *tmp = *head;
        if (tmp == elem)
        {
            *head = (*head)->next;
            free_node(&tmp);
        }
        else
        {
            while (tmp->next != NULL && tmp->next != elem)
                tmp = tmp->next;
            if (tmp->next == elem)
            {
                tmp->next = elem->next;
                free_node(&(elem));
            }
        }
    }
}

int copy(node_t *head, node_t **new_head)
{
    int result = OK;
    if (head == NULL || new_head == NULL)
        result = ERR_ARGS;
    else
    {
        node_t *new_node = malloc(sizeof(node_t));
        if (new_node != NULL)
        {
            *new_head = new_node;
            (*new_head)->data = head->data;
            node_t *tmp = head;
            node_t *new_tmp = *new_head;
            while (result == OK && tmp->next != NULL)
            {
                new_node = malloc(sizeof(node_t));
                new_tmp->next = new_node;
                if (new_node != NULL)
                    new_tmp->next->data = tmp->next->data;
                else
                    result = ERR_MEMORY;
                new_tmp = new_tmp->next;
                tmp = tmp->next;
            }
            new_tmp->next = NULL;
        }
        else
            result = ERR_MEMORY;
    }
    if (result == ERR_MEMORY)
        free_list(&head);
    return result;
}

void append(node_t **head_a, node_t **head_b)
{
    if (head_a != NULL && head_b != NULL)
    {
        node_t *tmp = *head_a;
        if (tmp == NULL)
            *head_a = *head_b;
        else
        {
            while (tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = *head_b;
        }
        *head_b = NULL;
    }
}

void remove_duplicates(node_t **head, int (*comparator)(const void *, const void *))
{
    if (head != NULL && *head != NULL)
    {
        node_t *tmp = *head;
        node_t *deleted = NULL;
        while (tmp->next != NULL)
        {
            if (comparator(tmp->data, tmp->next->data) == 0)
            {
                deleted = tmp;
                tmp = tmp->next;
                remove_element(head, deleted);
            }
            else
                tmp = tmp->next;
        }
    }
}

node_t *reverse(node_t *head)
{
    node_t *new_head = NULL;
    if (head != NULL)
        new_head = malloc(sizeof(node_t));
    int check = OK;
    if (new_head)
    {
        node_t *new_tmp = new_head;
        new_tmp->next = head->next;
        new_head->data = pop_back(&head);
        node_t *new_node = NULL;

        while (head != NULL)
        {
            new_node = malloc(sizeof(node_t));
            if (new_node)
            {
                new_node->data = pop_back(&(head));
            }
            else
                check = ERR_MEMORY;
            new_tmp->next = new_node;
            new_tmp = new_tmp->next;
        }
        new_tmp->next = NULL;
    }
    else
        free_node(&new_head);
    if (check != OK)
        free_list(&new_head);
    return new_head;
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (head != NULL && element != NULL && comparator != NULL)
    {
        node_t *tmp = *head;
        while (tmp != NULL && tmp->next != NULL && comparator(tmp->data, element->data) < 0)
            tmp = tmp->next;
        if (tmp != NULL && comparator(tmp->data, element->data) >= 0)
            insert(head, element, tmp);
        else if (tmp == NULL || tmp->next == NULL)
            insert(head, element, NULL);
    }
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *new_head = NULL;
    node_t *new_element = NULL;
    int check = OK;
    while (check == OK && head != NULL && comparator != NULL)
    {
        new_element = head;
        head = head->next;
        sorted_insert(&new_head, new_element, comparator);
    }
    return new_head;
}
