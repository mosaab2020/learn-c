#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 45

const int N = 26;

typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;

// Hash table
node *table[N];

unsigned int hash(const char *word) {
  // TODO: Improve this hash function
  unsigned int hash = 0;
  int counter = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    if (isalpha(word[i])) {
      hash += toupper(word[i]) - 'A';
      counter++;
    }

    if (counter >= 3) {
      break;
    }
  }
  return hash % N;
}
// Returns true if word is in dictionary, else false
bool check(const char *word) {
  /* TODO:
   * hash word to get a hash value -- done
   * Access linked list at that index in the hash table -- done
   * traverse linked list, looking for the word (strcasecmp) -- done
   */
  int index = hash(word);

  // cursor
  node *cursor = table[index];
  while (cursor != NULL) {
    if (strcasecmp(word, cursor->word) == 0) {
      return true;
    }
    cursor = cursor->next;
  }
  return false;
}

int main(void) {
  // program start:
  /*char str[LENGTH + 1];*/
  char *str = "foo";

  /*scanf("%s", str);*/

  printf("%i\n", check(str));
}
