//Emilio Gallegos Garcia
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;

    do
    {
        dollars = get_float("How much change is owed: ");
    } while (dollars < 0);
    //so cents is essentially the input the user typed * 100
    // the number of coins stars on 0
    int cents = round(dollars * 100);
    int coins = 0;
    // we give the condition that cents is less or equal to 25
    while (cents >= 25)
    {
        cents -= 25; //esentially we ask if we could subtract 25 from the original input can we do it again? if we cant then it goes onto the next value
        coins++;
    }
    while (cents >= 10)
    {
        cents -= 10;
        coins++;
    }
    while (cents >= 5)
    {
        cents -= 5;
        coins++;
    }

    while (cents >= 1)
    {
        cents -= 1;
        coins++;
    }
    printf("%i\n", coins); //we print the value of coins using a placeholder %i/n because we are dealing with integers
}