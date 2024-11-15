/*#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "draw_tree.h"

enum Ways
{
    FREE = 0,
    NOT_LEFT = 1
};

static const char QUESTION_MARK = '?';

Node* insert_node (Node *const node, char* str);
void make_base_tree (Tree* the_tree);
void database_tree_fill(Tree *const the_tree, const Input *const base_text);
bool find_question_mark(char* str);

char* make_definition (Tree* the_tree);

#endif //_FUNCTIONS_H_*/