#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  string name;
  string number;
} person;

int main(void) {
  /*string names[] = {"name1", "name2", "name3"};*/
  /*string numbers[] = {"111-111-111", "222-222-222", "333-333-333"};*/
  person people[3];

  /*people[0] = {"name1", "111-111-1111"};*/
  people[0].name = "name1";
  people[0].number = "111-111-1111";

  people[1].name = "name2";
  people[1].number = "222-222-2222";

  people[2].name = "name3";
  people[2].number = "333-333-3333";

  string name = get_string("Name: ");
  for (int i = 0; i < 3; i++) {
    if (strcmp(people[i].name, name) == 0) {
      printf("Found %s\n", people[i].number);
      return 0;
    }
  }
  printf("Not found\n");
  return 1;
}
