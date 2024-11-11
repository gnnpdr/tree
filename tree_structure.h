#ifndef _TREE_H_
#define _TREE_H_

#include "base_handle.h"

static const size_t START_STRS_AMT = 50;


static const size_t MAX_STR_LEN = 50;
static const size_t ONE_NODE    =  1;
static const size_t START_SIZE  = 60;  //зачем он был нужен?

struct Node 
{
    char* str;

    Node* Right;
    Node* Left;
};

struct Tree //структура дерева с корневым узлом
{
    char** database_str;
    int* string_inds;

    Node start_node;  //вот и вопрос. узел лучше, наверное, заранее инициализировать
};


Node* create_node (char *const str);

void insert_node (Node *const node);

void free (Node* node);

#endif //_TREE_H_