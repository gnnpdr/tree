#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


#include "errors.h"

static const size_t ONE_NODE =  1;

static const size_t MAX_STR_LEN =  100;

struct Node 
{
    char* str;

    Node* Right;
    Node* Left;
};


struct Tree //структура дерева с корневым узлом
{
    Node* start_node;
};

Errors node_ctor (Node *const node);
Errors tree_ctor (Tree *const the_tree, Node *const start_node);

Node* make_node (char* str);

void tree_dtor(Tree* the_tree);

#endif //_STRUCTURE_H_