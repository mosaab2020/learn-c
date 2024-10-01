#include <cs50.h>
#include <stdio.h>

/*
 * american express:
 * 15 digits, starts with 34 or 37
 *
 * mastercard:
 * 16 digits, starts with 51, 52, 53, 54, or 55
 *
 * visa:
 * 13 or 16 digits, starts with 4
*/

bool checkSum(long num);
string checkType(long num);

int main(void) {
  /*long creditNum = 4003600000000014;*/
  long creditNum = 1234567891234567;
  /*long creditNum = 5103600000000016;*/

  printf("%s\n", checkType(creditNum));
}

bool checkSum(long num) {
  bool multiply = false;
  bool isValid = false;
  int result = 0;

  while (num > 0) {
    int digit = num % 10;
    if (multiply) {
      digit = digit * 2;
      if (digit > 9) {
        result = result + digit % 10 + digit / 10 % 10;
      } else {
        result = result + digit;
      }

      multiply = false;
    } else if (!multiply) {
      result = result + digit;
      multiply = true;
    }
    num = num / 10;
  }
  if (result % 10 == 0) {
    isValid = true;
  }

  return isValid;
}

string checkType(long num) {
  /* TODO:
   *  get the length of num -- done
   *  check length and match cardType -- done
   *  then return cardType -- done
   *  make a function to checkType and checkSum function -- done
   *
   *  TODO later:
   *  review the code and check for improvements
   * */
  long firstDigits = num;
  string cardType = "INVAILD";
  int length  = 0;

  if (checkSum(num)) {

  // Remove last digit from number
  // till only two digits are left
  while (firstDigits >= 100) {
    firstDigits /= 10;
    length++;
  }

  // increase counter by two because the while loop loop til there are 2 digits
  length += 2;


  // check card type and change the cardType value
  if ((length == 15) && (firstDigits == 34 || firstDigits == 37)) {
	cardType = "AMEX";
  } else if ((length == 16 || length == 13) && (firstDigits / 10 == 4)) {
	cardType = "VISA";
  } else if ((length == 16) && (firstDigits >= 51 && firstDigits <= 55)) {
	cardType = "MASTERCARD";
  }

  }
  return cardType;
}


// some testing comments

/*printf("%li\n", creditNum % 0.1);*/
/*printf("%li\n", creditNum / 100 % 20);*/
/*printf("%li\n", creditNum / 1000 % 20);*/
/*printf("%li\n", creditNum / 10000 % 20);*/
/*printf("%li\n", creditNum / 100000 % 20);*/
/*printf("%li\n", creditNum / 1000000 % 20);*/
/*printf("%li\n", creditNum / 10000000 % 20);*/
/*printf("%li\n", creditNum / 100000000 % 20);*/
/*printf("%li\n", creditNum / 1000000000 % 20);*/
/*printf("%li\n", creditNum / 10000000000 % 20);*/
/*printf("%li\n", creditNum / 100000000000 % 20);*/
/*printf("%li\n", creditNum / 1000000000000 % 20);*/
/*printf("%li\n", creditNum / 10000000000000 % 20);*/
/*printf("%li\n", creditNum / 1000000000000000 % 20);*/
/**/
