#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> // For the atoi() function
#include <string.h>

int main(int argc, string argv[])
{
    // Check if exactly one command-line argument is provided
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert the argument to an integer
    int key = atoi(argv[1]);

    // Important to avoid negative numbers or zero in the user´s input
    if (key < 0)
    {
        printf("Pleaser enter a number above 0.\n");
        return 1;
    }

    // Check if the provided argument consists entirely of digits
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]) || isspace(argv[1][i]))
        {
            printf("Please enter a valid number as a key.\n");
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    string plain_text = get_string("Plaintext:  ");
    int plain_text_len = strlen(plain_text);
    char cipher_text[plain_text_len + 1]; // +1 for the null terminator

    // Iterate over each character in the plain text
    for (int i = 0; i < plain_text_len; i++)
    {
        char current_char = plain_text[i];

        // Check if the current character is a letter
        if (isalpha(current_char))
        {
            char base = isupper(current_char)
                            ? 'A'
                            : 'a'; // Determine the base character ('A' or 'a') for caps or minus.
            int shifted_index =
                (current_char - base + key) % 26;  // Shift the character by the key - delimiting
                                                   // boundaries for the proper count of letters.
            cipher_text[i] = base + shifted_index; // Store the shifted character
        }
        else
        {
            cipher_text[i] = current_char; // If it's not a letter, keep it unchanged
        }
    }
    cipher_text[plain_text_len] = '\0'; // Null-terminate the cipher text

    printf("ciphertext: %s\n", cipher_text);

    return 0;
}
