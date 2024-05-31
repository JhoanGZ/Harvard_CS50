#include <cs50.h>
#include <stdio.h>

int collatz(int value);

int main(void)
{

    int value = get_int("number :\n");
    printf("%i\n", collatz(value));
}

int collatz(int value)
{
    if (value == 1)
    {
        return 0;
    }

    if (value % 2 == 0)
    {
        // It sums one because we need to follow up the number of steps so as it's need to print it out
        return 1 + collatz(value / 2);
    }

    if ((value % 2) != 0)
    {
        return 1 + collatz((3 * value) + 1);
    }

    return -1;
}
