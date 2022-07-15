#include <stdlib.h>

char *strcpy_safe(char *dst, size_t dst_size, const char *src)
{
    if (dst_size > 0)
    {
        size_t i;
        for (i = 0; i < dst_size - 1 && src[i]; i++)
        {
            dst[i] = src[i];
        }
        dst[i] = '\0';
    }
    return dst;
}
