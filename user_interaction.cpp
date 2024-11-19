#include <stdio.h>

#include "user_interaction.h"

static Node* question (Node* node);

void guessing (Tree *const the_tree)
{
    assert(the_tree);
    Node* node = the_tree->start_node;

    while (node->Left && node->Right)
        node = question(node);

    char ans_str[MAX_STR_LEN] = {};
    
    printf("did you mean \"%s\"?\n", node->str);   //ошибки
    fgets(ans_str, MAX_STR_LEN, stdin);
    
    if (strncmp(ans_str, YES, MAX_STR_LEN) == 0)
    {
        printf("Yep! I knew it hehe\n");
        return;
    }
    
    printf("I despair of you, son\n");

    char* new_str = (char*)calloc(MAX_STR_LEN, sizeof(char));  //надо проверки сделать
    char* diff = (char*)calloc(MAX_STR_LEN, sizeof(char));

    node->Left = make_node(node->str);

    printf("what did you mean then?? I ll memorize it\n");
    fgets(new_str, MAX_STR_LEN, stdin);
    node->Right = make_node(new_str); 

    printf("what is the difference?\n");
    fgets(diff, MAX_STR_LEN, stdin);
    
    sprintf(diff, "%s%c", diff, QUESTION_MARK);
    node->str = diff;

    free(new_str);
    free(diff);
}

Node* question (Node* node)
{
    printf("%s\n", node->str);
    char ans_str[MAX_STR_LEN] = {};

    scanf("%s", ans_str);
    if (strncmp(ans_str, YES, MAX_STR_LEN) == 0)
        return node->Right;
    else
        return node->Left;
}


/*Node* find_node (const char *const str, Tree* the_tree)
{
    assert(str);
    assert(the_tree);

    size_t node_amt = the_tree->node_amt;

    for (size_t node_cnt = 0; node_cnt < node_amt; node_cnt++)
    {
        if (strncmp(str, the_tree->database_strs[node_cnt].str, MAX_STR_LEN)== 0)
            return the_tree->database_strs[node_cnt].node_address;
    }

    

    return nullptr;
}*/