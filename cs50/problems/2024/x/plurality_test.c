#import <string.h>
#import <cs50.h>
#import <stdio.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];

int candidate_counts;
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{

    if(argc<2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

     candidate_counts=argc-1;

    if(candidate_counts>MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for(int i=0;i<candidate_counts;i++)
    {
        candidates[i].name=argv[i+1];
        candidates[i].votes=0;
    }
    int nums=get_int("Number of voters: ");
    for(int i=0;i<nums;i++)
    {
        string name = get_string("Vote: ");
        if(!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }
    print_winner();
}
bool vote(string name)
{
    for(int i=0;i<candidate_counts;i++)
    {
        if(strcmp(candidates[i].name,name)==0)
        {
            candidates[i].votes+=1;
            return true;
        }
    }
    return false;
}
void print_winner(void)
{
    int maxvote=0;
    for(int i=0 ; i<candidate_counts;i++)
    {
        if(candidates[i].votes>maxvote)
        {
            maxvote=candidates[i].votes;
        }
    }
    for(int i=0;i<candidate_counts;i++)
    {
        if(maxvote==candidates[i].votes)
        {
            printf("%s\n",candidates[i].name);
        }
    }
    return;
}
