// #include <cs50.h>
// #include <stdio.h>
// #include <string.h>

// // Max number of candidates
// #define MAX 9

// // Candidates have name and vote count
// typedef struct
// {
//     string name;
//     int votes;
// } candidate;

// // Array of candidates
// candidate candidates[MAX];

// // Number of candidates
// int candidate_count;
// // string elected_names[voter_count];

// // Function prototypes
// bool vote(string name, candidate *candidates_list, int voter_count);
// void print_winner(candidate *candidate_final, int count, int highest_vote);

// int main(int argc, string argv[])
// {
//     // Check for invalid usage
//     if (argc < 2)
//     {
//         printf("Usage: plurality [candidate ...]\n");
//         return 1;
//     }

//     // Populate array of candidates
//     candidate_count = argc - 1;
//     if (candidate_count > MAX)
//     {
//         printf("Maximum number of candidates is %i\n", MAX);
//         return 2;
//     }

//     for (int i = 0; i < candidate_count; i++)
//     {
//         candidates[i].name = argv[i + 1];
//         candidates[i].votes = 0;
//     }

//     int voter_count = get_int("Number of voters: ");

//     // Loop over all voters
//     for (int i = 0; i < voter_count; i++)
//     {
//         string name = get_string("Vote: ");

//         // Check for invalid vote
//         if (!vote(name, candidates, voter_count))
//         {
//             printf("Invalid vote.\n");
//         }

//         for (int j = 0; j < candidate_count; j++)
//         {
//             // Adding the respective vote
//             if (strcmp(name, candidates[j].name) == 0)
//             {
//                 candidates[j].votes += 1;
//             }
//         }
//     }

//     int highest_vote = 0;

//     for (int j = 0; j < candidate_count; j++)
//     {
//         if (candidates[j].votes > highest_vote)
//         {
//             highest_vote = candidates[j].votes;
//         }
//     }

//     // Display winner of election
//     print_winner(candidates, candidate_count, highest_vote);
// }

// // Update vote totals given a new vote
// bool vote(string name, candidate *candidates_list, int voter_count)
// {
//     for (int i = 0; i < voter_count; i++)
//     {
//         if (strcmp(candidates_list[i].name, name) == 0)
//         {
//             return true;
//         }
//     }
//     return false;
// }

// // Print the winner (or winners) of the election
// void print_winner(candidate *candidate_final, int count, int highest_vote)
// {
//     for (int i = 0; i < count; i++)
//     {
//         if (candidate_final[i].votes == highest_vote)
//         {
//             printf("%s\n", candidate_final[i].name);
//         }
//     }
// }


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
bool vote(string name, int candidate_count, candidate *candidate_list);
void print_winner(candidate *candidate_final, int count);

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
        if (!vote(name, candidate_count, candidates))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner(candidates, candidate_count);
}

// Update vote totals given a new vote
bool vote(string name, int count, candidate *candidate_list)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(name, candidate_list[i].name) == 0)
        {
            candidate_list[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(candidate *candidate_final, int count)
{
    int highest_vote = 0;
    for ( int i = 0; i < count; i++)
    {
        if( candidate_final[i].votes > highest_vote)
        {
            highest_vote = candidate_final[i].votes;
        }
    }

    for ( int j = 0; j < count; j++)
    {
        if (candidate_final[j].votes == highest_vote)
        {
            printf("%s\n", candidate_final[j].name);
        }
    }

}
