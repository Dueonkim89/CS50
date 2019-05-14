from cs50 import get_int

height = get_int("Height: ")

while height <= 0 or height > 8:
    height = get_int("Height: ")

for i in range(height):
    for j in range(height):
        if (j + i) + 1 < height:
            print(" ", end="")
        else:
            print("#", end="")

    print(" ", end="")
    print(" ", end="")

    for k in range(height):
        if k <= i:
            print("#", end="")
    print()
