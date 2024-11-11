#include <stdio.h>
#include "base_handle.h"

static size_t find_file_size (const char *const name);
static size_t find_quot_mark_amt(Input* base_text);

Errors get_name(Input *const base_text, char **const argv)
{
    assert(base_text);
    assert(argv);

    //printf("%s\n", argv[1]);
    //printf("%d\n", strlen(argv[1]));

    char* name = (char*)calloc(strlen(argv[1]), sizeof(char));
    //printf("%s\n", name);
    //printf("%p\n", name);
    ALLOCATION_CHECK(name)

    
    
    strncpy(name, argv[1], strlen(argv[1]) + 1);
    //printf("%s\n", name);
    base_text->name = name;

    return ALL_RIGHT;
}

Errors get_file_text (Input *const base_text)
{
    //это фигня какая-то, повтор того, что было в процессоре (и онегине), только текст будет обрабатываться немного по-другому
    
    assert(base_text);

    char* base_file_name = base_text->name;
    FILE* input_file;
    input_file = fopen(base_file_name, "rb");
    //printf("pointer %p\n", input_file);
    FILE_CHECK(input_file)

    size_t size = find_file_size(base_text->name);
    //printf("size %d\n", size);

    char* text = (char*)calloc(size, sizeof(char));
    ALLOCATION_CHECK(text)

    size_t read_result = fread(text, sizeof(char), size, input_file);
    if (read_result != size)
        return READ_ERROR;

    //printf("text %s\n", text);

    int close_res = fclose(input_file);
    
    if(close_res != 0)
        return CLOSE_ERROR;

    base_text->text = text;
    base_text->size = size;

    return ALL_RIGHT;
}

size_t find_file_size (const char *const name)
{
    assert(name);

    struct stat file_info;

    if (stat(name, &file_info) == -1)
    {
        printf("stat problem\n");
        return 1;
    }

    return file_info.st_size;
}

Errors handle_text (Input* base_text)
{
    assert(base_text);

    size_t word_amt = find_quot_mark_amt(base_text);
    //printf("word amt %d\n", word_amt);
    
    char** strs = (char**)calloc(word_amt, sizeof(char**));
    ALLOCATION_CHECK(strs)

    size_t word_num = 0;
    char* text = base_text->text;
    //printf("text %s\n", text);
    char* address = text;

    while(word_num < word_amt)
    {
        sscanf(text, "%[^\"]", address);  //считывает до кавычки
        text += strlen(address) + 1;  //перейдет до конца входной строки и перешагнет кавычки
        //printf("start str %s\n", address);
        sscanf(text, "%[^\"]", address);  //перезаписывает в новый адрес, не старый, теперь это новая !строка! поэтомы не надо ставить \0
        
        strs[word_num] = address;  //может возникнуть проблема с тем, что сотрутся адреса, ведь все в цикле
        //printf("str %d %s\n", word_num, strs[word_num]);  //проблема в том, что после этого снова читает нужное слово, это нехорошо
        text += strlen(address) + 1;  //пройдет еще одну кавычку
        word_num++;
    }

    printf("HERE\n");
    printf("%s\n", strs[1]);
    for (size_t i = 0; i < word_amt; i++)  //возможно, метста просто нет для этого. Потому что нет ситора
        base_text->strs[i] = strs[i];

    printf("%s\n", base_text->strs[1]);

    for (int i = 0; i < word_amt; i++)
        printf("%s\n", strs[i]);

    return ALL_RIGHT;
}

size_t find_quot_mark_amt(Input* base_text)
{
    size_t quot_mark_cnt = 0;
    char* text = base_text->text;

    char* ch_pointer = strchr(text, QUOT_MARK);

    while (ch_pointer != nullptr)
    {
        quot_mark_cnt++;

        ch_pointer++;  //переход к строке без "
        ch_pointer = strchr(ch_pointer, QUOT_MARK);
    }

    return quot_mark_cnt / 2;
}
