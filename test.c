#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*int lengthOfLastWord(char *s) {*/
/*  int c = 0;*/
/*  for (int i = strlen(s) - 1; i >= 0; i--) {*/
/*    if (s[i] == ' ') {*/
/*      if (c > 0) {*/
/*        break;*/
/*      }*/
/*    } else {*/
/*      c++;*/
/*    }*/
/*  }*/
/**/
/*  return c;*/
/*}*/

int removeDuplicates(int *nums, int numsSize) {
  /* TODO:
   * have to pointers -- done
   * loop over the array -- done
   * if the first element in nums, is !equal to element in k:
   *    nums[i-1] = nums[i];
   *
   */
  int k = 0;
  for (int i = 0; i < numsSize; i++) {
    if (nums[k] != nums[i]) {
      nums[k + 1] = nums[i];
      k++;
    }
  }
  return k + 1;
}

int main(void) {
  // program start:
  /*printf("length: %i\n", lengthOfLastWord("hello world   ")); */
  int array[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

  printf("k: %i\n", removeDuplicates(array, 10));
}
