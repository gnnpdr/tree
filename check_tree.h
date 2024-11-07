#ifndef _CHECK_H_
#define _CHECK_H_

#include "tree.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

static const size_t MAX_STR_LEN     =  50;
static const size_t INPUT_FILE_SIZE = 5000;

enum Errors
{
    ALL_RIGHT,
    FILE_ERROR,
    WRITE_ERROR,
    CLOSE_ERROR,
    CMD_ERROR,
    ALLOCATION_ERROR
};

#define FILE_CHECK(file)    do                                      \
                            {                                       \
                                if (file == nullptr)                \
                                {                                   \
                                    printf("file wasn't opened\n"); \
                                    return FILE_ERROR;              \
                                }                                   \
                            }while(0);


void print (const Node* const node);
Errors graph_dump (const Node *const node, const Node *const definite_node);



#endif //_CHECK_H_