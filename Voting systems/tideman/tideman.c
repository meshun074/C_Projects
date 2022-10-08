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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

// Array of lock pair
int lpair[MAX];

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
    if(argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if(candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for(int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for(int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for(int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for(int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if(!vote(j, name, ranks))
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //if vote is a valid name save according to voters rank
    for(int k = 0; k < candidate_count; k++)
    {
        if(strcmp(candidates[k], name) == 0)
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //update the number of voter's who prefer a candidate over other candidates according to ranks
    int g;
    for(int h = 0; h < candidate_count - 1; h++)
    {
        g = h + 1;
        while(g > h && g < candidate_count)
        {
            preferences[ranks[h]][ranks[g]] += 1;
            g++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // add pair storing the winner and the loser of a particular pairing
    for(int o = 0; o < candidate_count; o++)
    {
        for(int u = 0; u < candidate_count; u++)
        {
            if ( o != u)
            {
                if(preferences[o][u] != 0 && preferences[o][u] > preferences[u][o])
                {
                    pairs[pair_count].winner = o;
                    pairs[pair_count].loser = u;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int higher = 0;
    int container = 0;
    // sort pair using a condition of pair with a greater winner value reference from preference
    for(int c = 0; c < pair_count; c++)
    {
        higher = c;
        for(int r = 0; r < pair_count; r++)
        {
            if(r > c && preferences[pairs[higher].winner][pairs[higher].loser]< preferences[pairs[r].winner][pairs[r].loser])
            {
                higher = r;
            }
        }
        if(c != higher)
        {
            container = pairs[c].winner;
            pairs[c].winner = pairs[higher].winner;
            pairs[higher].winner = container;

            container = pairs[c].loser;
            pairs[c].loser = pairs[higher].loser;
            pairs[higher].loser = container;
        }

    }
    return;
}

//check for cycle in locked graph where there is a cycle when all candidates locked pair array is 1
bool check_cycle(int check_lpair[])
{
    for(int w = 0; w < candidate_count; w++)
    {
        if(check_lpair[w] != 1)
        {
            return false;
        }
    }
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
// locate 1 in lock pair array for a candidate that loses a pair
void lock_pairs(void)
{
    int z = 0;
    for(int a = 0; a < pair_count; a++)
    {
        lpair[pairs[a].loser] = 1;
        //if cycle is formed reversed and break from the loop
        if(check_cycle(lpair))
        {
            lpair[pairs[a].loser] -= 1;
            break;
        }
    }
    return;
}



// Print the winner of the election
// print the name of the candidate with lock pair array index 0
void print_winner(void)
{
    for(int q = 0; q < candidate_count; q++)
    {
        if(lpair[q] == 0)
        {
            printf("%s\n", candidates[q]);
        }
    }
    return;
}

