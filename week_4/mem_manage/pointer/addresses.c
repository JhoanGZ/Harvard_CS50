#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;

    printf("To print normally: %i\n", n);
    printf("To print what's inside n: %i\n", *p);
    printf("To print memory address: %p\n", &n);
}
