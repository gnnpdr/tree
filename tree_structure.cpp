#include <stdio.h>

#include "tree_structure.h"

Errors node_ctor (Node *const node)
{
    assert(node);

    char* str = (char*)calloc(MAX_STR_LEN, sizeof(char));
    ALLOCATION_CHECK (str)

    node->str = str;  //дает место для записи строки

    //node->is_filled = false;  //показывает программе, что идти не надо, там уже все значения заняты

    return ALL_RIGHT;
}

Errors tree_ctor (Tree *const the_tree, Node *const start_node)
{
    assert(the_tree);

    //char** strs = (char**)calloc(MAX_STRS_AMT, sizeof(char*));
    //ALLOCATION_CHECK(strs)

    //the_tree->database_str = strs;
    the_tree->start_node = start_node;

    return ALL_RIGHT;
}

Node* make_node (char* str)
{
    Node* new_node = (Node*)calloc(ONE_NODE, sizeof(Node));
    //сюда бы проверку, но возвращаемое значение не подходит
    new_node->str = str;

    return new_node;
}


void tree_dtor(Tree* the_tree)
{
    //free(the_tree->database_str);
    free(the_tree->start_node);
}