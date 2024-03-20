#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mario-less
void blank_space_builder(int quantity);
void brick_builder(int bricks);

int main(void)
{
    int height;
    bool start;

    do
    {
        // ask for pyramid's height
        string input = get_string("Please insert the desired height:\n");

        // verify if the input is a number
        bool valid_input = true;
        for (int i = 0; i < strlen(input); i++)
        {
            if (!isdigit(input[i]) || isblank(input[i]))
            {
                valid_input = false;
                break;
            }
        }

        // if the verification fails, we return to the initial prompt
        if (!valid_input)
        {
            start = false;
            printf("No valid input.\n");
            printf("Please enter a number between 1 and 8..\n");
            continue;
        }

        height = atoi(input);

        if (height == 0)
        {
            start = false;
            printf("Entered value cannot be zero or blank.\n");
            continue;
        }

        if (height < 1 || height > 8)
        {
            start = false;
            printf("Please enter a number between 1 and 8..\n");
            continue;
        }

        if (height >= 1 && height <= 8)
        {
            start = true;
        }
    }

    while (!start);
    int increment = 1;
    // We start with i as height, then we dimish the value until 1
    for (int i = height; i >= 1; i--)
    {
        blank_space_builder(i);
        brick_builder(increment);
        printf("\n");   // Break line after we print every line of block
        increment += 1; // need to feedback the brick builder
    }
}

void blank_space_builder(int spaces)
{
    for (int j = 1; j <= spaces - 1; j++)
    { // We print j number of spaces for every iteration
        printf(" ");
    }
}

void brick_builder(int bricks)
{
    for (int k = 1; k <= bricks; k++)
    { // We print K number of blocks for every iteration
        printf("#");
    }
}
