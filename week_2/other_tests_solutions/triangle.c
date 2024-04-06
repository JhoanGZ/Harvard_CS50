#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool valid_triangle(int array[]);


int main(void)
{
    int numbers[3];
    bool validating_input = true;

    for (int i = 0, j = 1; i < 3; i++, j++)
    {
        numbers[i] = get_int("Please insert a side number %i\n", j);
    }

    bool result = valid_triangle(numbers);
    printf("%s\n", result ? "True" : "False");
    return 0;
}


bool valid_triangle(int array[])
{
    if( array[0] <= 0 || array[1]<= 0 || array[2] <= 0)
    {
        return false;
    }

    if( array[0] + array[1] <= array[2] ||  + array[2] <= array[0] || array[0] + array[2] <= array[1])
    {
        return false;
    }

    return true;
}
