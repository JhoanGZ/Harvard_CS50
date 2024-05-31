#include <cs50.h>
#include <stdio.h>

int factorial(int n);

int main(void)
{
    // Get positive value for n so as to procced with the factorial
    int n;
    do
    {
        n = get_int("Input a positive number: ");
    }
    while (n <= 0);

    // Print factorial

    printf("%i\n", factorial(n));
}

int factorial(int n)
{
    if ( n == 1)
    {
        return 1;
    }

    return n * factorial(n - 1);
}
