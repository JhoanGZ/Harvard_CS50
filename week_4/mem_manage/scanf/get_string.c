#include <stdio.h>

int main(void)
{
    // wrong way
    // char *string;
    // printf("Enter String: ");
    // scanf("%s\n", string);
    // printf("Input String: %s\n", string);
    // In this exercise clang was executed.
    // clang -o get_string -Wno-uninitialized get_string.cls

    char string[6]; // In order to receive 5 bites string 1+ Null like "hello"
    printf("Enter String: ");
    scanf("%s", string);
    printf("Input String: %s\n", string);
}
