#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Buckets in hash table for each letter of the alphabet
const unsigned int N = 26;
node *table[N];

// Number of words in the dictionary
unsigned int word_count = 0;

bool check(const char *word)
{
    // Hash the word to obtain the index
    unsigned int index = hash(word);

    // Traverse the linked list at the hash table index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Comparing word case-insensitively
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number based on the first letter
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer to hold each word
    char buffer[LENGTH + 1];

    // Reading words from the file one at a time
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false;
        }

        // Copying the word into the new node
        strcpy(new_node->word, buffer);
        new_node->next = NULL;

        // Hashing the word to obtain the index
        unsigned int index = hash(buffer);

        // Inserting the node into the hash table at the appropriate index
        new_node->next = table[index];
        table[index] = new_node;

        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            // Free each node in the linked list
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
