#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "noerr.h"
#include "str_safe.h"

static inline size_t strerrorlen(errno_t errnum)
{
    return strlen(strerror(errnum));
}

char *get_error(errno_t errnum)
{
    size_t size = strerrorlen(errnum) + 1;
    char *msg = malloc(size);
    if (msg == NULL)
    {
        return NULL;
    }

    if (strerror_r(errnum, msg, size) != 0)
    {
        strcpy_safe(msg, size, "unknown error");
    }

    return msg;
}
