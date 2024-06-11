#include <stdio.h>

void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x , y);

    // To pass the address must be used & to send it
    swap(&x, &y);
    printf("x is %i, y is %i\n", x , y);
}

// If this code is left, the scope makes the values disappear
// Instead using pass by value to set the swapping
// It must be used pass by reference
// void swap(int a, int b)
// {
//     int temp = a;
//     a = b;
//     b = temp;
// }

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
