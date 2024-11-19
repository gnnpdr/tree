#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "user_interaction.h"

enum Ways
{
    FREE = 0,
    NOT_LEFT = 1
};

void make_definition (Tree* the_tree);
void find_difference(Tree* the_tree);

#endif //_FUNCTIONS_H_