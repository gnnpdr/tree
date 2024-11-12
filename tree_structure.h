#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include "base_handle.h"

static const size_t ONE_NODE    =  1;

struct Node 
{
    char* str;

    Node* Right;
    Node* Left;

    bool is_filled;
};

struct NodeParameters 
{
    char* str;
    Node* node_address; 
};

struct Tree //структура дерева с корневым узлом
{
    NodeParameters database_strs[MAX_STRS_AMT];
    size_t node_amt;

    Node* start_node;  //вот и вопрос. узел лучше, наверное, заранее инициализировать
};


Errors node_ctor (Node *const node);
Errors tree_ctor (Tree *const the_tree, Node *const start_node);

Node* create_node (char* str);

void tree_dtor(Tree* the_tree);

#endif //_STRUCTURE_H_