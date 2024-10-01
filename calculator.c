#include <cs50.h>
#include <stdio.h>

int add(int a, int b);
int min(int a, int b);

int main(void) {
  // sixth program
  int x = get_int("x: ");
  int y = get_int("y: ");

  int z = min(x, y);

  printf("%i\n", z);
}

int add(int a, int b) {
  // return value
  return a + b;
}

int min(int a, int b) {
  // return value
  return a - b;
}
