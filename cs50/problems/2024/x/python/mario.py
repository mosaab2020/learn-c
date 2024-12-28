from cs50 import get_int

height = 0

while height > 8 or height < 1:
    height = get_int("Height: ")

counter = 0

for i in range(height, 0, -1):
    for j in range(height):
        if j < i - 1:
            print(" ", end="")
        elif j < height:
            print("#", end="")

    print("  ", end="")
    for k in range(counter+1):
        print("#", end="")

    counter += 1
    print()
