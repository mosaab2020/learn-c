# program main
def main():
    text = input("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # print(letters)
    # print(words)
    # print(sentences)

    res: int = coleman_index(letters, words, sentences)

    print_level(res)


def count_letters(str):
    counter: int = 0

    for c in str:
        if c.isalpha():
            counter += 1

    return counter


def count_words(str):
    counter: int = 0

    for c in str:
        if c == " ":
            counter += 1

    return counter + 1


def count_sentences(str):
    counter: int = 0

    for c in str:
        if c in ["!", ".", "?"]:
            counter += 1

    return counter


def coleman_index(L: int, W: int, S: int):
    index: int = round(0.0588 * L / W * 100 - 0.296 * S / W * 100 - 15.8)
    return index


def print_level(index: int):
    if index >= 1 and index < 16:
        print(f"Grade {index}")
    elif index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")


main()
