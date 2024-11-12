#include <stdio.h>
#include "base_handle.h"

static size_t find_file_size (const char *const name);
static size_t find_quot_mark_amt(Input* base_text);


Errors get_name(Input *const base_text, char **const argv)
{
    assert(base_text);
    assert(argv);

    char* name = (char*)calloc(strlen(argv[1]), sizeof(char));
    ALLOCATION_CHECK(name)

    strncpy(name, argv[1], strlen(argv[1]) + 1);
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
    FILE_CHECK(input_file)

    size_t size = find_file_size(base_text->name);

    char* text = (char*)calloc(size, sizeof(char));
    ALLOCATION_CHECK(text)

    size_t read_result = fread(text, sizeof(char), size, input_file);
    if (read_result != size)
        return READ_ERROR;

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
    
    char** strs = base_text->strs;

    size_t word_num = 0;
    char* text = base_text->text;

    size_t symb_amt = 0;
    char address[MAX_STR_LEN] = {};  //временная строка для получения длины 

    printf("text address %p, %p\n", text, base_text->text);

    while(word_num < word_amt)
    {
        sscanf(text + symb_amt, "%[^\"]", address);  //считывает до кавычки
        
        symb_amt += strlen(address) + 1;  //перейдет до конца входной строки и перешагнет кавычки

        sscanf(text + symb_amt, "%[^\"]", address);
        text[symb_amt + strlen(address)] = '\0';

        strs[word_num] = text + symb_amt;
        symb_amt += strlen(address) + 1;  //пройдет еще одну кавычку
        
        word_num++;
    }
        

    for (size_t i = 0; i < word_amt; i++)
        base_text->strs[i] = strs[i];

    base_text->node_amt = word_amt;

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


void input_dtor(Input* base_text)
{
    free(base_text->name);
    free(base_text->text);
}