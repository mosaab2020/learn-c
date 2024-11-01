#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);
void print_winner(int score1, int score2);

int main(void) {
  // Prompt the user for two words
  string word1 = get_string("Player 1: ");
  string word2 = get_string("Player 2: ");

  // Compute the score of each word
  int score1 = compute_score(word1);
  int score2 = compute_score(word2);

  /*printf("%i\n", score1);*/
  /*printf("%i\n", score2);*/
  // Print the winner
  print_winner(score1, score2);
}

int compute_score(string word) {
  // Compute and return score for word
  int score = 0;
  int word_index;
  int WORD_SCORE[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

  for (int i = 0, len = strlen(word); i < len; i++) {
    if (islower(word[i])) {
      word[i] -= 'a';
      word_index = word[i];
      score += WORD_SCORE[word_index];
    } else if (isupper(word[i])) {
      word[i] -= 'A';
      word_index = word[i];
      score += WORD_SCORE[word_index];
    }
  }
  return score;
}

void print_winner(int score1, int score2) {
  if (score1 > score2) {
    printf("Player 1 wins!\n");
  } else if (score2 > score1) {
    printf("Player 2 wins!\n");
  } else {
    printf("Tie!\n");
  }
}
