// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
  char word[LENGTH + 1];
  struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 53;

// Hash table
node *table[N];

// number of words
int size_num = 0;

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

// Hashes word to a number
unsigned int hash(const char *word) {
  // TODO: Improve this hash function -- done
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

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
  /* TODO:
   * open dictionary file -- done
   * read strings from file one at a time -- done
   * create a ne node for each work -- done
   * hash word to obtain a hash value -- done
   * insert node into hash table at that location -- done
   */
  FILE *file = fopen(dictionary, "r");
  if (file == NULL) {
    return false;
  }

  for (int i = 0; i < N; i++) {
    table[i] = NULL;
  }

  char word[LENGTH + 1];

  while (fscanf(file, "%s", word) != EOF) {
    node *n = malloc(sizeof(node));
    if (n == NULL) {
      return false;
    }

    strcpy(n->word, word);

    // find the index of the word on the table
    int index = hash(n->word);

    // point to the next element
    n->next = table[index];

    // point the table to the new element
    table[index] = n;
    size_num++;
  }
  fclose(file);
  /*printf("size_num: %i\n", size_num);*/
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
  // TODO -- done
  return size_num;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
  /* TODO:
   * loop over table -- done
   * create a cursor and a tmp pointers -- done
   * tmp is equal to cursor -- done
   * loop over the linked list -- done
   * while cursor != NULL: -- done
   *    cursor is equal to the next cursor -- done
   *    tmp frees the node -- done
   *    tmp is equal to cursor -- done
   */
  for (int i = 0; i < N; i++) {
    node *cursor = table[i];
    node *tmp = cursor;
    while (cursor != NULL) {
      cursor = cursor->next;
      free(tmp);
      tmp = cursor;
    }
  }
  return true;
}
