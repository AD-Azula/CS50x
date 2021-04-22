//Emilio Gallegos Garcia
#include <stdio.h>
#include <cs50.h>
//we initialize the program
int main(void)
{
    //we let C know that the input the user is going to give us is a string therefore we make use of the function get_string.
    string answer = get_string("what is your name?\n");
    //the %s\n is to let C understand that we are waiting (in this case) for a STRING to be given by the user and then printing the answer alongside with the message hello.
    printf("hello, %s\n", answer);