#include <cs50.h>
#include <stdio.h>

int countDigits(long n);
int sumOfDigits(int cardDigitsArray[], int length);

int main(void)
{
    // Prompt user for long (4 bytes of data)
    unsigned long numb = get_long("Number: ");

    // Keep looping, if input is less than zero.
    while (numb < 0)
    {
        numb = get_long("Number: ");
    }

    int lengthOfDigits = countDigits(numb);
    printf("Length of number is: %i\n", lengthOfDigits);

    // must be minimum 13 digits, max 16 digits
    if (lengthOfDigits < 13 || lengthOfDigits > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // Create array based on length of digits
    int cardDigitsArray[lengthOfDigits];
    // Starting array index;
    int arrayReference = 0;
    // Base number
    unsigned long long base = 1;
    // loop to length of card digits
    while (arrayReference < lengthOfDigits)
    {
        //  Set each digit into array starting from last number.
        cardDigitsArray[arrayReference] = (numb / base) % 10;
        arrayReference ++;
        base *= 10;
    }

    // Get sum of the card number based on Luhn's Algo
    int theSum = sumOfDigits(cardDigitsArray, lengthOfDigits);
    printf("The sum is: %i\n", theSum);

    // Check if divisible by 10
    if (theSum % 10 != 0) {
        printf("INVALID\n");
        return 0;
    }

    //check if AMEX
    if ((lengthOfDigits == 15 && cardDigitsArray[lengthOfDigits - 1] == 3) &&
    (cardDigitsArray[lengthOfDigits - 2] == 4 || cardDigitsArray[lengthOfDigits - 2] == 7))
    {
        printf("AMEX\n");
        return 0;
    }

    //check if VISA
    if ((lengthOfDigits == 13 || lengthOfDigits == 16) && (cardDigitsArray[lengthOfDigits - 1] == 4))
    {
        printf("VISA\n");
        return 0;
    }

    //check if MASTERCARD
    if ((lengthOfDigits == 16 && cardDigitsArray[lengthOfDigits - 1] == 5) &&
    (cardDigitsArray[lengthOfDigits - 2] == 1 || cardDigitsArray[lengthOfDigits - 2] == 2 ||
      cardDigitsArray[lengthOfDigits - 2] == 3 || cardDigitsArray[lengthOfDigits - 2] == 4 ||
      cardDigitsArray[lengthOfDigits - 2] == 5))
    {
        printf("MASTERCARD\n");
        return 0;
    }

    printf("INVALID\n");
}

int countDigits(long n)
{
    int digit = 0;
    while (n > 0) {
        n /= 10;
        digit ++;
    }
    return digit;
}

int sumOfDigits(int cardDigitsArray[], int length)
{
    int sum = 0;
    for (int i = 0; i<length; i++)
    {
        if (i % 2 != 0)
        {
            int digit = cardDigitsArray[i] * 2;
            // Find if its a 2 digit number
            if ((digit/10) % 10 != 0)
            {
                // Get first and second digits
                sum += (digit/1) % 10;
                sum += (digit/10) % 10;
            }
            else
            {
                sum += digit;
            }
        }
        else
        {
            sum += cardDigitsArray[i];
        }
    }
    return sum;
}
