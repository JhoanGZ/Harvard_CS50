#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
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
int is_candidate(string name);
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
int compare_pairs(const void *element1, const void *element2);
void sort_pairs(void);
void lock_pairs(void);
bool has_cycle(int winner, int loser);
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

// Searching into candidates if there's a match
int is_candidate(string name)
{
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        if (strcmp(name, candidates[candidate]) == 0)
        {
            return candidate;
        }
    }
    return -1;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int voted_candidate_index = is_candidate(name);
    if (voted_candidate_index != -1)
    {
        ranks[rank] = voted_candidate_index;
        return true;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int row = 0; row < candidate_count; row++)
    {
        for (int col = row + 1; col < candidate_count; col++)
        {
            preferences[ranks[row]][ranks[col]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            int vote_majority = preferences[i][j] - preferences[j][i];
            if (vote_majority > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (vote_majority < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // No need to handle the case where vote_majority equals 0
        }
    }
}

// Using pointers to obtain
int compare_pairs(const void *element1, const void *element2)
{
    // Convert generic pointers to pair pointers and dereference them
    const pair *first_pair = (const pair *) element1;
    const pair *second_pair = (const pair *) element2;

    // Calculate the margin of victory for the second candidate in the pair
    int second_candidate_votes_margin = preferences[second_pair->winner][second_pair->loser] -
                                        preferences[second_pair->loser][second_pair->winner];

    // Calculate the margin of victory for the first candidate in the pair
    int first_candidate_votes_margin = preferences[first_pair->winner][first_pair->loser] -
                                       preferences[first_pair->loser][first_pair->winner];

    // Compare the margins of victory and return the result
    return second_candidate_votes_margin - first_candidate_votes_margin;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), compare_pairs);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (has_cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

bool has_cycle(int winner_candidate, int loser_candidate)
{
    if (winner_candidate == loser_candidate)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser_candidate][i] == true)
        {
            if (has_cycle(winner_candidate, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool winner_votation = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                winner_votation = false;
                break;
            }
        }
        if (winner_votation == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
}
