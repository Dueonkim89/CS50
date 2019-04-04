
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
        // Prompt user for amount
        float input = get_float("Change: ");

        // Keep looping, if input is less than zero.
        while (input < 0)
        {
                input = get_float("Change: ");
        }

        // Set counter
        int counter = 0;
        // Set var to hold floating number
        float remainingChange;

        // If input greater than 1
        if (input > 1)
        {
                // Get float as an integer
                int wholeNumber = input;
                // Increment counter
                counter = 4 * wholeNumber;
                // Get the change remaining
                remainingChange = input - wholeNumber;
        }
        else
        {
                remainingChange = input;
        }

        remainingChange = (round(remainingChange  * 100)) / 100;
        printf("counter is: %i\n", counter);
        printf("Remaining change rounded is: %f\n", remainingChange);


        //  While loop as long as change is greater than 0
        while (remainingChange > 0)
        {
                if (remainingChange >= 1)
                {
                        counter += 4;
                        remainingChange -= 1;
                        remainingChange = (round(remainingChange  * 100)) / 100;
                }
                else if (remainingChange < 1 && remainingChange >= .25)
                {
                        printf("greaeter than a q\n");
                        counter += 1;
                        remainingChange -= .25;
                        remainingChange = (round(remainingChange  * 100)) / 100;
                }
                else if (remainingChange < .25 && remainingChange >= .10)
                {
                        counter += 1;
                        remainingChange -= .10;
                        remainingChange = (round(remainingChange  * 100)) / 100;
                }
                else if (remainingChange < .10 && remainingChange >= .05)
                {
                        counter += 1;
                        remainingChange -= .05;
                        remainingChange = (round(remainingChange  * 100)) / 100;
                }
                else if (remainingChange < .050000 && remainingChange != 0.000000)
                {
                        printf("hello world");
                        counter += 1;
                        remainingChange -= .01;
                        remainingChange = (round(remainingChange  * 100)) / 100;
                }
                else
                {
                        remainingChange -= .01;
                }
                printf("%f\n", remainingChange);
        }
        //print counter
        printf("%i\n", counter);
}
