#include <stdio.h>

#include "tree.h"
#include "check_tree.h"

int main ()
{
    Node* n1 = create_node(50);

    insert_node (n1, 30);

    insert_node (n1, 70);

    insert_node (n1, 10);

    insert_node (n1, 65);

    insert_node (n1, 80);
    graph_dump (n1, n1);

    free (n1);
}