#include <stdio.h>

#include "user_interaction.h"

static Node* question (Node* node, char* str);
//static size_t find_free_place (Tree* the_tree);

void guessing (Tree *const the_tree)
{
    assert(the_tree);

    char** strs = (char**)calloc(the_tree->node_amt, sizeof(char*));
    for (size_t i = 0; i < the_tree->node_amt; i++)
        strs[i] = the_tree->database_strs[i].str;

    char ans_str[MAX_STR_LEN] = {};
    char new_str[MAX_STR_LEN] = {};

    char diff[MAX_STR_LEN] = {};

    bool is_question = true;
    Node* guess_node = the_tree->start_node;
    size_t node_cnt = 0;

    while (is_question)
    {
        guess_node = question(guess_node, strs[node_cnt]);
        node_cnt++;
        is_question = find_question_mark(guess_node->str);
    }

    printf("did you mean \"%s\"?\n", guess_node->str);
    scanf ("%s", ans_str);
    
    if (strncmp(ans_str, YES, MAX_STR_LEN) == 0)
        printf("Yep! I knew it hehe\n");
    else
    {
        printf("I despair of you, son\n");
        
        size_t free_place = the_tree->node_amt;

        guess_node->Left = create_node(guess_node->str);
        the_tree->database_strs[free_place].str = guess_node->str;
        the_tree->database_strs[free_place].node_address = guess_node->Left;

        printf("what did you mean then?? I ll memorize it\n");
        scanf("%s", ans_str);
        strncpy(new_str, ans_str, MAX_STR_LEN);

        guess_node->Right = create_node(new_str);  //надо было заполнить базу данных, а не создавать новые узлы?
        the_tree->database_strs[free_place + 1].str = new_str;
        the_tree->database_strs[free_place + 1].node_address = guess_node->Right;

        printf("what is the difference?\n");
        scanf("%s", ans_str);

        strncpy(diff, ans_str, MAX_STR_LEN);
        printf("%s\n", diff);
        
        sprintf(diff, "%s%c", diff, QUESTION_MARK);
        guess_node->str = diff;

        the_tree->database_strs[free_place - 1].str = diff;

        the_tree->node_amt += 2;
    }

    free(strs);
}

Node* question (Node* node, char* str)
{
    char ans_str[MAX_STR_LEN] = {};
    printf("is that %s\n", str);

    scanf("%s", ans_str);
    if (strncmp(ans_str, YES, MAX_STR_LEN) == 0)
        return node->Right;
    else
        return node->Left;
}


Node* find_node (const char *const str, Tree* the_tree)
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
}