#include <cs50.h>
#include <stdio.h>

void draw(int n);

int main(void) {
  int height = get_int("Height: ");
  draw(height);
}

void draw(int n) {
  // if nothing to draw
  if (n <= 0) {
    // exit
    return;
  }

  for (int i = 0; i < n; i++) {
    printf("#");
  }

  // prints a new line
  printf("\n");

  draw(n - 1);
}

/*
 *
 */
