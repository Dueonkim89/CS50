// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// global counter var
unsigned long counter = 0;

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // get the hash function of each word
        int hashIndex = hash(word);
        // malloc a node and copy string into it.
        node *node1 = malloc(sizeof(node));
        // make sure not null
        if (node1 == NULL)
        {
            unload();
            return false;
        }
        strcpy(node1->word, word);
        // store it into the hashtable
        if (hashtable[hashIndex] == NULL)
        {
            // assign next property to null for valgrind
            node1->next = NULL;
            hashtable[hashIndex] = node1;
        }
        else
        {
            node1->next = hashtable[hashIndex];
            hashtable[hashIndex] = node1;
        }

        // increment counter
        counter ++;
    }

    /*
    node *headNode = hashtable[2];
    // loop through all nodes to see if there is a match
    while (headNode != NULL)
    {

        printf("%s\n", headNode->word);

        // get next node in the list.
        headNode = headNode->next;
    }   */


    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // make lower case
    char *lowerCase = makeLowerCase(word);
    // get hash of word in text
    int hashIndex = hash(lowerCase);
    // get head node at the hash index
    node *headNode = hashtable[hashIndex];
    // loop through all nodes to see if there is a match
    while (headNode != NULL)
    {
        // check to see if word in headNode is a match
        if (strcmp(lowerCase, headNode->word) == 0)
        {
            // if match free memory, return  true
            free(lowerCase);
            return true;
        }
        // get next node in the list.
        headNode = headNode->next;
    }
    // else free memory return false
    free(lowerCase);
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // loop thru hash table
    for (int i = 0; i < N; i++)
    {
        // get head node at current i of hash table
        node *headNode = hashtable[i];
        while (headNode != NULL)
        {
            node *temp = headNode;
            headNode = headNode->next;
            free(temp);
        }
    }
    return true;
}

// make lower case
char *makeLowerCase(const char *word)
{
    int length = strlen(word);
    // cannot alter const pointer, calloc memory to prevent garbage values
    char *lowerCase = calloc((length + 1), sizeof(char));
    for (int i = 0; i < length; i++)
    {
        lowerCase[i] = tolower(word[i]);
    }
    // return lower case
    return lowerCase;
}
