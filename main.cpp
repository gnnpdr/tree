#include <stdio.h>

#include "tree_structure.h"
#include "draw_tree.h"
#include "get_database.h"
#include "user_interaction.h"
#include "tree_functions.h"

int main (int argc, char** argv)
{
    Node start_node = {};
    node_ctor (&start_node);

    Input base_text = {};

    input_ctor(&base_text);

    get_database_name(&base_text, argv);
    get_database_text(&base_text);

    Tree the_tree = {};
    tree_ctor (&the_tree, &start_node);
    handle_text (&base_text, &the_tree);

    printf("ALL_RIGHT\n");
    graph_dump (the_tree.start_node, the_tree.start_node);

    //make_definition (&the_tree);
    find_difference(&the_tree);
    //guessing (&the_tree);

    

    input_dtor(&base_text);
    tree_dtor(&the_tree);
}