typedef struct Node
{
    int nextLetter[128];//переход автомата
    int parent;
    int isWord;
    int suff_link;
    int auto_move[128]; //auto_move - запоминание перехода автомата
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
void vector_add(vector* array, Node vertex);
void vectorS_add(vectorS* array, char* string);
void initTrie();
void add_string_to_trie(char* string, int length);
void find_all_pos(const char* s, int n);
void freeTrie();