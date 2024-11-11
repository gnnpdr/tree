/*void insert_node (Node *const node)
{
    assert (node);

    char object[MAX_STR_LEN]      = "";
    char differ_sign[MAX_STR_LEN] = "";
    char question[MAX_STR_LEN]    = "";

    if (!node->Left)
        insert_node (node->Left);

    printf("what did you mean?\n");
    scanf("%s", object);

    printf("what is sign by witch they differ?\n");
    scanf("%s", differ_sign);

    sprintf(question, "is that %s?", differ_sign);

    node->Right = create_node (node->str);

    strncpy(node->str, question, MAX_STR_LEN);

    node->Left = create_node (object);
}*/