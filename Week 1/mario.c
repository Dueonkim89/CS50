#include <cs50.h>
#include <stdio.h>

void buildLeftSide(int n, int m);
void buildRightSide(int n);

int main(void)
{
    //prompt user for numb
    int numb = get_int("Height: ");

    while (numb < 1 || numb > 8)
    {
        numb = get_int("Height: ");
    }

    for (int i = 0; i < numb; i++)
    {
        //build left side, pass parameter of i and numb
        buildLeftSide(i, numb);
        // make 2 gaps of space
        printf(" ");
        printf(" ");
        // build right rightSide, pass parameter of i and numb
        buildRightSide(i);
        //on to next line
        printf("\n");
    }
}

void buildLeftSide(int n, int m)
{
    for (int j = 1; j <= m; j++)
    {
        if (j + n < m)
        {
            printf(" ");
        } else
        {
            printf("#");
        }
    }
}

void buildRightSide(int n)
{
    for (int j = 0; j < n+1; j++)
    {
        if (j <= n)
        {
            printf("#");
        } else
        {
            printf(" ");
        }
    }
}
