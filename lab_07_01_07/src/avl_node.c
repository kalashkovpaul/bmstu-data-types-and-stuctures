#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "actions.h"
#include "avl_node.h"

int file_read_avl_node(FILE *src, avl_node_t **new_node);

void avl_add_node(avl_node_t **root, avl_node_t *new_avl_node);

void free_avl(avl_node_t *root);

void find_heights(avl_node_t *root);

int file_read_avl(FILE *src, avl_node_t **root)
{
    int result = OK;
    avl_node_t *new_avl_node = NULL;
    do
    {
        result = file_read_avl_node(src, &new_avl_node);
        if (result != NOTHING)
            avl_add_node(root, new_avl_node);
    }
    while (result == OK);
    if (result != END_READ && result != NOTHING)
    {
        printf("Не удалось считать АВЛ... завершение...\n");
        free_avl(*root);
    }
    else
    {
        find_heights(*root);
        result = OK;
    }
    return result;
}

int file_read_avl_node(FILE *src, avl_node_t **new_node)
{
    int result = OK;
    char *word = NULL;
    result = file_read_word(src, &word);
    if (result != OK && result != END_READ)
        return result;
    *new_node = malloc(sizeof(avl_node_t));
    if (new_node == NULL)
    {
        free(word);
        return ERR_MEMORY;
    }
    (*new_node)->left = NULL;
    (*new_node)->right = NULL;
    (*new_node)->value = word;
    (*new_node)->height = 0;
    return result;
}

void avl_add_node(avl_node_t **root, avl_node_t *new_avl_node)
{
    if (*root == NULL)
        *root = new_avl_node;
    else
    {
        if (strcmp((*root)->value, new_avl_node->value) > 0)
        {
            if ((*root)->left == NULL)
                (*root)->left = new_avl_node;
            else
                avl_add_node(&((*root)->left), new_avl_node);
        }
        else if (strcmp((*root)->value, new_avl_node->value) < 0)
        {
            if ((*root)->right == NULL)
                (*root)->right = new_avl_node;
            else
                avl_add_node(&((*root)->right), new_avl_node);
        }
        else
            free(new_avl_node);
    }
}

void free_avl(avl_node_t *root)
{
    if (root != NULL)
    {
        avl_node_t *left = root->left;
        avl_node_t *right = root->right;
        free(root->value);
        free(root);
        free_avl(left);
        free_avl(right);
    }
}

void find_heights(avl_node_t *root)
{
    if (root != NULL)
    {
        find_heights(root->left);
        if (root->left == NULL)
            root->height = 0;
        else
            root->height = root->left->height;
        find_heights(root->right);
        if (root->right != NULL && root->right->height > root->height)
            root->height = root->right->height;
        root->height += 1;
    }
}

char get_height(avl_node_t *node)
{
    return node ? node->height : 0;
}

char get_bfactor(avl_node_t *node)
{
    return node ? (get_height(node->right) - get_height(node->left)) : 0;
}

void fix_height(avl_node_t *root)
{
    if (root)
    {
        char height_left = get_height(root->left);
        char height_right = get_height(root->right);
        root->height = (height_left > height_right ? height_left : height_right) + 1;
    }
}

avl_node_t *rotate_right(avl_node_t *node)
{
    avl_node_t *rotated = node->left;
    node->left = rotated->right;
    rotated->right = node;
    fix_height(node);
    fix_height(rotated);
    return rotated;
}

avl_node_t *rotate_left(avl_node_t *node)
{
    avl_node_t *rotated = node->right;
    node->right = rotated->left;
    rotated->left = node;
    fix_height(node);
    fix_height(rotated);
    return rotated;
}

avl_node_t *balance_node(avl_node_t *node)
{
    fix_height(node);
    if (get_bfactor(node) >= 2)
    {
        if (get_bfactor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    else if (get_bfactor(node) <= -2)
    {
        if (get_bfactor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    return node;
}

void balance(avl_node_t **root)
{
    if (root && *root) 
    {
        (*root)->left = balance_node((*root)->left);
        balance(&((*root)->left));
        (*root)->right = balance_node((*root)->right);
        balance(&((*root)->right));
        fix_height(*root);
        *root = balance_node(*root);
        fix_height(*root);
        (*root)->left = balance_node((*root)->left);
        balance(&((*root)->left));
        (*root)->right = balance_node((*root)->right);
        balance(&((*root)->right));
        fix_height(*root);  
    }
}

void print_avl_to_file(avl_node_t *root, FILE *file)
{
    if (root)
    {
        fprintf(file, "\"%s\"", root->value);
        if (root->left)
        {
            fprintf(file, "\"%s\" -> \"%s\";\n", root->value, root->left->value);
            print_avl_to_file(root->left, file);
        }
        if (root->right)
        {
            fprintf(file, "\"%s\" -> \"%s\";\n", root->value, root->right->value);
            print_avl_to_file(root->right, file);
        }
    }
}

void print_avl(avl_node_t *root)
{
    FILE *file = fopen("graphviz_avl.gv", "w");
    if (file)
    {
        fprintf(file, "digraph avl {\n");
        print_avl_to_file(root, file);
        fprintf(file, "}\n");
        fclose(file);
        system("dot -Tjpg graphviz_avl.gv -o graph_avl.jpg");
        system("feh graph_avl.jpg");
    }
}

int find_avl(avl_node_t *root, char *searched, int *found)
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
            result += find_avl(root->left, searched, found);
            if (*found == 0)
            {
                result += find_avl(root->right, searched, found);
            }
        }
    }
    return result;
}
