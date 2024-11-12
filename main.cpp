#include <stdio.h>

#include "base_handle.h"
#include "tree_structure.h"
#include "draw_tree.h"
#include "tree_functions.h"
#include "user_interaction.h"

int main (int argc, char** argv)
{
    Node start_node = {};
    node_ctor (&start_node);

    Input base_text = {};

    get_name(&base_text, argv);
    get_file_text(&base_text);
    handle_text (&base_text);


    Tree the_tree = {};
    tree_ctor (&the_tree, &start_node);

    database_tree_fill(&the_tree, &base_text);


    make_definition (&the_tree);
    //guessing (&the_tree);

    graph_dump (the_tree.start_node, the_tree.start_node);

    input_dtor(&base_text);
    tree_dtor(&the_tree);

}