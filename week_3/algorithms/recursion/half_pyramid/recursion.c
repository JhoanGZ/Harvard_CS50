#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void)
{
    int height = get_int("height: \n");
    draw(height);
}


void draw(int n)
{
    // If there's nothing to draw return.
    if (n <= 0)
    {
        printf("End of Program\n");
        return;
    }

    // Print pyramid of height n - 1
    draw(n - 1);

    // Starts printing as the call stack indicates
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }

    printf("\n");




}
