#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Make sure program was run with just one command-line argument - done
 * Make sure every character in argv[1] is a digit - done
 * Convert argv[1] from a `string` to an `int` - done
 * Prompt user for plaintext - done
 * For each character in the plaintext: - done
 *    Rotate the character if it's a letter - done
 */

int exit_status = 0;

bool only_digits(string s);
char rotate(char c, int key);

int main(int argc, string argv[]) {
  /*
   * check if the argument number (argc) is 2,
   * which is ./caesar and the key (number)
   * and only_digits function is true
   */

  // make the key int
  int key = atoi(argv[1]);

  if (argc == 2 && only_digits(argv[1]) && key >= 0) {
    string plainText = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plainText); i < n; i++) {
      printf("%c", rotate(plainText[i], key));
    }

    printf("\n");
  } else {
    printf("Usage: %s key\n", argv[0]);
    return exit_status + 1;
  }
}

bool only_digits(string s) {
  for (int i = 0, n = strlen(s); i < n; i++) {
    if (!isdigit(s[i])) {
      return false;
    }
  }
  return true;
}

char rotate(char letter, int key) {
  // if the letter is alpha
  if (isalpha(letter)) {
    // if the letter is lowercase
    if (islower(letter)) {
      letter = (letter - 97 + key) % 26;
      letter += 97;
      // if the letter is uppercase
    } else if (isupper(letter)) {
      letter = (letter - 65 + key) % 26;
      letter += 65;
    }
  }
  return letter;
}

// test code
/*char letters[26] = {*/
/*    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',*/
/*    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',*/
/*};*/
