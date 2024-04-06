#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./mario number\n");
        return 1;


    int height = atoi(argv[1]);

    for (int i = 0; i < height; i++)
    {
        printf("#");
        printf("\n");
    }
    return 0;
}
