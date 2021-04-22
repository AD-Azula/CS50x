//Emilio Gallegos
// December 8th 2020

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{

    // check for arguments
    if (argc == 2 && isdigit(*argv[1]))

    {
        //using the atoi function to convert any string into an integer
        int k = atoi(argv[1]);
        // prompt user for a code to encrypt
        string ss = get_string("Plain Text: ");
        printf("ciphertext: ");

        // iterate through plain text letter by letter
        for (int i = 0, n = strlen(ss); i < n; i++)
        {
            // checking if it is lowercase and if it meets requirements
            if (ss[i] >= 'a' && ss[i] <= 'z')
            {
                printf("%c", (((ss[i] - 'a') + k) % 26) + 'a');
            }

            else if (ss[i] >= 'A' && ss[i] <= 'Z')
            {
                printf("%c", (((ss[i] - 'A') + k) % 26) + 'A');
            }

            else

            {
                printf("%c", ss[i]);
            }
        }

        printf("\n");
        return 0;
    }

    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}

// I actually had trouble because my output was Cipher Text: XXX instead of ciphertext: XXX haha! gotta be careful.