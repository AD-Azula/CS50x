//Emilio Gallegos
// December 8th 2020

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

int f_index(string name)
{
    for (int i = 0; i < candidate_count; i++)
        if (strcmp(name, candidates[i].name) == 0) //The strcmp() function takes two strings and returns an integer. If strcmp returns 0 it means that name provided by the parameter and the current candidate are the same or not.
            return i;                              //of they're the same it returns the index
    return -1;
}
// Update vote totals given a new vote
bool vote(string name)
{
    int c_index = f_index(name); //firstly, we figure out the index that corresponds to the given name
    if (c_index != -1)           //check if candidate index (if ==0 returns false, if not...)
    {
        //increment candidate votes
        candidates[c_index].votes++; //using the given array we need to find the index and doing an increment of 1
        return true;
    }
    return false;
}

int find_max(void)
{
    int votes_max = candidates[0].votes;
    for (int i = 1; i < candidate_count; i++) //iterate
        if (candidates[i].votes > votes_max)  //if the current candidates is greater than the maximum votes so far we update is value.
            votes_max = candidates[i].votes;  //update maximum votes
    return votes_max;
}
// Print the winner (or winners) of the election
void print_winner(void)
{
    int votes_max = find_max(); //figuring out maximum number of votes then printing the name of the candidates that have the maximum number of votes.
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == votes_max)
            printf("%s\n", candidates[i].name);
    }
    return;
}
