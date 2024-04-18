#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ahocorassic.h"

char buffer[1024];
int main(int argc, char** argv)
{
    initTrie();
    char * inputFile = argv[1];
    for(int step = 2; step < argc; step++)
    {
        add_string_to_trie(argv[step], strlen(argv[step]));
    }    
    freopen(inputFile, "r", stdin);
    while(scanf("%s", buffer) != EOF)
    {
        find_all_pos(buffer);
        memset(buffer, '\0', sizeof(buffer));
    }
    return 0;
}