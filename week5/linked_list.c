#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int number;
  struct node *next;
} node;

int main(int argc, char *argv[]) {
  // start
  node *list = NULL;
  ;
  for (int i = 1; i < argc; i++) {
    int number = atoi(argv[i]);
    /*printf("%i\n", number);*/

    node *n = malloc(sizeof(node));
    if (n == NULL) {
      return 1;
    }
    n->number = number;
    n->next = list;
    list = n;
  }

  // print whole list
  node *ptr = list;

  while (ptr != NULL) {
    printf("%i\n", ptr->number);
    ptr = ptr->next;
  }

  return 0;
}
