#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  /*int i = get_int("i: ");*/
  /*int j = get_int("j: ");*/
  char *s = get_string("s: ");
  char *t = get_string("t: ");

  if (s == t) {
    printf("Same\n");
  } else {
    printf("Different\n");
  }
}

int string_length(char *s) {
  int counter = 0;
  while (s[counter] != '\0') {
    counter++;
  }
  return counter;
}

/*
 * TODO:
 * check if s1 length is equal to s2
 * loop over s1 and s1
 */
int chrcmp(char *s1, char *s2) {}
