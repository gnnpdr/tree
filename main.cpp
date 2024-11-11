#include <stdio.h>

#include "base_handle.h"

int main (int argc, char** argv)
{
    Node first_node = {};
    
    Input base_text = {};

    get_name(&base_text, argv);
    get_file_text(&base_text);
    handle_text (&base_text);
}

/*printf("question\n");
    char str[MAX_STR_LEN] = "";
    scanf("%s", str);

    make_base_tree();

    Node* n1 = create_node(str); //вопрос с названиями переменных. хочется, чтобы можно было окрасить определенный узел в цвет, а как к нему обратиться, если нет переменной..

    printf("Right\n");
    //n1.Right = 
    insert_node (n1);

    graph_dump (n1, n1);

    free (n1);*/