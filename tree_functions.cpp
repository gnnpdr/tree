#include <stdio.h>

#include "tree_functions.h"

static bool find_path(Node *const node, bool* path, char* str, int* path_cnt);
static char* make_def_str(char* definition, bool* path, int path_cnt, Node* node, size_t num);
static char* make_dif_str(char* difference, bool* first_path, bool* sec_path, Node* node, int num, int path_cnt, int start_dif);
static size_t find_dif_num(bool* first_path, bool* sec_path, int min_path_cnt);


void make_definition (Tree* the_tree)
{
    assert(the_tree);

    printf("what word do you want to define?\n");
    
    char ans_str[MAX_STR_LEN] = {};
    fgets(ans_str, MAX_STR_LEN, stdin);

    bool path[MAX_STRS_AMT] = {};
    int path_cnt = 0;  //инт, а не сайз т, чтобы была проверка на отсутствие слова в дереве.
    find_path(the_tree->start_node, path, ans_str, &path_cnt);

    if (path_cnt < 0)
    {
        printf("there is no such word\n");
        return;
    }
        
    char definition[MAX_STR_LEN] = {};
    size_t num = 0;
    make_def_str(definition, path, path_cnt, the_tree->start_node, num);
    printf("definition %s\n", definition);
}

bool find_path(Node *const node, bool* path, char* str, int* path_cnt)
{
    assert(node);
    assert(path);

    /*printf("-----------------------------------\n");
    for (int i = 0; i < *path_cnt; i++)
        printf("%d ", path[i]);

    printf("\n");*/

    bool this_way = true;

    if(node->Left == nullptr && node->Right == nullptr)
    {
        size_t cmp_res = strncmp(str, node->str, strlen(node->str));
        if (cmp_res != 0)
        {
            (*path_cnt)--;
            return false;
        }
        else
            return true;
    }
    
    if (node->Left)
    {
        path[*path_cnt] = false;
        
        (*path_cnt)++;
        
        this_way = find_path(node->Left, path, str, path_cnt);
    }
    if (this_way)
        return true;

    if (node->Right)
    {
        path[*path_cnt] = true;
        (*path_cnt)++;
        this_way = find_path(node->Right, path, str, path_cnt);
        if (!this_way)
        {
            path[*path_cnt] = false;
            (*path_cnt)--;
        }
        else
            return true;
    }

    return false;
}

char* make_def_str(char* definition, bool* path, int path_cnt, Node* node, size_t num)
{
    if ((int)num == path_cnt)
        return definition;

    char str[MAX_STR_LEN] = {};
    strncpy(str, node->str, strlen(node->str) - 1);

    if(path[num])
    {
        sprintf(definition, "%s %s", definition, str);
        num++;
        make_def_str(definition, path, path_cnt, node->Right, num);
    }
    else
    {
        sprintf(definition, "%s not %s", definition, str);
        num++;
        make_def_str(definition, path, path_cnt, node->Left, num);
    }

    return definition;
}

