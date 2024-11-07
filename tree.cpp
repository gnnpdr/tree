#include <stdio.h>

#include "tree.h"

Node* create_node (int value)
{
    Errors error = ALL_RIGHT;

    Node* new_node = (Node*)calloc(ONE_NODE, sizeof(Node));
    ALLOCATION_CHECK (new_node)

    new_node->data = value;

    return new_node;
}

void insert_node (Node *const node, int value)
{
    assert (node);

    if (value < node->data)
    {
        if(node->Left)
            insert_node (node->Left, value);
        else
            node->Left = create_node (value);
    } 
    else
    {
        if(node->Right)
            insert_node (node->Right, value);
        else
            node->Right = create_node (value);
    }
}

void free (Node* node)
{
    free(node);
}