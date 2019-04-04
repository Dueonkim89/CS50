#include <cs50.h>
#include <stdio.h>

void buildLeftSide(int n, int m);

int main(void)
{
        //prompt user for numb
        int numb = get_int("Height: ");

        while (numb < 1 || numb > 8) {
                numb = get_int("Height: ");
        }

        for (int i = 0; i < numb; i++) {
                //build left side, pass parameter of i and numb
                buildLeftSide(i, numb);
                printf("\n");
        }
}

void buildLeftSide(int n, int m) {
        for (int j = 0; j < m; j++) {
                if ( (j + n) + 1 < m) {
                        printf(" ");
                } else {
                        printf("#");
                }
        }
}