void find_difference(Tree* the_tree)
{
    assert(the_tree);

    printf("which words do you want to compare?\n");
    printf("Enter first\n");
    char first_word[MAX_STR_LEN] = {};
    fgets(first_word, MAX_STR_LEN, stdin);

    printf("Yep. Enter second\n");
    char sec_word[MAX_STR_LEN] = {};
    fgets(sec_word, MAX_STR_LEN, stdin);

    int cmp_res = strncmp(first_word, sec_word, MAX_STR_LEN);
    if (cmp_res == 0)
    {
        printf("this is one word!\n");
        return;
    }
        
    bool first_path[MAX_STR_LEN] = {};
    int first_path_cnt = 0;  //инт, а не сайз т, чтобы была проверка на отсутствие слова в дереве.
    find_path(the_tree->start_node, first_path, first_word, &first_path_cnt);

    if (first_path_cnt < 0)
    {
        printf("there is no such word\n");
        return;
    }

    printf("first word\n");
    for (int i = 0; i < first_path_cnt; i++)
        printf("%d ", first_path[i]);

    printf("\n");

    bool sec_path[MAX_STR_LEN] = {};
    int sec_path_cnt = 0;  //инт, а не сайз т, чтобы была проверка на отсутствие слова в дереве.
    find_path(the_tree->start_node, sec_path, sec_word, &sec_path_cnt);

    if (sec_path_cnt < 0)
    {
        printf("there is no such word\n");
        return;
    }

    int num = 0;

    int max_path_cnt = 0;
    if (first_path_cnt >= sec_path_cnt)
        max_path_cnt = first_path_cnt;
    else
        max_path_cnt = sec_path_cnt;

    int min_path_cnt = first_path_cnt + sec_path_cnt - max_path_cnt;

    int start_dif = find_dif_num(first_path, sec_path, min_path_cnt);

    if (start_dif == 0)
    {
        printf("this things have nothing in common!\n");
        return;
    }

    

    printf("sec word\n");
    for (int i = 0; i < first_path_cnt; i++)
        printf("%d ", sec_path[i]);

    printf("\n");
        
    char difference[MAX_STR_LEN] = {};
    //printf("IT SHOULD WORK\n");
    //printf("start dif %d\n", start_dif);
    //printf("max cnt %d\n", max_path_cnt);

    sprintf(difference, "%s and %s have some similarities. Here they are:", first_word, sec_word);
    //printf("%s\n", difference);
    //printf("dif %p, first path %p, sec_path %p, node %p, num %d\n", difference, first_path, sec_path, the_tree->start_node, num);
    make_dif_str(difference, first_path, sec_path, the_tree->start_node, num, max_path_cnt, start_dif);
    printf("%s\n", difference);
}

size_t find_dif_num(bool* first_path, bool* sec_path, int min_path_cnt)
{
    for (int i = 0; i < min_path_cnt; i++)
    {
        if (first_path[i] != sec_path[i])
            return i;
    }

    return min_path_cnt;
}


char* make_dif_str(char* difference, bool* first_path, bool* sec_path, Node* node, int num, int path_cnt, int start_dif)
{
    printf("HERE\n");
    if (num == path_cnt)
    {
        printf("RETURN AT START\n");
        return difference;
    }
        

    char str[MAX_STR_LEN] = {};
    strncpy(str, node->str, strlen(node->str) - 1);
    printf("STR %s\n", str);
    printf("diff %s\n", difference);

    /*printf("ABOUT DIF\n");
    for (int i = 0; i < start_dif; i++)
        printf("%d ", first_path[i]);

    printf("\n");

    for (int i = 0; i < start_dif; i++)
        printf("%d ", sec_path[i]);

    printf("\n");*/

    if(num < start_dif)
    {
        if (first_path[num] == sec_path[num])
        {
            if (first_path[num])
            {
                printf("ADD\n");
                sprintf(difference, "%s %s", difference, str);
                num++;
                make_dif_str(difference, first_path, sec_path, node->Right, num, path_cnt, start_dif);
                return difference;
            }
            else
            {
                printf("ADD\n");
                sprintf(difference, "%s not %s", difference, str);
                num++;
                make_dif_str(difference, first_path, sec_path, node->Left, num, path_cnt, start_dif);
                return difference;
            }
        }
    }

    /*if (num >= path_cnt)
    {
        printf("RETURN\n");
        return difference;
    }*/
        

    if (num == start_dif)
    {
        printf("ADD DIFF\n");
        sprintf(difference, "%s. And some differences:", difference, str);
    }

    if(first_path[num])
    {
        printf("ADD\n");
        sprintf(difference, "%s %s", difference, str);
        num++;
        make_dif_str(difference, first_path, sec_path, node->Right, num, path_cnt, start_dif);
    }
    else
    {
        printf("ADD\n");
        sprintf(difference, "%s not %s", difference, str);
        num++;
        make_dif_str(difference, first_path, sec_path, node->Left, num, path_cnt, start_dif);
    }

    printf("RETURN IN END\n");
    return difference;
}
/*void find_diff(const char *const str1, const char *const str2)
{
    assert(str1);
    assert(str2);

    size_t* path_str1 = find_way(strs, str1);
}*/