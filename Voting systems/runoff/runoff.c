#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;
int voteround = 0;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if(argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if(candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for(int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if(voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for(int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for(int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if(!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while(true)
    {
        // Calculate votes given remaining candidates
        tabulate();
        voteround++;

        // Check if election has been won
        bool won = print_winner();
        if(won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if(tie)
        {
            for(int i = 0; i < candidate_count; i++)
            {
                if(!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for(int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
//In a particular voter rank for an individual voter
bool vote(int voter, int rank, string name)
{
    for(int i = 0; i < candidate_count; i++)
        {
            if(strcmp(name, candidates[i].name) == 0)
            {
                 preferences[voter][rank] = i;
                 return true;
            }
        }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
     for(int i = 0; i < voter_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            //for calculating a specific rank
            if(j == voteround)
            {
                // loop through a voters reference for a rank of voted candidate who is not eliminated
                // and count vote
                int check = 0;
                while(candidates[preferences[i][check]].eliminated)
                {
                    check++;
                    if(check > candidate_count)
                    {
                        break;
                    }
                }
                candidates[preferences[i][check]].votes += 1;
            }
        }
    }
    // TODO
    return;
}

// Print the winner of the election, if there is one
// and his number of votes is greater than half of the number of voters
bool print_winner(void)
{
    for(int j = 0; j < candidate_count; j++)
    {
        if(candidates[j].votes > voter_count / 2)
        {
            printf("%s\n",candidates[j].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
// if the candidate is not eliminated
int find_min(void)
{
    int min;
    for(int j = 0; j < candidate_count; j++)
    {
        if(!candidates[j].eliminated)
        {
            min = candidates[j].votes;
            break;
        }
    }
    for(int j = 0; j < candidate_count; j++)
    {
        if(candidates[j].votes < min && !candidates[j].eliminated)
        {
            min = candidates[j].votes;
        }
        }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
//if more than all the candidates number of votes are the same
bool is_tie(int min)
{
    for(int k = 0; k < candidate_count; k++)
        {
            if(!candidates[k].eliminated && candidates[k].votes != min)
            {
                return false;
            }
        }
    return true;
}

// Eliminate the candidate (or candidates) in last place
//with the min votes
void eliminate(int min)
{
    for(int c = 0; c < candidate_count; c++)
        {
            if(candidates[c].votes == min)
            {
                candidates[c].eliminated = true;
            }
        }
    return;
}
