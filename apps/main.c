#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modern.h"
#include "noerr.h"

static char random_text[] = "The scarlet dragonfly is a species of dragonfly in the family "
                            "Libellulidae";

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        fprintf(stderr, "%s doesn't accept arguments\n", argv[0]);
        return 1;
    }

    printf("%s\n", random_text);
    char *token = strtok(random_text, " ");
    while (token)
    {
        printf("%s ", reverse_in_place(token));
        token = strtok(NULL, " ");
    }
    printf("\n\n");

    char *noerr_str = get_error(EACCES);
    printf("EACCES - %s\n", noerr_str);
    free(noerr_str);
    return 0;
}
