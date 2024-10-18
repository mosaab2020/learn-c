#include <stdio.h>

typedef int integer;
typedef char *string;

int main(void) {
  char *s = "HI!";
  printf("%c\n", *s);
  printf("%c\n", *(s + 1));
}
