from cs50 import get_int


def main():
    creditNum = 0

    while creditNum <= 0:
        creditNum = get_int("Number: ")

    res = checkType(creditNum)
    print(f"{res}")


def checkSum(num: int):
    multiply: bool = False
    isValid: bool = False
    result: int = 0

    while int(num) > 0:
        digit = num % 10
        if multiply:
            digit = digit * 2
            if digit > 9:
                result = result + digit % 10 + digit // 10 % 10
            else:
                result = result + digit
            multiply = False
        elif not multiply:
            result = result + digit
            multiply = True
        num = num // 10

    if int(result) % 10 == 0:
        isValid = True

    return isValid


def checkType(num: int):
    firstDigits: int = num
    cardType = "INVALID"
    length: int = 0

    if checkSum(num):

        while firstDigits >= 100:
            firstDigits //= 10
            length += 1

        length += 2

        if length == 15 and (firstDigits == 34 or firstDigits == 37):
            cardType = "AMEX"
        elif (length == 16 or length == 13) and (firstDigits // 10 == 4):
            cardType = "VISA"
        elif length == 16 and (firstDigits >= 51 and firstDigits <= 55):
            cardType = "MASTERCARD"

    return cardType


# run the program
main()
