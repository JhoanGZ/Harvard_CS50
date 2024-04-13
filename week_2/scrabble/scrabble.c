#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_question(string input);

int main(void)
{
    // Starting to ask for players inputs
    string player_1 = get_string("Player 1 Input: ");
    string player_2 = get_string("Player 2 Input: ");

    // Evaluating players responses with functions in order to get their scores
    int value_player_1 = calculate_question(player_1);
    int value_player_2 = calculate_question(player_2);

    // Comparing results accordingly
    if (value_player_1 > value_player_2)
    {
        printf("Player 1 wins\n");
    }
    else if (value_player_1 < value_player_2)
    {
        printf("Player 2 wins\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Function to create calculations for a input.

int calculate_question(string input)
{
    // Creating the arrays of letters and values
    char letter_array[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                           'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
                           };
    int value_array[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                         1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
                         };
    int result = 0;
    int input_length = strlen(input);

    // Starting iterations

    for (int i = 0; input_length > i; i++)
    {
        char input_converted = toupper(input[i]);
        for (int j = 0; j < 26; j++) // letter_array length's because We need to check through all the letters and find its values.
        {
            if (input_converted == letter_array[j])
            {
                result += value_array[j];
                break; // Once there's a match,there's no need to continue searching. Performance concern.
            }
        }
    }

    return result;
}
