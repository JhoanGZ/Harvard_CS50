#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numbers[] = {20, 500, 10, 5, 100, 1, 50};

    int number = get_int("Insert number to search: ");
    for (int i = 0; i < 7; i++)
    {
        if (numbers[i] == number)
        {
            printf("Number Found\n");
            return 0;
        }
    }
    printf("Number Not found\n");
    return 1;
}
