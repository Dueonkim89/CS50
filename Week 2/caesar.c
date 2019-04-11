#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int checkIfNotValidKey(string key, int length);
void shiftAndPrintLetters(string text, int key);

int main(int argc, string argv[])
{
    // Null value for key
    if (!argv[1]) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Get length of second argument
    int len = strlen(argv[1]);

   // Not 2 arguments or not valid key
    if (argc !=2 || checkIfNotValidKey(argv[1], len))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);
    string plainText = get_string("plaintext: ");

    shiftAndPrintLetters(plainText, key);
}

int checkIfNotValidKey(string key, int length)
{
    for (int i = 0; i<length; i++)
    {
        if (!isdigit(key[i]))
        {
            return 1;
        }
    }
    return 0;
}

void shiftAndPrintLetters(string text, int key)
{
    char defaultLowerChar = 'a';
    char defaultUpperChar = 'A';

    int lowerEndRange = 122;
    int lowerBeginRange = 97;

    int upperBeginRange = 65;
    int upperEndRange = 90;

    int len = strlen(text);
    int modulo;

    printf("ciphertext: ");

    for (int i =0; i<len; i++)
    {
        if (!isalpha(text[i]))
        {
            printf("%c", text[i]);
        }
        else if (islower(text[i]))
        {
            if (key > 26)
            {
                modulo = key % 26;
                int numb = text[i];
                if (modulo + numb > lowerEndRange)
                {
                    modulo = modulo - (lowerEndRange - numb);
                    printf("%c", defaultLowerChar + (modulo -1));
                }
                else
                {
                    printf("%c", text[i] + (modulo));
                }
            }
            else if (key < 26)
            {
                int numb = text[i];
                if (numb + key > lowerEndRange)
                {
                    printf("%c", defaultLowerChar + (key - (lowerEndRange -numb) -1));
                }
                else
                {
                    printf("%c", text[i] + (key));
                }
            }
        }
        else if (isupper(text[i]))
        {
            if (key > 26)
            {
                modulo = key % 26;
                int numb = text[i];
                if (modulo + numb > upperEndRange)
                {
                    modulo = modulo - (upperEndRange - numb);
                    printf("%c", defaultUpperChar + (modulo -1));
                }
                else
                {
                    printf("%c", text[i] + (modulo));
                }
            }
            else if (key < 26)
            {
              int numb = text[i];
              if (numb + key > upperEndRange)
              {
                  printf("%c", defaultUpperChar + (key - (upperEndRange -numb) -1));
              }
              else
              {
                  printf("%c", text[i] + (key));
              }
            }
        }
    }
    printf("\n");
}
