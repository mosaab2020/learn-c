#include <cs50.h>
#include <stdio.h>
#include <string.h>

int string_length(string s);

int main(void) {
  string name = "mosaab0j";
  int length = strlen(name);
  printf("%i\n", length);
}

int string_length(string s) {
  int counter = 0;
  while (s[counter] != '\0') {
    counter++;
  }
  return counter;
}
