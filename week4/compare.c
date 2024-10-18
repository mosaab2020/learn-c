#include <cs50.h>
#include <stdio.h>

int string_length(char *s);
int chrcmp(char *s1, char *s2);

int main(void) {
  /*int i = get_int("i: ");*/
  /*int j = get_int("j: ");*/
  char *s = get_string("s: ");
  char *t = get_string("t: ");

  if (chrcmp(s, t) == 0) {
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
 * check if s1 length is equal to s2 -- done
 * loop over s1 and s1 -- done
 * check if  s1[i] doesn't equal s2[i] -- done
 * return zero if all chars are the same -- done
 */
int chrcmp(char *s1, char *s2) {
  if (string_length(s1) != string_length(s2)) {
    return 1;
  }
  for (int i = 0, len = string_length(s1); i < len; i++) {
    if (s1[i] != s2[i]) {
      return 1;
    }
  }
  return 0;
}
