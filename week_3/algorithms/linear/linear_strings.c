#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string strings[] = {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};

    string word = get_string("Insert word to search:\n");
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(strings[i], word) == 0)
        {
            printf("Word found!\n");
            return 0;
        }
    }
    printf("Word not found!\n");
    return 1;
}
