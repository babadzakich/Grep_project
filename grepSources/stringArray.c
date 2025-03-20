#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "stringArray.h"

String data;
int len = 0;
void mystrncat(char* dest, char* src, int n)
{
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
