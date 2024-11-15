#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


#include "errors.h"

static const size_t ONE_NODE =  1;

static const size_t MAX_STR_LEN =  50;

struct Node 
{
    char* str;

    Node* Right;
    Node* Left;

    //bool is_filled;
};

/*struct NodeParameters 
{
    char* str;
    Node* node_address; 
};*/

struct Tree //структура дерева с корневым узлом
{
    //NodeParameters database_strs[MAX_STRS_AMT];  //по-другому можно. Лучше убрать
    //size_t node_amt;

    Node* start_node;  //вот и вопрос. узел лучше, наверное, заранее инициализировать
};


Errors node_ctor (Node *const node);
Errors tree_ctor (Tree *const the_tree, Node *const start_node);

Node* make_node (char* str);  //make

void tree_dtor(Tree* the_tree);

#endif //_STRUCTURE_H_