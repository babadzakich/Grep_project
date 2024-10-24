typedef struct string_str
{
    char* array;
    size_t cap, size;
}String;
extern String data;
extern int len;
void add_data(char* buff);