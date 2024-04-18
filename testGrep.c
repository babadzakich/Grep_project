#include <stdio.h>
#include<stdlib.h>
#include<string.h>
// #include"ahocorassic.h"

typedef struct Node
{
    int nextLetter[96];
    int parent;
    int isWord;
    int suff_link;
    int auto_move[96]; //auto_move - запоминание перехода автомата
    int par; //par - вершина-отец в дереве
    char symb;
    int suff_flink;
}Node;
typedef struct Vector
{
    Node* array;
    int cap;
    int top;
}vector;
typedef struct VectorS
{
    char** array;
    int cap;
    int top;
}vectorS;
vectorS Pattern;
vector Trie;

void vector_add(vector* array, Node vertex)
{
    if(array->cap == 0)
    {
        array->cap = 1;
        array->array = (Node*)malloc(sizeof(Node));
    }
    if (array->cap == array->top)
    {
        array->cap *= 2;
        array->array = (Node*)realloc(array->array, sizeof(Node) * array->cap);
    }
    array->array[array->top++] = vertex;
}

void vectorS_add(vectorS* array, char* string)
{
    if(array->cap == 0)
    {
        array->cap = 1;
        array->array = (char**)malloc(sizeof(char*));
    }
    if (array->cap == array->top)
    {
        array->cap *= 2;
        array->array = (char**)realloc(array->array, sizeof(char*) * array->cap);
    }
    array->array[array->top++] = string;
}

Node makeTrieVertex(int p, char c)
{
    Node vertex;
    memset(vertex.nextLetter, 255, sizeof(vertex.nextLetter));
    vertex.isWord = 0;
    vertex.suff_link = -1;
    memset(vertex.auto_move, 255, sizeof(vertex.auto_move));
    vertex.par = p;
    vertex.symb = c;
    vertex.suff_flink = -1;
    return vertex;
}

void initTrie()
{
    Trie.cap = 0;
    Trie.top = 0;
    if(Trie.array) free(Trie.array);
    vector_add(&Trie, makeTrieVertex(0, '$'));
}

void add_string_to_trie(char* string, int length)
{
    int num = 0;
    for(int step = 0; step < length; step++)
    {
        char ch = string[step] - 'a';
        if (Trie.array[num].nextLetter[ch] == -1)
        {
            vector_add(&Trie, makeTrieVertex(num, string[step]));
            Trie.array[num].nextLetter[ch] = Trie.top - 1;
        }
        num = Trie.array[num].nextLetter[ch];
    }
    Trie.array[num].isWord = 1;
    vectorS_add(&Pattern, string);
    Trie.array[num].parent = Pattern.top - 1; 
}
int get_auto_move(int v, char ch);

int get_suff_link(int v)
{
    if(Trie.array[v].suff_link == -1)
    {
        if(v == 0 || Trie.array[v].par == 0)
        {
            Trie.array[v].suff_link = 0;
        }
        else
        {
            Trie.array[v].suff_link = get_auto_move(get_suff_link(Trie.array[v].par), Trie.array[v].symb);
        }
    }
    return Trie.array[v].suff_link;
}

int get_auto_move(int v, char ch)
{
    if (Trie.array[v].auto_move[ch] == -1)
    {
        if(Trie.array[v].nextLetter[ch] != -1)
        {
            Trie.array[v].auto_move[ch] = Trie.array[v].nextLetter[ch];
        }
        else
        {
            if (v == 0)
            {
                Trie.array[v].auto_move[ch] = 0;
            }
            else
            {
                Trie.array[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
            }
        }
    }
    return Trie.array[v].auto_move[ch];
}

int get_suff_flink(int v)
{
    if (Trie.array[v].suff_flink == -1)
    {
        int u = get_suff_link(v);
        if (u == 0) //либо v - корень, либо суф. ссылка v указывает на корень 
        {
            Trie.array[v].suff_flink=0;
        }
        else
        {
            Trie.array[v].suff_flink=(Trie.array[u].isWord) ? u : get_suff_flink(u);
        }
    }
   return Trie.array[v].suff_flink;
}

int IsInTrie(const char* string, int length)
{
    int num = 0;   
    for (int step = 0; step < length; step++)
    {
        char ch = string[step] - 'a';
        if (Trie.array[num].nextLetter[ch] == -1)
        {
            return 0;         
        }
        num = Trie.array[num].nextLetter[ch];
   }
   return 1;
}

void check(int v, int i)
{
    for(int u = v; u != 0; u = get_suff_flink(u))
    {
        if(Trie.array[u].isWord)
        {
            printf("%d %s\n", i - (int)strlen(Pattern.array[Trie.array[u].parent]) + 1, Pattern.array[Trie.array[u].parent]);
        }
    }
}

void find_all_pos(const char* s)
{
    int u = 0;
    for(int i = 0; i < (int)strlen(s); i++)
    {
        u = get_auto_move(u, s[i] - 'a');
        check(u, i + 1);
    }
}

char buffer[1024];
int main(int argc, char** argv)
{
    initTrie();
    char * inputFile = argv[1];
    for(int step = 2; step < argc; step++)
    {
        add_string_to_trie(argv[step], strlen(argv[step]));
    }    
    FILE *in = fopen(inputFile, "r");
    while(scanf("%s", buffer) != EOF)
    {
        find_all_pos(buffer);
        memset(buffer, '\0', sizeof(buffer));
    }
    return 0;
}