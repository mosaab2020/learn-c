#include <cs50.h>
#include <stdio.h>

int main(void) {
  int height;
  // if the height is less than 0 or more than 8, reprompt
  do {
    height = get_int("Height: ");
  } while (height <= 0 || height > 8);

  int counter = 0;

  for (int i = height; i > 0; i--) {
    // the first #
    for (int j = 0; j < height; j++) {
      // print the spaces
      if (j < i - 1) {
        printf(" ");
      } else if (j < height) {
        printf("#");
      }
    }

    printf("  ");

    // the second #
    for (int k = 0; k < counter + 1; k++) {
      printf("#");
    }
    counter++;
    printf("\n");
  }
}
