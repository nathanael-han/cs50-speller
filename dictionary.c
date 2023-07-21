// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>

int count = 0; // variable to store number of words read from dictionary

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    int value = hash(word); // gets hash value of word

    for (node *cursor = table[value]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

    }
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char lower = tolower(word[0]);
    int number = lower - 'a';
    return number;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *read = fopen(dictionary, "r");    // opens dictionary

    if (read == NULL)    // checks if open was successful
    {
        return false;
    }

    else
    {
        char rword[LENGTH + 1];    // character array to read into
        while (fscanf(read, "%s", rword) != EOF)    // reads strings from file
        {
            node *tmp = malloc(sizeof(node));    // allocates memory
            if (tmp == NULL)     // checks if enough memory
            {
                free(tmp);
                return false;
            }
            else
            {
                count++;    // increments count of words

                strcpy(tmp->word, rword);    // copies word into node

                int index = hash(rword);    // gets hash of word

                if (table[index] == NULL)
                {
                    tmp ->next = NULL;
                    table[index] = tmp;
                }
                else
                {
                    tmp->next = table[index];
                    table[index] = tmp;
                }

            }

        }
    }
    fclose(read);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *cursor = table[i];
            while (cursor != NULL)
            {
                node *tmp = cursor;
                cursor = cursor ->next;
                free(tmp);
            }

        }
    }
    return true;
}
