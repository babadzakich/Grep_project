#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ahocorassic.h"

typedef struct string_str
{
    char* array;
    size_t cap, size;
}String;

String data;
int len = 0;
void mystrncat(char* dest, char* src, int n)
{   
    // int len = strlen(dest);
    for (int step = 0; step < n; step++)
    {
        dest[len + step] = src[step];
    }
    len += n;
}

void add_data(char* buff)
{
    if(data.cap == 0)
    {
        data.cap = 1000;
        data.array = (char*)malloc(sizeof(char) * data.cap);
    }
    if (data.cap == data.size)
    {
        data.cap *= 2;
        data.array = (char*)realloc(data.array, sizeof(char) * data.cap);
        printf("%zu\n", data.cap);
    }
    mystrncat(data.array, buff, 1000);
    data.size += strlen(buff);
}

char buffer[1001];
int main(int argc, char** argv)
{
    initTrie();
    char * inputFile = argv[1];
    for(int step = 2; step < argc; step++)
    {
        add_string_to_trie(argv[step], strlen(argv[step]));
    }    
    freopen("output.txt", "w", stdout);
    FILE* fin = fopen(inputFile, "r");
    // add_string_to_trie("i[a-b,e-z]", 10);
    // add_string_to_trie("[a-z]o|u", 8);
    // FILE* fin = fopen("input.txt", "r");
    
    int line = 1;
    while(fgets(buffer, 1001, fin) != NULL)
    {
        add_data(buffer);
        if (buffer[strlen(buffer) - 1] == '\n' || strlen(buffer) < 1000)
        {  
            find_all_pos(data.array, line++);
            memset(buffer, '\0', 1001);
            memset(data.array, '\0', data.cap); 
            data.size = 0;
            len = 0;
            continue;
        }
        memset(buffer, '\0', 1001);
        
    }
    // freopen(inputFile, "r", stdin);
    // int line = 1;
    // while(scanf("%s", buffer) != EOF)
    // {
    //     find_all_pos(buffer, line++);
    //     memset(buffer, '\0', sizeof(buffer));
    // }
    free(data.array);
    fclose(fin);
    freeTrie();
    return 0;
}