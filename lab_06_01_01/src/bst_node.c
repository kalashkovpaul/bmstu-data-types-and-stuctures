#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "actions.h"
#include "bst_node.h"

int file_read_bst_node(FILE *src, bst_node_t **new_node);

void bst_add_node(bst_node_t **root, bst_node_t *new_bst_node);

void free_bst(bst_node_t *root);

int file_read_bst(FILE *src, bst_node_t **root)
{
    int result = OK;
    bst_node_t *new_bst_node = NULL;
    do
    {
        result = file_read_bst_node(src, &new_bst_node);
        if (result != NOTHING)
            bst_add_node(root, new_bst_node);
    }
    while (result == OK);
    if (result != END_READ && result != NOTHING)
    {
        printf("%d\n", result);
        printf("Не удалось считать ДДП... завершение...\n");
        free_bst(*root);
    }
    else
        result = OK;
    return result;
}

int file_read_bst_node(FILE *src, bst_node_t **new_node)
{
    int result = OK;
    char *word = NULL;
    result = file_read_word(src, &word);
    if (result != OK && result != END_READ)
        return result;
    *new_node = malloc(sizeof(bst_node_t));
    if (new_node == NULL)
    {
        free(word);
        return ERR_MEMORY;
    }
    (*new_node)->left = NULL;
    (*new_node)->right = NULL;
    (*new_node)->value = word;
    return result;
}

void bst_add_node(bst_node_t **root, bst_node_t *new_bst_node)
{
    if (*root == NULL)
        *root = new_bst_node;
    else
    {
        if (strcmp((*root)->value, new_bst_node->value) > 0)
        {
            if ((*root)->left == NULL)
                (*root)->left = new_bst_node;
            else
                bst_add_node(&((*root)->left), new_bst_node);
        }
        else if (strcmp((*root)->value, new_bst_node->value) < 0)
        {
            if ((*root)->right == NULL)
                (*root)->right = new_bst_node;
            else
                bst_add_node(&((*root)->right), new_bst_node);
        }
        else
            free(new_bst_node);
    }
}

void free_bst(bst_node_t *root)
{
    if (root != NULL)
    {
        bst_node_t *left = root->left;
        bst_node_t *right = root->right;
        free(root->value);
        free(root);
        free_bst(left);
        free_bst(right);
    }
}

void print_bst_to_file(bst_node_t *root, FILE *file)
{
    if (root)
    {
        fprintf(file, "\"%s\"", root->value);
        if (root->left)
        {
            fprintf(file, "\"%s\" -> \"%s\";\n", root->value, root->left->value);
            print_bst_to_file(root->left, file);
        }
        if (root->right)
        {
            fprintf(file, "\"%s\" -> \"%s\";\n", root->value, root->right->value);
            print_bst_to_file(root->right, file);
        }
    }
}

void print_bst(bst_node_t *root)
{
    FILE *file = fopen("graphviz_bst.gv", "w");
    if (file)
    {
        fprintf(file, "digraph bst {\n");
        print_bst_to_file(root, file);
        fprintf(file, "}\n");
        fclose(file);
        system("dot -Tjpg graphviz_bst.gv -o graph_bst.jpg");
        system("feh graph_bst.jpg");
    }
}

int find_bst(bst_node_t *root, char *searched, int *found)
{
    int result = 0;
    if (root)
    {
        if (strcmp(root->value, searched) == 0)
        {
            *found = 1;
            return 1;
        }
        else
        {
            result = 1;
            result += find_bst(root->left, searched, found);
            if (*found == 0)
            {
                result += find_bst(root->right, searched, found);
            }
        }
    }
    return result;
}