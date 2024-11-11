#include <stdio.h>

#include "tree_structure.h"

Errors create_node (Node *const node) //так как это служебная функция, надо, чтобы она возвращалв эррорс
{
    assert(node);
    Errors error = ALL_RIGHT;

    Node* new_node = (Node*)calloc(ONE_NODE, sizeof(Node));
    ALLOCATION_CHECK (new_node)

    new_node->data = value;

    return new_node;
}


Errors tree_ctor (Tree *const the_tree)  //не очень хорошо, что будет типа обязательный параметр с структурой базы дерева. Можно сделать отдельно ситор с выделением "многа" памяти и отдельную функцию на заполнение определенной информацией
{
    assert(the_tree);

    char** strs = (char**)calloc(START_STRS_AMT, sizeof(char*));
    ALLOCATION_CHECK(strs)

    int* inds = (int*)calloc(START_STRS_AMT, sizeof(int));
    ALLOCATION_CHECK(inds)


}

Errors database_tree_fill(Tree *const the_tree, const Input *const base_text)
{
    assert(the_tree );
    assert(base_text);
}



/*Node* make_base_tree(Input* base_text, Tree* the_tree)  //функцию получения имени как аргумента ком строки можно взять из проуессора
{
    assert(base_text);
    assert(the_tree);
    //сначала сделать массив строк из ткх, что заключены в "", так как там есть четкая последовательность заполнения базы, можно брать строки и все.
    //можно сделать ошибку - проверку глубины дерева. Если она не будет совпадать с максимальным колвом табов, что выдать трабл.
    //проблема в том, что сканф прокускает табы и тд

    Node start_node = //теперь будет разделение на основе вопросительных знаков. Право лево определается последовательностью, а конец ветки - отсутствием вопр знака

}



void insert_node (Node *const node)  //формирует дерево по базе
{
    assert (node);

    if (value < node->data)
    {
        if(node->Left)
            insert_node (node->Left, value);
        else
            node->Left = create_node (value);
    } 
    else
    {
        if(node->Right)
            insert_node (node->Right, value);
        else
            node->Right = create_node (value);
    }
}

void free (Node* node)  //переименовать
{
    free(node);
}

/*Node* create_node (char *const str)
{
    assert(str);

    //Errors error = ALL_RIGHT;

    //Node* new_node = (Node*)calloc(ONE_NODE, sizeof(Node));
    //ALLOCATION_CHECK (new_node)

    //strncpy(new_node->str, str, MAX_STR_LEN);  //проверка

    //return new_node;
}*/