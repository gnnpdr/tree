#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


static const char QUOT_MARK = '"';


struct Input 
{
    char* name;
    char* text;
    size_t size;

    char** strs;
};

enum Errors
{
    ALL_RIGHT,
    FILE_ERROR,
    READ_ERROR,
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

#define ALLOCATION_CHECK(buf) do                                    \
                            {                                       \
                                if (buf == 0)                       \
                                {                                   \
                                    printf("no place\n");           \
                                    return ALLOCATION_ERROR;        \
                                }                                   \
                            }while(0);

Errors get_name(Input *const base_text, char **const argv);
Errors get_file_text (Input *const base_text);
Errors handle_text (Input* base_text);
