#include <stdio.h>

#include "tree.h"
#include "check_tree.h"

int main ()
{
    Node n1 = {};
    n1.data = 50;
    //printf("parent %p\n", n1);

    Node n2 = {};
    n2.data = 75;
    n1.Right = &n2;
    //printf("right %p and %p\n", &n2, n1.Right);

    Node n3 = {};
    n3.data = 25;
    n1.Left = &n3;
    //printf("left %p and %p\n", &n3, n1.Left);

    graph_dump (&n1, &n1);

    Node n4 = {};
    n4.data = 7;
    n3.Left = &n4;

    graph_dump (&n1, &n4);
    //printf("left %p and %p\n", &n4, n2.Left);
}