//Emilio Gallegos
// December 8th 2020
#include <stdlib.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

int get_index(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name))
            return i;
    }
    return -1;
}
// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int candidate_index = get_index(name);
    if (candidate_index != -1)
    {
        ranks[rank] = candidate_index;
        return true;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++; //whatever ranks of i we get, its going to move and look at all ranks that are ahead of the given rank
        //meaning, if we had an area of ranks like: [0 1 2 3 4] if ranks of i is = 0,
        //then, ranks of i+1 all the way to the end of the area, voter 0 STILL has preference
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) //keeping in mind the struct pair that consists of a winner and a loser we need to add al such pairs.
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) //comparison of how many voters prefer the i candidate over the j vs how many voters prefer j candidate over i
            {
                pair p;
                p.winner = i;
                p.loser = j;
                pairs[pair_count++] = p;
            }
        }
    }
}

int comparison(const void *elem1, const void *elem2)
{ //according to documentation...
    pair f = *((pair *)elem1);
    pair s = *((pair *)elem2);
    int f_margin = preferences[f.winner][f.loser] - preferences[f.loser][f.winner];
    int s_margin = preferences[s.winner][s.loser] - preferences[s.loser][s.winner];
    return s_margin - f_margin;
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), comparison); //qsort takes an array and the size in the array
}

bool true_cycle_confirmed(int index, bool visitedArea[])
{
    if (visitedArea[index])
        return true;
    visitedArea[index] = true;
    for (int i = 0; i < candidate_count; i++) //iterate on all neighbors
    {
        if (locked[index][i] && true_cycle_confirmed(i, visitedArea))
        {
            return true;
        }
    }
    return false; //if it doesnt find any cycle it returns false
}

bool true_cycle(int f_index)
{
    bool visitedArea[candidate_count];
    for (int i = 0; i < candidate_count; i++)
        visitedArea[i] = false;
    return true_cycle_confirmed(f_index, visitedArea);
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) //MUST look at the order of every pair
//create edges until theres a cycle when it does find a cycle it will continue onto the next one, with the next pair
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true; //locked[i][j]
        //now we chceck for cycle in this candidate graph with i candidate
        if (true_cycle(i))
            locked[pairs[i].winner][pairs[i].loser] = false;
    }
}

bool i_source(int index)
{
    for (int i = 0; i < candidate_count; i++)
        if (locked[i][index])
            return false;
    return true;
}

int get_source()
{
    for (int i = 0; i < candidate_count; i++)
        if (i_source(i)) //if i IS a source
            return i;
    return -1;
}
// Print the winner of the election
void print_winner(void) //find the source of the graph
{
    int index = get_source();
    if (index != -1)
    {
        printf("%s\n", candidates[index]);
    }
}
// Done! This was kinda tough...