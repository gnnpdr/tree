/*#include <stdio.h>

#include "tree_functions.h"

static size_t* find_way (char** strs, char* str, size_t* node_amt);

Node* insert_node (Node *const node, char* str)
{
    assert (node);

    Node* temp_node = {};

    bool is_str_question = find_question_mark(str);
    bool is_left_node_question = false;
    if (node->Left)
        is_left_node_question = find_question_mark(node->Left->str);
    
        
    if (node->Left)
    {
        if(!is_left_node_question)
        {
            node->is_filled = true;
            temp_node = create_node(str);
            node->Right = temp_node;
            return temp_node;
        }

        if(!node->Left->is_filled)
            temp_node = insert_node(node->Left, str);
        
        else
        {
            if (!is_str_question)
                node->is_filled = true;

            if (!node->Right)
            {   
                temp_node = create_node(str);
                node->Right = temp_node;
            }
            else
                temp_node = insert_node(node->Right, str);
        }
    }
    else
    {
        temp_node = create_node(str);
        node->Left = temp_node;   
    }
    return temp_node;
}


void make_base_tree (Tree* the_tree)
{
    assert(the_tree);

    size_t node_amt = the_tree->node_amt;

    char** strs = (char**)calloc(node_amt, sizeof(char*));
    for (size_t i = 0; i < the_tree->node_amt; i++)
        strs[i] = the_tree->database_strs[i].str;

    the_tree->start_node->str = strs[0];
    the_tree->database_strs[0].node_address = the_tree->start_node;

    for(size_t str_ind = 1; str_ind < node_amt; str_ind++)
    {
        Node* definite_node = insert_node(the_tree->start_node, strs[str_ind]);
        the_tree->database_strs[str_ind].node_address = definite_node;

        graph_dump (the_tree->start_node, definite_node);
    }

    free(strs);
}

bool find_question_mark(char* str)
{
    assert(str);

    if (str[strlen(str) - 1] == QUESTION_MARK)
        return true;
    else
        return false;
}


void database_tree_fill(Tree *const the_tree, const Input *const base_text)
{
    assert(the_tree );
    assert(base_text);

    size_t node_amt = base_text->node_amt;
    char** strs = (char**)calloc(node_amt, sizeof(char*));
    
    for (size_t i = 0; i < node_amt; i++)
        strs[i] = base_text->strs[i];

    for (size_t str_ind = 0; str_ind < node_amt; str_ind++)
        the_tree->database_strs[str_ind].str = strs[str_ind];

    the_tree->node_amt = base_text->node_amt;

    make_base_tree(the_tree);
}


char* make_definition (Tree* the_tree)
{
    assert(the_tree);
    
    printf("what word?\n");

    char* str = (char*)calloc(MAX_STR_LEN, sizeof(char));  //не динамическая память
    scanf("%s", str);  //отдельно в user 

    size_t steps_amt = the_tree->node_amt;

    char** strs = (char**)calloc(steps_amt, sizeof(char*));
    for (size_t i = 0; i < the_tree->node_amt; i++)
        strs[i] = the_tree->database_strs[i].str;

    size_t* path = find_way(strs, str, &steps_amt);

    char* definition = (char*)calloc(MAX_STR_LEN, sizeof(char));
    sprintf(definition, "%s it is ", str);
    
    for (size_t str_num = 0; str_num < steps_amt - 1; str_num++)  //-1 так как путь включает в себя сасо слово, нам это не нужно
    {
        if (path[str_num + 1] % 2 == 1)
            sprintf(definition, "%snot", definition);

        str = strs[path[str_num]];
        str[strlen(str) - 1] = ' ';
        
        sprintf(definition, "%s%s", definition, str);
    }

    printf("here it is\n");
    printf("%s\n", definition);

    free(path);
    free(definition);
    free(strs);
}

size_t* find_way (char** strs, char* str, size_t* node_amt)
{
    Ways way_type = FREE;
    size_t* path = (size_t*)calloc(*node_amt, sizeof(size_t));
    size_t step = 0;


    for (size_t str_num = 0; str_num < *node_amt; str_num++)
    {
        bool is_question = find_question_mark(strs[str_num]);
        if (is_question)
        {
            path[step] = str_num;
            step++;
        }
        else
        {
            if (strncmp(strs[str_num], str, MAX_STR_LEN) == 0)
            {
                path[step] = str_num;
                step++;
            }
            else
            {
                if(way_type == FREE)
                    way_type = NOT_LEFT;
                else if(way_type == NOT_LEFT)
                {
                    way_type = FREE;
                    step--;
                }
            }
        }
    }

    *node_amt = step;

    return path;
}


/*void find_diff(const char *const str1, const char *const str2)
{
    assert(str1);
    assert(str2);

    size_t* path_str1 = find_way(strs, str1);
}*/