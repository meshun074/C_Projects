// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
int numofwords = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int bucket = (int)tolower(*(word + 0)) % 97;
    for(node *tmp = table[bucket]; tmp != NULL; tmp = tmp->next)
    {
        if(strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return (int)tolower(*(word + 0)) % 97;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dic = fopen(dictionary, "r");
    if(dic == NULL)
    {
        return false;
    }
    char letter;
    int bucket = 0;
    while(1)
    {
        letter = fgetc(dic);
        if(letter == EOF)
        {
            break;
        }
        if(isalpha(letter))
        {
            numofwords++;
            node *data = malloc(sizeof(node));
            int numofletters = 0;
            data->word[numofletters] = letter;
            while(1)
            {
                letter = fgetc(dic);
                if(isalpha(letter) || letter == '\'')
                {
                    numofletters++;
                    data->word[numofletters] = letter;
                }
                else
                {
                    break;
                }
            }
            numofletters++;
            data->word[numofletters] = '\0';
            data->next = NULL;
            bucket = hash(data->word);
            if(table[bucket] == NULL)
            {
                table[bucket] = data;
            }
            else
            {
                data->next = table[bucket];
                table[bucket] = data;
            }
        }
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(numofwords > 0)
    {
        return numofwords;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
