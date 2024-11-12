#ifndef _DRAW_H_
#define _DRAW_H_

#include "tree_structure.h"

static const size_t INPUT_FILE_SIZE = 5000;

void print (const Node* const node);
Errors graph_dump (const Node *const node, const Node *const definite_node);

#endif //_DRAW_H_