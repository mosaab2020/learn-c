def main():

    text = input("Text: ")

    letters = count_letters(text)
    print(letters)


def count_letters(str):
    counter = 0
    for c in str:
        if c.isalpha():
            counter += 1
    return counter
