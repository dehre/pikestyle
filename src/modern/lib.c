#include <string.h>

#include "modern.h"

char *reverse_in_place(char *str)
{
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
    return str;
}
