#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("Input: ");

    if (s == NULL)
    {
        return 1;
    }

    char *t = malloc(strlen(s) + 1);

    if (t == NULL)
    {
        return 2;
    }

    // It only copies memory address
    // char *t = s;

    // It iterates throu the input but same is to use strcpy(s, t)
    for (int i = 0, len = strlen(s); i <= len; i++)
    {
        t[i] = s[i];
    }


    printf("%s\n", s);
    printf("%s\n", t);

    free(t);
    return 0;


}
