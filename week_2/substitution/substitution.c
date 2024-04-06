#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check if exactly one command-line argument is provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key(26 character set)\n");
        return 1; // Return an error code if the argument count is incorrect
    }

    int key_length = strlen(argv[1]);

    // Check if the second argument has 26 characters
    if (key_length != 26)
    {
        printf("Usage: ./substitution key(must be 26 character set)\n");
        return 1; // Return an error code if the key length is not 26
    }

    // Check for duplicates in key
    for (int i = 0; i < 26; i++)
    {
        char check_char = tolower(argv[1][i]);
        for (int j = i + 1; j < 26; j++)
        {
            char iterated_char = tolower(argv[1][j]);
            if (check_char == iterated_char)
            {
                printf("Please enter a key(26 character set) without duplicates\n");
                return 1; // Return an error code if duplicate characters are found in the key
            }
        }
    }

    // Check if the second argument is alphabetic and doesn't have spaces nor punctuation marks
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isalpha(argv[1][i]) || isspace(argv[1][i]) || ispunct(argv[1][i]))
        {
            printf("Please enter a key(26 character set)\n");
            return 1; // Return an error code if the key contains non-alphabetic characters, spaces,
                      // or punctuation marks
        }
    }

    char key[27];         // Plus one due to null terminator
    strcpy(key, argv[1]); // Copy the key from the command-line argument to the key array

    string plain_text = get_string("Plaintext:  ");
    int plain_len = strlen(plain_text);
    char ciphertext[plain_len + 1];
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int index;

    for (int i = 0; i < plain_len; i++)
    {
        char current_char = plain_text[i];

        if (isalpha(current_char))
        {
            // Find index of current character in alphabet
            char *position = strchr(alphabet, tolower(current_char));
            if (position != NULL)
            {
                index = position - alphabet;

                // Determine the corresponding character in the key
                char based_type_char =
                    isupper(current_char) ? toupper(key[index]) : tolower(key[index]);

                ciphertext[i] =
                    based_type_char; // Assign the encrypted character to the ciphertext array
            }
        }
        else
        {
            ciphertext[i] = plain_text[i]; // Copy non-alphabetic characters as they are
        }
    }

    ciphertext[plain_len] = '\0'; // Add null terminator to the ciphertext string

    printf("ciphertext: %s\n", ciphertext); // Print the encrypted text

    return 0; // Return success code
}
