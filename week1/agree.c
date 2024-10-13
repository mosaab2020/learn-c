#include <cs50.h>
#include <stdio.h>

int main(void) {
  // fourth program
  char c = get_char("Do you agree? (Y/n) ");

  if (c == 'y' || c == 'Y') {
    printf("Agreed\n");
  } else if (c == 'n' || c == 'N') {
    printf("Didn't agree\n");
  }
}
