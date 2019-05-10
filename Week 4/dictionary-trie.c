// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a trie
node *root;

// global counter var
unsigned long counter = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }

    // set default settings for root trie
    nullTheChildrenValue(root);

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];
    // starting trie
    node *currentTrie = root;

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        // get back array of index positions of the letters in word
        int *array = getIndexOfLetters(word);
        // loop thru array
        for (int i = 0; i < strlen(word); i++)
        {
            //check if valid
            if (currentTrie->children[array[i]] == NULL)
            {
                // create new trie
                node *newTrie = malloc(sizeof(node));
                if (newTrie == NULL)
                {
                    return false;
                }
                // set default settings
                nullTheChildrenValue(newTrie);
                // set the trie
                currentTrie->children[array[i]] = newTrie;
                // update the current trie
                currentTrie = currentTrie->children[array[i]];
            }
            else
            {
                // update the current trie
                currentTrie = currentTrie->children[array[i]];
            }
        }
        // set is_word to true
        currentTrie->is_word = true;
        // free array from heap
        free(array);
        // increment counter
        counter ++;
        //reset reference back to root node.
        currentTrie = root;
    }

    /*
    bool exist = root->children[2]->children[0]->children[19]->is_word;
    bool existy = root->children[2]->children[0]->is_word;
    bool exizt = root->children[15]->children[14]->children[14]->children[15]->children[26]->children[18]->is_word;
    bool poop = root->children[1]->children[14]->children[1]->children[26]->children[18]->is_word;
    bool poop2 = root->children[15]->children[14]->children[14]->children[15]->is_word;

    printf("%d\n", exist);
    printf("%d\n", existy);
    printf("%d\n", exizt);
    printf("%d\n", poop);
    printf("%d\n", poop2);
    */

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
    int *array = getIndexOfLetters(word);
    // starting trie
    node *currentTrie = root;

    // loop thru array
    for (int i = 0; i < strlen(word); i++)
    {
        //check if at currentTrie, the provided index from array exists
        if (currentTrie->children[array[i]] == NULL)
        {
            free(array);
            return false;
        }
        else
        {
            currentTrie = currentTrie->children[array[i]];
        }
    }

    if (currentTrie->is_word == true)
    {
        free(array);
        return true;
    }

    // free array
    free(array);
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // starting trie
    node *startingTrie = root;
    // send this trie to a new function to be made..
    return traverseAndFreeTries(startingTrie);
}

bool traverseAndFreeTries(node *currentTrie)
{
    for (int i = 0; i < N; i++)
    {
        if (currentTrie->children[i] != NULL)
        {
            traverseAndFreeTries(currentTrie->children[i]);
        }
    }
    free(currentTrie);
    return true;
}

// return array of indexes based on chars of dictionary word
int *getIndexOfLetters(const char *word)
{
    int length = strlen(word);
    // cannot alter const pointer, calloc memory to prevent garbage values
    int *letterArray = calloc((length), sizeof(int));
    if (letterArray == NULL)
    {
        return false;
    }
    for (int i = 0; i < length; i++)
    {
        if (word[i] == '\'')
        {
            letterArray[i] = 26;
        }
        else
        {
            letterArray[i] = tolower(word[i]) - 'a';
        }
    }
    // return array of letter index
    return letterArray;
}

// null all values of children array
void nullTheChildrenValue(node *trie)
{
    trie->is_word = false;
    for (int i = 0; i < N; i++)
    {
        trie->children[i] = NULL;
    }
}
