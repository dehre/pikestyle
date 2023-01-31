#include <stdio.h>
#include <vec.h>

int main(void)
{
    struct Vec *v = vec_new(5);
    vec_push(v, 2);
    vec_push(v, 4);
    for (size_t i = 0; i < vec_len(v); i++)
    {
        printf("v[%zu] = %d\n", i, vec_nth(v, i));
    }
    printf("Done\n");
    return 0;
}
