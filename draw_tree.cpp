#include <stdio.h>

#include "draw_tree.h"

static void make_file_names (char *const input_file_name, char *const output_file_name, size_t enter_cnt);

static void make_nodes (const Node *const node, const Node *const definite_node, char *const input_file_data); 
static void make_connections (const Node *const node, char *const input_file_data);

static Errors fill_input_file (const char *const  input_file_name, const char *const input_file_data);

static Errors do_graph_cmd (const char *const input_file_name, const char *const output_file_name);


void print (const Node* const node)
{
    if (!node)
        return;

    printf("(");
    printf("%s", node->str);
    if (node->Left)
        print(node->Left);

    if (node->Right)
        print(node->Right);

    printf(")");
}


Errors graph_dump (const Node *const node, const Node *const definite_node)  //можно сделать так, чтобы возвращало в мэйн определенное значение и печаталась ошибка. Или так, что ошибка печатается при неверном возврате
{  
    assert (node);

    static size_t enter_cnt = 0;

    char  input_file_name[MAX_STR_LEN] = "";
    char output_file_name[MAX_STR_LEN] = "";

    make_file_names (input_file_name, output_file_name, enter_cnt);
    
    char input_file_data[INPUT_FILE_SIZE] = {};

    sprintf(input_file_data, "%sdigraph G\n{\n\tnode [shape = Mrecord; fillcolor = \"#9FDFDA\";];\n",\
    input_file_data);

    make_nodes (node, definite_node, input_file_data);

    sprintf (input_file_data, "%s\n", input_file_data);  //их только здесь, так как функции печати входят в рекурсию

    make_connections (node, input_file_data);

    sprintf (input_file_data, "%s\n}\n", input_file_data);

    fill_input_file (input_file_name, input_file_data);
    
    do_graph_cmd (input_file_name, output_file_name);

    enter_cnt++;

    return ALL_RIGHT;
}


void make_file_names (char *const input_file_name, char *const output_file_name, size_t enter_cnt)
{
    assert (input_file_name );
    assert (output_file_name);

    static char name_base[MAX_STR_LEN] = "";

    /*if (enter_cnt == 0)
    {
        printf("enter name of input dot file (please)\n");
        scanf("%s", name_base);
    }*/
        
    strncpy(output_file_name, input_file_name, MAX_STR_LEN);

    sprintf(input_file_name, "%s%lld.dot", name_base, enter_cnt);
    sprintf(output_file_name, "%s%lld.png", name_base, enter_cnt);
}


//make_nudes
void make_nodes (const Node *const node, const Node *const definite_node, char *const input_file_data)  //заполнение узлов
{
    assert (node);
    assert (input_file_data);

    if (!node)
        return;

    const char*  left = NO;
    const char* right = YES;

    /*if (!node->Left)
        strncpy(left, "0", MAX_STR_LEN);

    if (!node->Right)
        strncpy(right, "0", MAX_STR_LEN);*/

    if(node == definite_node)  //сделать функцию поиска по адресу
        sprintf(input_file_data, "%s\tnode%p [style = filled; fillcolor = \"#E64F72\"; label = \"{<f0> %s  |{<f1> %s | <f2> %s}} \"];\n",\
        input_file_data, node, node->str, left, right);
    else
        sprintf(input_file_data, "%s\tnode%p [style = filled; fillcolor = \"#9FDFDA\"; label = \"{<f0> %s  |{<f1> %s | <f2> %s}} \"];\n",\
        input_file_data, node, node->str, left, right);

    if (node->Left)
        make_nodes (node->Left, definite_node, input_file_data);
        
    if (node->Right)
        make_nodes (node->Right, definite_node, input_file_data);
}


void make_connections (const Node *const node, char *const input_file_data)  //связи и ранк
{
    assert (node);
    assert (input_file_data);

    if (!node)
        return;

    if (node->Left && node->Right)
        sprintf(input_file_data, "%s\t{rank = same; node%p; node%p}\n",\
        input_file_data, node->Left, node->Right);

    if (node->Left)
    {
        sprintf(input_file_data, "%s\tnode%p:<f1> -> node%p:<f0> [weight = 0.15; color = \"#1D638B\";];\n",\
        input_file_data, node, node->Left);
        make_connections (node->Left, input_file_data);
    }
        
    if (node->Right)
    {
        sprintf(input_file_data, "%s\tnode%p:<f2> -> node%p:<f0> [weight = 0.15; color = \"#1D638B\";];\n",\
        input_file_data, node, node->Right);
        make_connections (node->Right, input_file_data);
    }
}


Errors fill_input_file (const char *const  input_file_name, const char *const input_file_data)
{
    assert (input_file_name);
    assert (input_file_data);

    FILE* input_file;
    input_file = fopen(input_file_name, "w");
    FILE_CHECK(input_file)

    if (!fwrite(input_file_data, sizeof(char), INPUT_FILE_SIZE, input_file))
        return WRITE_ERROR;

    if (fclose(input_file) != 0)
        return  CLOSE_ERROR;

    return ALL_RIGHT;
}

Errors do_graph_cmd (const char *const input_file_name, const char *const output_file_name)
{
    assert (input_file_name );
    assert (output_file_name);

    char cmd[80] = {};
    sprintf(cmd, "dot %s -Tpng -o %s", input_file_name, output_file_name);

    if(system(cmd) != 0)
        return CMD_ERROR;

    return ALL_RIGHT;
}
