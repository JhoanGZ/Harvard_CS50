#include <cs50.h>
#include <stdio.h>

typedef struct {
    string name;
    int votes;
} candidate;

int main(void)
{
    const int num_candidates = 3;
    candidate candidates[num_candidates];

    candidates[0].name = "Carter";
    candidates[0].votes = 10;

    candidates[1].name = "Clinton";
    candidates[1].votes = 12;

    candidates[2].name = "Trump";
    candidates[2].votes = 20;

    int highest_vote = 0;
    string most_voted_candidate;

    for (int i = 0; i < num_candidates; i++)
    {
        if ( candidates[i].votes > highest_vote)
        {
            highest_vote = candidates[i].votes;
            most_voted_candidate = candidates[i].name;
        }
    }

    printf("Highest vote is: %i and the winner is: %s!\n", highest_vote, most_voted_candidate);

}

