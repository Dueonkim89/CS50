#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checkIfNotValidKey(string key, int length);
int getIntForASCII(char letter);
void shiftAndPrintLetters(string text, int asciiArr[], int keyLength);

int main(int argc, string argv[])
{
    // Null value for key
    if (!argv[1]) {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    // Get length of second argument
    int len = strlen(argv[1]);

    // Not 2 arguments or not valid key
    if (argc !=2 || checkIfNotValidKey(argv[1], len))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }

    // create array for ascii characters
    int asciiArray[len];

    // loop through the keyword and get ascii representation
    for (int i = 0; i<len; i++)
    {
        char letter = argv[1][i];
        int numb = getIntForASCII(letter);
        asciiArray[i] = numb;
    }

    //get plain text from user
    string plainText = get_string("plaintext: ");
    //send plain text, array, key length to new function
    shiftAndPrintLetters(plainText, asciiArray, len);
}

void shiftAndPrintLetters(string text, int asciiArr[], int keyLength)
{
    char defaultLowerChar = 'a';
    char defaultUpperChar = 'A';

    int lowerEndRange = 122;
    int upperEndRange = 90;

    int counter = 0;

    printf("ciphertext: ");
    for (int i=0, n = strlen(text); i<n; i++)
    {
        // Check if counter >= keyLength if so reset to 0.
        if (counter > keyLength - 1)
        {
          counter = 0;
        }

        // Not an alphabet, just print it.
        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
        else if (isupper(text[i]))
        {
            int numb = text[i];
            if (numb + asciiArr[counter] <= upperEndRange)
            {
                printf("%c", text[i] + asciiArr[counter]);
            }
            else
            {
                int increase = (numb + asciiArr[counter]) - upperEndRange - 1;
                printf("%c", defaultUpperChar + (increase));
            }
            counter ++;
        }
        else
        {
            int numb = text[i];
            if (numb + asciiArr[counter] <= lowerEndRange)
            {
                printf("%c", text[i] + asciiArr[counter]);
            }
            else
            {
                int increase = (numb + asciiArr[counter]) - lowerEndRange - 1;
                printf("%c", defaultLowerChar + (increase));
            }
            counter ++;
        }
    }
   printf("\n");
}

int checkIfNotValidKey(string key, int length)
{
    for (int i = 0; i<length; i++)
    {
        if (!isalpha(key[i]))
        {
            return 1;
        }
    }
    return 0;
}

int getIntForASCII(char letter)
{
    string lowerCaseAlpha = "abcdefghijklmnopqrstuvwxyz";
    char lowerCase = tolower(letter);

    // Find corresponding index value
    for (int i = 0; i<26; i++)
    {
        if (lowerCaseAlpha[i] == lowerCase)
        {
            return i;
        }
    }
    return 1;
}
