#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string str);
int count_words(string str);
int count_sentences(string str);
int coleman_index(int L, int W, int S);
void print_level(int index);

int main(void) {
  // Prompt the user for some text
  string text = get_string("Text: ");
  /*string text = "Congratulations! Today is your day. You're off to Great "*/
  /*              "Places! You're off and away!";*/

  // Count the number of letters, words, and sentences in the text
  int letters = count_letters(text);
  int words = count_words(text);
  int sentences = count_sentences(text);

  /*printf("letters: %i\n", letters);*/
  /*printf("words: %i\n", words);*/
  /*printf("sentences: %i\n", sentences);*/

  // Compute the Coleman-Liau index
  int index = coleman_index(letters, words, sentences);

  // Print the grade level
  print_level(index);
}

int count_letters(string str) {
  int counter = 0;
  for (int i = 0, len = strlen(str); i < len; i++) {
    if (isalpha(str[i])) {
      counter++;
    }
  }
  return counter;
}

int count_words(string str) {
  int counter = 0;
  for (int i = 0, len = strlen(str); i < len; i++) {
    if (str[i] == ' ') {
      counter++;
    }
  }
  // Add one for the last word
  counter++;
  return counter;
}

int count_sentences(string str) {
  int counter = 0;
  for (int i = 0, len = strlen(str); i < len; i++) {
    if (str[i] == '!' || str[i] == '.' || str[i] == '?') {
      counter++;
    }
  }
  // Add one for the last word
  return counter;
}

// Calculate the Coleman-Liau index
int coleman_index(int L, int W, int S) {
  int index = round(0.0588 * L / W * 100 - 0.296 * S / W * 100 - 15.8);
  return index;
}

void print_level(int index) {
  if (index >= 1 && index < 16) {
    printf("Grade %i\n", index);
  } else if (index >= 16) {
    printf("Grade 16+\n");
  } else if (index < 1) {
    printf("Before Grade 1\n");
  }
}
