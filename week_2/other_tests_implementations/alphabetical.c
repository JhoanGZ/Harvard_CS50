#include <cs50.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    string phrase = get_string("Enter your phrase\n");

    for ( int i = 0, length = strlen(phrase) - 1; i < length; i++)
    {
        if( phrase[i] > phrase[i + 1])
        {
            printf("Not in Alphabetical order\n");
            return 0;
        }
    }

    printf("In Alphabetical Order\n");
    return 0;
}
