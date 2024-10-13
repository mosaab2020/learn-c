#include <cs50.h>
#include <stdio.h>

void meow(int counter);

int main(void) {
  // fifth program
  // hello this is a program that meow
  /*int i = 0;*/
  /**/
  /*while (i < 3) {*/
  /*  printf("Meow\n");*/
  /*  i++;*/
  /*}*/
  /**/
  /*for (int i = 0; i < 3; i++) {*/
  /*  printf("Meow\n");*/
  /*}*/

  // better meow
  meow(3);
}

void meow(int counter) {
  for (int i = 0; i < counter; i++) {
    printf("Meow\n");
  }
}
