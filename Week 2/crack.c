#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    int PWcombos = 52;

    bool found = false;
    // Get hash
    char *hashPW = argv[1];
    // Get salt
    char salt[3] = {hashPW[0], hashPW[1], '\0'};

    string possibleLetters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Create array of letters
    string possibleLettersArray[52] = {0};

    for (int i = 0; i<PWcombos; i++)
    {
        // Cannot create a fixed char array, since it will always point to same location
        // in memory even when its in a loop!
        // Allocating 2 bytes of memory * char size (1 byte)
        char *letter = malloc((2) * sizeof(char));
        letter[0] = possibleLetters[i];
        letter[1] = '\0';
        possibleLettersArray[i] = letter;
        // check if any of the 52 letters with salt are a match.
        char *pw = crypt(possibleLettersArray[i], salt);
        // if match, set bool to true, return 0
        if (strcmp(pw, hashPW) == 0)
        {
            printf("%s\n", possibleLettersArray[i]);
            found = true;
            return 0;
        }
    }

    // Two pointers to store PW combos
    string *comboA;
    string *comboB;
    long long counter = 0;

    // Create comboA, 2704
    comboA = malloc((PWcombos * 52) * sizeof(string));

    for (int i = 0; i<PWcombos; i++)
    {
        // Add new permutations to combo A
        for (int j = 0; j<PWcombos; j++)
        {
            char *new = malloc((2) * sizeof(string));
            strcpy(new, possibleLettersArray[i]);
            strcat(new, possibleLettersArray[j]);
			char *pw = crypt(new, salt);
			if (strcmp(pw, hashPW) == 0)
			{
				printf("%s\n", new);
				found = true;
				return 0;
			}
			// push this concat into old[counter]
            comboA[counter] = new;
            counter ++;
        }
    }

    // increase PW Combos, 2704 combos
    PWcombos *= 52;
    // reset counter to 0;
    counter = 0;

    // 140,608 combos, combo B
    comboB = malloc((PWcombos * 52) * sizeof(string));

    for (int i = 0; i<PWcombos; i++)
    {
        // Add new permutations to array
        for (int j = 0; j<52; j++)
        {
            char *new = malloc((5) * sizeof(string));
            strcpy(new, comboA[i]);
            strcat(new, possibleLettersArray[j]);
			char *pw = crypt(new, salt);
			if (strcmp(pw, hashPW) == 0)
			{
				printf("%s\n", new);
				found = true;
				return 0;
			}
            comboB[counter] = new;
            counter ++;
        }
        // free each [i] of combo A
        free(comboA[i]);
    }

    // Free combo A
    free(comboA);
    counter = 0;
    // 140,608
    PWcombos *= 52;

    // Recreate comboA, 7,311,616 combos
    comboA = malloc((PWcombos * 52) * sizeof(string));

    for (int i = 0; i<PWcombos; i++)
    {
        // Add new permutations to array
        for (int j = 0; j<52; j++)
        {
            char *new = malloc((5) * sizeof(string));
            strcpy(new, comboB[i]);
            strcat(new, possibleLettersArray[j]);
	        char *pw = crypt(new, salt);
			// if match, set bool to true, return 0
			if (strcmp(pw, hashPW) == 0)
			{
				printf("%s\n", new);
				found = true;
				return 0;
			}
            comboA[counter] = new;
            counter ++;
        }
        // free each [i] of combo B
        free(comboB[i]);
    }

     // Free combo B
    free(comboB);
    counter = 0;
    // 7,311,616
    PWcombos *= 52;

    // 	Requesting too much memory from heap, this cannot be granted.
    //	comboB = malloc((PWcombos * 52) * sizeof(5));

    for (int i = 0; i<PWcombos; i++)
    {
        // Find final permutations, 380,204,032 combos
        for (int j = 0; j<52; j++)
        {
            char *new = malloc((6) * sizeof(string));
            strcpy(new, comboA[i]);
            strcat(new, possibleLettersArray[j]);

            //compare hash to input
            char *pw = crypt(new, salt);
			if (strcmp(pw, hashPW) == 0)
			{
				printf("%s\n", new);
				found = true;
				return 0;
			}
            //free memory immediately
            free(new);
        }
        // free each [i] of combo A
        free(comboA[i]);
    }
    // Free combo A
    free(comboA);
}
