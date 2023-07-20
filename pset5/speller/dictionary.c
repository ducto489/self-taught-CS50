// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define FNV_32_PRIME ((Fnv32_t)0x01000193)

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;
int counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char downcase[LENGTH + 1] = {};

    // Downcase the word
    for (int i = 0; word[i]; i++)
    {
        downcase[i] = tolower(word[i]);
    }

    node *p = table[hash(word) % N];
    // Finding word in linked-list
    while (p != 0 && strcmp(downcase, p->word) != 0)
    {
        p = p->next;
    }

    if (p != NULL)
    {
        return true;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
// return toupper(word[0]) - 'A';
// return (toupper(word[0]) - 'A') * 26 + (toupper(word[1]) - 'A');
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *file_dict = fopen(dictionary, "r");
    if (!file_dict)
    {
        return false;
    }

    char buffer[LENGTH + 1];
    // Repeatedly scan word in dictionary
    node *n = NULL;
    while (fscanf(file_dict, "%s", buffer) != EOF)
    {
        // Copy node
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file_dict);
            return false;
        }
        strcpy(n->word, buffer);

        // Insert node into hash table at this location
        int i = hash(buffer) % N;
        n->next = table[i];
        table[i] = n;

        // Variable for size() function
        counter++;
    }
    fclose(file_dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i], *tmp = table[i];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
