#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ahocorassic.h"
#include "stringArray.h"

char buffer[1001];
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <string1> <string2> ... <stringN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    initTrie();
    
    for(int step = 1; step < argc; step++)
    {
        add_string_to_trie(argv[step], strlen(argv[step]));
    }

    int line = 1;
    while(fgets(buffer, 1001, stdin) != NULL)
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
    free(data.array);
    return 0;
}