//Emilio Gallegos
// December 8th 2020
//Forgot to do this one before advancing to pset3!!

//Basic explanation: Import all librabries needed then ask  the user for an input
// we calculate number of words, number of letters and number of sentences in the text
// that is basically calculating index (using the forumla given in the assignment)
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    string thisIsAstring = get_string("Text: ");
    int numOfWords;
    int numOfSentences;
    int numOfLetters;
    numOfWords = numOfSentences = numOfLetters = 0;
    for (int i = 0, len = strlen(thisIsAstring); i < len; i++)
    {
        if (isalpha(thisIsAstring[i])) //function checks whether a character is an alphabet or not.
            numOfLetters++;
        if ((i == 0 && thisIsAstring[i] != ' ') || (i != len - 1 && thisIsAstring[i] == ' ' && thisIsAstring[i + 1] != ' '))
            numOfWords++;                                                                  //increment number of words by 1
        if (thisIsAstring[i] == '.' || thisIsAstring[i] == '?' || thisIsAstring[i] == '!') //if any elements are found we get a sentence
            numOfSentences++;                                                              //increment number of sentences by 1
    }
    //Calculate L and S to find out the index.
    float L = (numOfLetters / (float)numOfWords) * 100; //we add float so that we dont get an integer division
    float S = (numOfSentences / (float)numOfWords) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1) //we check in which grade the given index corresponds to, so we can print the appropiate index or message.
        printf("Before Grade 1\n");
    else if (index >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", index);
}
