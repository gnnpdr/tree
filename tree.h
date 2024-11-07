#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include <assert.h>

static const size_t ONE_NODE = 1;


enum Errors
{
    ALL_RIGHT,
    FILE_ERROR,
    WRITE_ERROR,
    CLOSE_ERROR,
    CMD_ERROR,
    ALLOCATION_ERROR
};

struct Node 
{
    int data;
    Node* Right;
    Node* Left;
};

#define ALLOCATION_CHECK(buf) do                                    \
                            {                                       \
                                if (buf == 0)                       \
                                {                                   \
                                    printf("no place\n");           \
                                    error = ALLOCATION_ERROR;       \
                                    return nullptr;                 \
                                }                                   \
                            }while(0);

Node* create_node (int value);

void insert_node (Node *const node, int value);

void free (Node* node);

#endif //_TREE_H_