//Emilio Gallegos Garcia
#include <cs50.h>
#include <stdio.h>
//initialize program
int main(void)
{
    //we essentially start our do while loop that says that the user should be prompet for a POSITIVE int and it will be reprompted if it isnt.
    //i=rows, j=spaces n=the input the user types
    int n;

    do
    {
        n = get_int("Height: ");
    } while (n < 1 || n > 8); //we set the limit from 1 to 8

    for (int i = 1; i <= n; i++) //we initialize the i integer and make it repeat itself
    {
        for (int j = n - i; j > 0; j--) //we print a space " " if the new integer is equal to n and bigger than the number of rows (i), j essentially represents the variable for spaces.
        {
            printf(" ");
        }

        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        // for the spaces between the hashes we print a double blankspace
        printf("  ");

        // Column loop - right hand hashes
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        printf("\n"); //new line or in this case new row
    }
}