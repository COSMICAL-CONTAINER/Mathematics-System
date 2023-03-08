#include <string.h>
#include <stdlib.h>
#include "my_string.h"

String String_Init(const char* str)
{
    String result = (String)malloc(sizeof(char) * (strlen(str) + 1) );
    strcpy(result, str);
    return result;
}

String String_AddChar(String str, char c)
{
    size_t len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
    return str;
}

String String_Addxchar_temp(String str, size_t times, char c)
{
    size_t len = strlen(str);
    if(times > 0)
    {
        String result = (String)calloc(len + times, sizeof(char));
        strcpy(result, str);
        for(int i = 0; i < times; ++i)
        {
            result[len + i] = c;
        }
        result[len + times] = '\0';
        return result;
    }
    else
    {
        return str;
    }
}
