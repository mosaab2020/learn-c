#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct {
  string name;
  int votes;
  bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name); // done
void tabulate(void);                         // done
bool print_winner(void);                     // done
int find_min(void);                          // done
bool is_tie(int min);                        // done
void eliminate(int min);                     // not done
int first_candidate(void);                   // done

int main(int argc, string argv[]) {
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: runoff [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX_CANDIDATES) {
    printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i].name = argv[i + 1];
    candidates[i].votes = 0;
    candidates[i].eliminated = false;
  }

  // Get the number of voters
  voter_count = get_int("Number of voters: ");
  if (voter_count > MAX_VOTERS) {
    printf("Maximum number of voters is %i\n", MAX_VOTERS);
    return 3;
  }

  // Keep querying for votes
  for (int i = 0; i < voter_count; i++) {

    // Query for each rank
    for (int j = 0; j < candidate_count; j++) {
      string name = get_string("Rank %i: ", j + 1);

      // Record vote, unless it's invalid
      // j gives the rank number
      if (!vote(i, j, name)) {
        printf("Invalid vote.\n");
        return 4;
      }
    }

    printf("\n");
  }

  // Keep holding runoffs until winner exists
  while (true) {
    // Calculate votes given remaining candidates
    tabulate();

    // Check if election has been won
    bool won = print_winner();
    if (won) {
      break;
    }

    // Eliminate last-place candidates
    int min = find_min();
    bool tie = is_tie(min);

    // If tie, everyone wins
    if (tie) {
      for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated) {
          printf("%s\n", candidates[i].name);
        }
      }
      break;
    }

    // Eliminate anyone with minimum number of votes
    eliminate(min);

    // Reset vote counts back to zero
    for (int i = 0; i < candidate_count; i++) {
      candidates[i].votes = 0;
    }
  }
  return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name) {
  /*
   * ERR: there is a bug in this function! -- done bug fixed
   * TODO:
   * Look for the candidate called name -- done
   * If the candidate found: -- done
   *    update preferences so that they are the voter's
   *    rank preference, and return true
   *
   * If no candidates found, return false -- done
   */
  for (int i = 0; i < candidate_count; i++) {
    // If name matches candidates[i]:
    if (strcmp(candidates[i].name, name) == 0) {
      // Update the preferences array with the candidate's index
      preferences[voter][rank] = i;
      return true;
    }
  }
  return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void) {
  /*
   * TODO:
   * no thing todo
   */
  int candidate_index;
  // just for testing
  /*candidates[0].eliminated = true;*/

  // loop over voters
  for (int i = 0; i < voter_count; i++) {
    // loop over voter's preferred candidate
    for (int j = 0; j < candidate_count; j++) {
      // store the candidate index
      candidate_index = preferences[i][j];

      // check if the candidate at that index is is correct
      if (candidates[candidate_index].eliminated == false) {
        // increase the candidate vote by 1
        candidates[candidate_index].votes++;

        // after updating candidate vote, break the loop
        break;
      }
    }
  }

  return;
}

// Print the winner of the election, if there is one
bool print_winner(void) {
  /*
   * TODO:
   * loop over candidates -- done
   * check if candidate[i] votes are more than the needed votes -- done
   */

  // the needed number of votes for a candidate to win
  int needed_votes = voter_count / 2;

  // loop over candidates
  for (int i = 0; i < candidate_count; i++) {
    // check of the candidate votes are more than the needed votes
    if (candidates[i].votes > needed_votes) {
      printf("%s\n", candidates[i].name);
      return true;
    }
  }

  return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void) {
  /* TODO:
   * loop over Candidates -- done
   * if the candidate is not eliminated && have the least votes:
   *    return his number of votes
   */
  // the minimum index
  // find the first not eliminated candidate
  int min_index = first_candidate();

  // loop over candidates
  for (int i = 0; i < candidate_count; i++) {
    // if the candidate[i] is not eliminated && his votes are less than the
    // candidate_index who have the least votes
    if (candidates[i].eliminated == false &&
        candidates[i].votes < candidates[min_index].votes) {
      min_index = i;
    }
  }
  return candidates[min_index].votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min) {
  /* TODO:
   * loop over candidates -- done
   * if the candidate[first_voter].votes != candidates[i].votes:
   */
  int min_index = first_candidate();
  // loop over candidates
  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].eliminated == false &&
        candidates[min_index].votes != candidates[i].votes) {
      return false;
    }
  }
  return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min) {
  /* TODO:
   * loop over candidates
   * if the candidates[i].votes == min:
   *    candidates[i].eliminated = true
   */
  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].votes == min) {
      candidates[i].eliminated = true;
    }
  }
  return;
}

int first_candidate(void) {
  // find the first not eliminated candidate
  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].eliminated == false) {
      return i;
    }
  }
  return 0;
}

// just for testing
/*candidates[0].name = "bob";*/
/*candidates[0].votes = 0;*/
/**/
/*candidates[1].name = "mark";*/
/*candidates[1].votes = 3;*/
/*/*candidates[1].eliminated = true;*/
/**/
/*candidates[2].name = "joe";*/
/*candidates[2].votes = 3;*/
/**/
/*candidate_count = 3;*/
/*voter_count = 6;*/
/*int min = find_min();*/
/*eliminate(min);*/
/*for (int i = 0; i < candidate_count; i++) {*/
/*  printf("%s\n", candidates[i].name);*/
/*  printf("%i\n", candidates[i].eliminated);*/
/*}*/
