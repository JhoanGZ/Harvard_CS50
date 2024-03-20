#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mario-more
bool is_input_number(string valid_input);
void left_blank_space_builder(int spaces);
void right_side_brick_builder(int bricks);
void gap_builder(void);
void left_side_brick_builder(int bricks);

int main(void)
{
    int height;
    bool start;

    do
    {
        // Ask for pyramid's height
        string input = get_string("Please input the desired height:\n");

        // Verify if the input is a number
        bool valid_input = is_input_number(input);

        // if the verification fails, we return to the initial prompt
        if (!valid_input)
        {
            start = false;
            printf("No valid input.\n");
            printf("Please enter a number between 1 and 8..\n");
            continue;
        }

        // String is converted to Integer
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
        left_blank_space_builder(i);
        right_side_brick_builder(increment);
        gap_builder();
        left_side_brick_builder(increment);
        printf("\n");   // Break line after we print every line of block
        increment += 1; // need to feedback the brick builder
    }
}

// Functions

bool is_input_number(string valid_input)
{
    for (int i = 0; i < strlen(valid_input); i++)
    {
        if (!isdigit(valid_input[i]) || isblank(valid_input[i]))
        {
            return false;
        }
    }
    return true;
}

void left_blank_space_builder(int spaces)
{
    for (int j = 1; j <= spaces - 1; j++)
    { // We print j number of spaces for every iteration
        printf(" ");
    }
}

void right_side_brick_builder(int bricks)
{
    for (int k = 1; k <= bricks; k++)
    { // We print K number of blocks for every iteration
        printf("#");
    }
}

void gap_builder(void)
{
    printf("  ");
}

void left_side_brick_builder(int bricks)
{
    for (int k = 1; k <= bricks; k++)
    { // Print K number of blocks for every iteration
        printf("#");
    }
}
