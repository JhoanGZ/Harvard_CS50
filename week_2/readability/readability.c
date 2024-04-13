#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
int calculate_letters(string input);
int calculate_words(string input);
int calculate_sentences(string input);
int coleman_liau_calc(string input);
void result_index(int input);

int main(void)
{
    string text = get_string("Type the text to evaluate: ");

    // Calculate Coleman-Liau index and print the result
    float index = coleman_liau_calc(text);

    // Print the grade level based on the index
    result_index(index);

    return 0;
}

// Function to calculate the quantity of letters
int calculate_letters(string input)
{
    int letter_counter = 0;
    int input_len = strlen(input);
    for (int i = 0; i < input_len; i++)
    {
        // Check if the character is alphabetic
        if (isalpha(input[i]))
        {
            letter_counter++; // Increment the letter counter
        }
    }
    return letter_counter;
}

// Function to calculate the quantity of words
int calculate_words(string input)
{
    int words_counter = 0;
    int input_len = strlen(input);
    for (int i = 0; i < input_len; i++)
    {
        // If the character at the current index is whitespace or the end of text,
        // consider it as the end of a word
        if (isspace(input[i]) || (((input[i]) == '.') && (input[i + 1] == '\0')))
        {
            words_counter++;
        }
    }
    return words_counter;
}

// Function to calculate the quantity of sentences
int calculate_sentences(string input)
{
    int sentence_counter = 0;
    int input_len = strlen(input);

    // Iterate through each character in the input text
    for (int i = 0; i < input_len; i++)
    {
        // Check if the current character indicates the end of a sentence
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            sentence_counter++;
        }
    }
    return sentence_counter;
}

// Function to calculate Coleman-Liau index
int coleman_liau_calc(string input)
{
    float L = (float) calculate_letters(input) / calculate_words(input) * 100;
    float S = (float) calculate_sentences(input) / calculate_words(input) * 100;
    return round((0.0588 * L) - (0.296 * S) - 15.8);
}

// Function to determine grade level based on index
void result_index(int index)
{
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
